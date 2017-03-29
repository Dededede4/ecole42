/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:10:32 by mprevot           #+#    #+#             */
/*   Updated: 2017/03/21 19:10:36 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compiler.h"

void			compiler_hydrate_argument(
	t_op opecode_config, char *arg, t_instruct *inst, int arg_no)
{
	int			argint;

	inst->args[arg_no][0] = get_argtype(arg, opecode_config.tab_arg[arg_no]);
	if (inst->args[arg_no][0] == T_REG)
		inst->args[arg_no][1] = 1;
	else if (inst->args[arg_no][0] == T_IND ||
			inst->args[arg_no][0] == T_LABIND)
		inst->args[arg_no][1] = 2;
	else
		inst->args[arg_no][1] = (opecode_config.nbr_octet_dir) ? 2 : 4;
	if (opecode_config.have_ocp)
	{
		inst->argcode = inst->argcode << 2;
		if (inst->args[arg_no][0] == T_DIR || inst->args[arg_no][0] == T_LABDIR)
			inst->argcode = inst->argcode | 2;
		if (inst->args[arg_no][0] == T_REG)
			inst->argcode = inst->argcode | 1;
		if (inst->args[arg_no][0] == T_IND || inst->args[arg_no][0] == T_LABIND)
			inst->argcode = inst->argcode | 3;
	}
	if (inst->args[arg_no][0] > T_LAB)
		inst->args_labels[arg_no] = extract_str(arg);
	argint = (inst->args[arg_no][0] <= T_LAB) ? extract_int(arg) : 0;
	ft_memmove(inst->args[arg_no] + 2, &argint, inst->args[arg_no][1]);
}

t_op			compiler_hydrate_opcode(
	char *line, t_instruct *inst, char ***splited)
{
	char		*str;
	char		*tmpstr;
	int			i;
	t_op		opecode_config;

	tmpstr = ft_strtrim(line);
	if ((str = ft_strchr(tmpstr, COMMENT_CHAR)))
		*str = 0;
	str = tmpstr;
	i = 0;
	while (str[i] != ' ' && str[i] != '\t' && str[i])
		i++;
	tmpstr = ft_strsub(str, 0, i);
	opecode_config = get_config(tmpstr);
	ft_memdel((void**)&tmpstr);
	tmpstr = ft_strtrim(str + i);
	ft_memdel((void**)&str);
	inst->opcode = opecode_config.op_code;
	inst->arg_nbrs = opecode_config.nb_arg;
	if (opecode_config.op_code != 0)
		*splited = ft_strsplit(tmpstr, SEPARATOR_CHAR);
	ft_memdel((void**)&tmpstr);
	return (opecode_config);
}

void			compiler_compile_line(
	char *line, t_instruct *inst)
{
	int			y;
	char		**splited;
	t_op		opecode_conf;
	char		*arg;

	splited = NULL;
	opecode_conf = compiler_hydrate_opcode(line, inst, &splited);
	if (opecode_conf.op_code == 0)
		return ;
	y = 0;
	while (y < opecode_conf.nb_arg && splited[y])
	{
		arg = ft_strtrim(splited[y]);
		compiler_hydrate_argument(opecode_conf, arg, inst, y++);
		ft_memdel((void**)&arg);
	}
	if (((y = (y == 0) ? 1 : y) && splited[y] != 0) || y != opecode_conf.nb_arg)
		error("Bad arguments number.\n");
	while (y++ < 4)
		inst->argcode = inst->argcode << 2;
	while (splited[y - 5])
		ft_memdel((void**)&splited[(y++ - 5)]);
	ft_memdel((void**)&splited);
	inst->size = inst->args[0][1] + inst->args[1][1] + inst->args[2][1] + 1;
	inst->size = (inst->argcode) ? inst->size + 1 : inst->size;
}

void			compiler_compile_newinstruct(
	char **line, t_instruct **inst_first)
{
	t_instruct	*inst;
	int			endlabel;
	char		*instruct;

	if (!(inst = (ft_memalloc(sizeof(t_instruct)))))
		error("Malloc error\n");
	endlabel = compiler_compile_get_label(*line);
	if (endlabel != -1)
		inst->label_name = ft_strsub(*line, 0, endlabel);
	instruct = ft_strtrim((endlabel != -1) ? *line + endlabel + 1 : *line);
	if (*instruct)
		compiler_compile_line(instruct, inst);
	ft_memdel((void**)&instruct);
	instructs_add(inst_first, inst);
	ft_memdel((void**)line);
}

t_instruct		*compiler_compile(int fdin)
{
	char		*line;
	t_instruct	*inst_first;

	inst_first = NULL;
	while (gnl(fdin, &line))
	{
		if (!(*line) || *line == COMMENT_CHAR)
		{
			ft_memdel((void**)&line);
			continue ;
		}
		line = ft_strtrim_free(&line);
		if (!*line || *line == COMMENT_CHAR)
		{
			ft_memdel((void**)&line);
			continue;
		}
		compiler_compile_newinstruct(&line, &inst_first);
	}
	ft_memdel((void**)&line);
	hydrate_labels(inst_first);
	return (inst_first);
}

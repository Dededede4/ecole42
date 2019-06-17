/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:10:44 by heynard           #+#    #+#             */
/*   Updated: 2017/05/11 22:41:54 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <wchar.h>

# define BUF_SIZE 100

typedef enum	e_modifier
{
	H, HH, L, LL, J, Z, M_DEFAULT
}				t_modifier;

typedef enum	e_type
{
	U_DEC, S_DEC, OCTAL, L_HEXA, U_HEXA,
	U_CHAR, STRING, PTR, PERCENT, U_BIN,
	T_DEFAULT
}				t_type;

typedef struct	s_format
{
	int			position;
	int			written;
	int			print;
	int			fd;
	int			is_error;
	int			nb_of_arg;
	int			cursor_error;
	const char	*format;
}				t_format;

typedef struct	s_flags
{
	int			alternate_form;
	int			zero_pad;
	int			add_space;
	int			force_sign;
	int			rev_pad;
}				t_flags;

typedef struct	s_argument
{
	t_modifier	modifier;
	t_flags		flags;
	int			nb_of_zero;
	int			precision_is_set;
	int			precision;
	int			min;
	int			is_ptr;
	int			neg;
	t_type		type;
}				t_arg;

int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);

/*
** Fonctions utiles
*/

int				ft_isdigit(int c);
int				ft_isdigit_nozero(int c);
intmax_t		ft_rev_nbr(intmax_t nbr, int *nb_of_zero);
int				ft_count_nb(intmax_t nb);
int				ft_count_base_nb(intmax_t nb, int base);
int				size_of_wchar(wchar_t c);

/*
** Fonctions parsing
*/

int				ft_is_end_of_arg(t_format *env, int i);
void			parse_arg(t_format *env, va_list ap, char buffer[BUF_SIZE]);
int				parse_arg_modifier(t_format *env, t_arg *arg);
int				parse_arg_flags(t_format *env, t_arg *arg, int tmp);
int				parse_arg_precision(t_format *env, t_arg *arg,
										int tmp, va_list ap);
int				parse_arg_min(t_format *env, t_arg *arg, int tmp, va_list ap);
int				parse_arg_type(t_format *env, t_arg *arg);

/*
** Fonctions d'ecriture dans le buffer
*/

void			ft_reset_buffer(t_format *env, char buffer[BUF_SIZE]);
void			ft_reset_buffer_d(t_format *env, char buffer[BUF_SIZE]);
void			padding_int(t_format *env, t_arg *arg, char buffer[BUF_SIZE],
								intmax_t to_print);
void			write_str(t_format *env, t_arg *arg, char *to_print,
								char buffer[BUF_SIZE]);
void			write_wchar(t_format *env, wchar_t chr, char buffer[BUF_SIZE]);
void			put_char_in_buffer(t_format *env,
									char to_print, char buffer[BUF_SIZE]);
void			write_arg_in_buffer(t_format *env, va_list ap,
									t_arg *arg, char buffer[BUF_SIZE]);
void			write_sint_in_buffer(t_format *env, t_arg *arg, va_list ap,
									char buffer[BUF_SIZE]);
void			write_uint_in_buffer(t_format *env, t_arg *arg, va_list ap,
									char buffer[BUF_SIZE]);
void			write_hexa_in_buffer(t_format *env, t_arg *arg, va_list ap,
									char buffer[BUF_SIZE]);
void			write_octal_in_buffer(t_format *env, t_arg *arg, va_list ap,
									char buffer[BUF_SIZE]);
void			write_char_in_buffer(t_format *env, t_arg *arg, va_list ap,
									char buffer[BUF_SIZE]);
void			write_str_in_buffer(t_format *env, t_arg *arg, va_list ap,
									char buffer[BUF_SIZE]);
void			write_str_in_buffer(t_format *env, t_arg *arg, va_list ap,
									char buffer[BUF_SIZE]);
void			write_ptr_in_buffer(t_format *env, t_arg *arg, va_list ap,
									char buffer[BUF_SIZE]);
void			write_wchar_in_buffer(t_format *env, t_arg *arg, va_list ap,
									char buffer[BUF_SIZE]);
void			write_wstr_in_buffer(t_format *env, t_arg *arg, va_list ap,
									char buffer[BUF_SIZE]);
void			write_bin_in_buffer(t_format *env, t_arg *arg, va_list ap,
									char buffer[BUF_SIZE]);

/*
** Fonctions d'affichage
*/

void			full_print_buffer(char buffer[BUF_SIZE]);
void			final_print_buffer(char buffer[BUF_SIZE]);
void			error_print_buffer(char buffer[BUF_SIZE], size_t written);
void			full_print_buffer_d(char buffer[BUF_SIZE], t_format *env);
void			final_print_buffer_d(char buffer[BUF_SIZE], t_format *env);
void			error_print_buffer_d(char buffer[BUF_SIZE], size_t written,
									t_format *env);

#endif

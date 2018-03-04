# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprevot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/01 11:18:53 by mprevot           #+#    #+#              #
#    Updated: 2017/08/10 21:38:54 by mprevot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc

CFLAGS=-Wall -Wextra -Werror -ltermcap -w -g

RM=rm -f

SRC= main.c execute/execute.c prompt/insert_delete_chars.c prompt/init_termcaps.c prompt/termcaps1.c prompt/termcaps2.c prompt/display_directions.c prompt/display_supermoves.c prompt/display_supermoves_homeend.c\
prompt/clear_input.c prompt/display_input_delete_insert.c prompt/display_input_validate.c\
prompt/display_input_historic.c prompt/display_input_copypast.c prompt/complete_buff.c\
prompt/display_input_heredoc.c prompt/ft_putchar2.c prompt/show_command.c prompt/sig_handler.c\
execute/get_word_pos.c execute/clear_escapes.c execute/tokenize.c \
execute/command2instruct_redirect.c execute/command2instruct.c execute/instructs_pipe_chain.c execute/heredoc.c\
execute/deltoken.c execute/ft_execwait.c execute/instruct_to_argv.c \
execute/minishell.c execute/instruct_file2fd_chain.c execute/exec_instruct_simple.c execute/instruct_pipe_fd.c\
execute/storeinstructs.c

OBJS=$(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: 21sh

21sh: $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o 21sh

clean:
	$(RM) $(OBJS)
	make -C libft clean

fclean: clean
	$(RM) 21sh
	make -C libft fclean

re: fclean all

libft/libft.a:
	make -C libft

.PHONY: clean fclean re all

#gcc -Wall -Wextra -Werror -ltermcap -g -o 21sh execute/command2instruct.c main.c execute.c prompt/insert_delete_chars.c prompt/init_termcaps.c prompt/termcaps1.c prompt/termcaps2.c prompt/display_directions.c prompt/display_supermoves.c prompt/clear_input.c prompt/display_input_delete_insert.c prompt/display_input_validate.c prompt/display_input_historic.c prompt/display_input_copypast.c prompt/complete_buff.c prompt/display_input_heredoc.c prompt/ft_putchar2.c prompt/show_command.c prompt/sig_handler.c execute/get_word_pos.c execute/clear_escapes.c execute/tokenize.c
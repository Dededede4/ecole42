# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    srcs_list.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heynard <heynard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/03 11:43:27 by heynard           #+#    #+#              #
#    Updated: 2018/06/03 11:43:28 by heynard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PATH_LIST = srcs/ft_list/

SRCS_LIST = ft_print_error_list.c\
			sl_add_first.c\
			sl_add_last.c\
			sl_add_sort.c\
			sl_check_list.c\
			sl_count.c\
			sl_count_one.c\
			sl_create_list.c\
			sl_create_node.c\
			sl_del_first.c\
			sl_del_last.c\
			sl_del_list.c\
			sl_del_n.c\
			sl_is_set.c\
			sl_get_data.c\
			sl_get_data_n.c\
			sl_print_list.c\
			dl_add_first.c\
			dl_add_last.c\
			dl_add_sort.c\
			dl_check_list.c\
			dl_count.c\
			dl_count_one.c\
			dl_create_list.c\
			dl_create_node.c\
			dl_del_first.c\
			dl_del_last.c\
			dl_del_list.c\
			dl_del_n.c\
			dl_is_set.c\
			dl_get_data.c\
			dl_get_data_n.c\
			dl_print_list.c
			
			
PATH_SRC_LIST = $(addprefix $(PATH_LIST), $(SRCS_LIST))

OBJ_LIST = $(PATH_SRC_LIST:.c=.o)

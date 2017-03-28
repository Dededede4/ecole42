# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/13 14:54:46 by ntoniolo          #+#    #+#              #
#    Updated: 2017/03/28 17:50:25 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : clean, fclean, re, all $(NAME)
.SUFFIXES :

CC = gcc
FLAGS = -Wall -Werror -Wextra
SPE_FLAGS =  -lncurses -g
OPTI_FLAGS = -O2
DEBUG_FLAG = -fsanitize=address
EXTRA_FLAGS =
E = -O2 -Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int \
	-Werror-implicit-function-declaration -Wmain -Wparentheses \
	-Wsign-compare -Waggregate-return -Wstrict-prototypes \
	-Wmissing-prototypes -Wmissing-declarations -Wmissing-noreturn \
	-Wformat -Wmissing-format-attribute -Wno-deprecated-declarations \
	-Wpacked -Wredundant-decls -Wnested-externs -Winline -Wlong-long \
	-Wunreachable-code \
	-Wsequence-point -Wreturn-type -Wswitch -Wtrigraphs -Wunused \
	-Wuninitialized -Wunknown-pragmas -Wfloat-equal -Wundef \
	-Wshadow -Wpointer-arith -Wbad-function-cast \
	-Wpadded  -Wwrite-strings -Wconversion
	-Weverything -std=c89 -pedantic -MMD

NAME = corewar

LIB = $(LIB_DIR)libft.a
LIB_DIR = ./../includes/libft/

SRC3 = ncurses_end.c \
	   ncurses_key.c \
	   ncurses_find_pc.c \
	   ncurses_loop_arene.c \
	   ncurses_light.c \
	   ncurses_kirby.c \
	   ncurses_comment.c \
	   ncurses_cycle.c \
	   ncurses_put_background.c \
	   ncurses_main_menu.c \
	   ncurses_process.c \
	   ncurses_start_init.c \
	   ncurses_init.c \
	   ncurses_print_end.c

SRC2 = vm_champ_number_to_position.c \
	   vm_champ_position_to_number.c \
	   vm_add_valid.c \
	   vm_op_0_exec.c \
	   vm_op_10_exec.c \
	   vm_op_11_exec.c \
	   vm_op_12_exec.c \
	   vm_op_13_exec.c \
	   vm_op_14_exec.c \
	   vm_op_15_exec.c \
	   vm_op_16_exec.c \
	   vm_op_17_exec.c \
	   vm_op_18_exec.c \
	   vm_op_19_exec.c \
	   vm_op_20_exec.c \
	   vm_op_21_exec.c \
	   vm_op_22_exec.c \
	   vm_op_23_exec.c \
	   vm_op_24_exec.c \
	   vm_op_1_exec.c \
	   vm_op_2_exec.c \
	   vm_op_3_exec.c \
	   vm_op_4_exec.c \
	   vm_op_5_exec.c \
	   vm_op_6_exec.c \
	   vm_op_7_exec.c \
	   vm_op_8_exec.c \
	   vm_op_9_exec.c \
	   vm_recup_all_process.c \
	   vm_recup_arena_num.c \
	   vm_recup_indirect_num.c \
	   vm_recup_process_reg.c \
	   vm_verif_datas.c \
	   vm_op_jump.c \
	   vm_put_nbr_in_arene.c

SRC = vm_main.c \
	  vm_copy_process.c \
	  vm_create_flags.c \
	  vm_create_process.c \
	  vm_destroy_process.c \
	  vm_do_cycles.c \
	  vm_champ_process.c \
	  vm_init_champ.c \
	  vm_init_process.c \
	  vm_innit_to_0.c \
	  vm_ocp_tools.c \
	  vm_show_arene.c \
	  vm_verif_macro.c \
	  vm_delete_unlive_process.c \
	  vm_turn_process.c \
	  vm_destroy_all_process.c \
	  vm_start_op_code.c \
	  vm_print_start_battle.c \
	  vm_print_end_battle.c \
	  vm_error.c \
	  vm_verif_num_champ.c \
	  ft_void_error.c \
	  ft_int_error.c \
	  ft_square_root.c \
	  ft_gcd.c \
	  ft_itoa_base_unsigned.c \
	  ft_isatoied.c \
	  ../../includes/share_c/corewar_op_tab.c \
	  ../../includes/share_c/corewar_music.c \
	  ../../includes/share_c/corewar_end_music.c

SRC_DIR = ./srcs/
SRC2_DIR = ./srcs/vm_op_mod/
SRC3_DIR = ./srcs/ncurses/

OBJ = $(SRC:.c=.o)
OBJ2 = $(SRC2:.c=.o)
OBJ3 = $(SRC3:.c=.o)

OBJ_DIR = ./objs/
OBJ2_DIR = ./objs/vm_op_mod/
OBJ2_DIR = ./objs/ncurses/

INC = ../includes/
INC_FILES = ../includes/corewar.h ../includes/struct.h ../includes/prototypes.h

all : $(NAME)

$(NAME) : $(LIB) $(OBJ_DIR) $(OBJ2_DIR) $(OBJ3_DIR) $(addprefix $(OBJ_DIR), $(OBJ)) $(addprefix $(OBJ_DIR), $(OBJ2)) $(addprefix $(OBJ_DIR), $(OBJ3)) $(INC_FILES)
	@($(CC) $(FLAGS) $(SPE_FLAGS) $(addprefix $(OBJ_DIR), $(OBJ)) $(addprefix $(OBJ_DIR), $(OBJ2)) $(addprefix $(OBJ_DIR), $(OBJ3)) $(LIB) -I$(INC) -o $(NAME))
	@(echo "\033[2K\033[2F")
	@(echo "\n\033[5m Ouverture de l'arene de Combat !!!!!!!!!!!\033[0m")
	@(echo "\033[2K";)
	@(echo "\t\t\t\t\t\t\t\t    Survive in the arena             ";)
	@(echo "\t\t\t\t\t\t\t\t    Fight for fame and glory\n             ";)
	@(echo "\t\t\t\t\t                            ==(W{==========-      /===-                        ";)
	@(echo "\t\t\t\t\t                              ||  (.--.)         /===-_---~~~~~~~~~------____  ";)
	@(echo "\t\t\t\t\t                              | \\_,|**|,__      |===-~___                _,-' \`";)
	@(echo "\t\t\t\t\t                 -==\\\\        \`\\ ' \`--'   ),    \`//~\\\\   ~~~~\`---.___.-~~      ";)
	@(echo "\t\t\t\t\t             ______-==|        /\`\\\\_. .__/\\\\ \\\\    | |  \\\\\\\\           _-~\`         ";)
	@(echo "\t\t\t\t\t       __--~~~  ,-/-==\\\\      (   | .  |~~~~|   | |   \`\\        ,'             ";)
	@(echo "\t\t\t\t\t    _-~       /'    |  \\\\     )__/==0==-\\<>/   / /      \\      /               ";)
	@(echo "\t\t\t\t\t  .'        /       |   \\\\      /~\\___/~~\\/  /' /        \\   /'                ";)
	@(echo "\t\t\t\t\t /  ____  /         |    \\\`\\.__/-~~   \\  |_/'  /          \\/'                  ";)
	@(echo "\t\t\t\t\t/-'~    ~~~~~---__  |     ~-/~         ( )   /'        _--~\`                   ";)
	@(echo "\t\t\t\t\t                  \\_|      /        _) | ;  ),   __--~~                        ";)
	@(echo "\t\t\t\t\t                    '~~--_/      _-~/- |/ \\   '-~ \\                            ";)
	@(echo "\t\t\t\t\t                   {\\__--_/}    / \\\\_>-|)<__\\      \\                           ";)
	@(echo "\t\t\t\t\t                   /'   (_/  _-~  | |__>--<__|      |                          ";)
	@(echo "\t\t\t\t\t                  |   _/) )-~     | |__>--<__|      |                          ";)
	@(echo "\t\t\t\t\t                  / /~ ,_/       / /__>---<__/      |                          ";)
	@(echo "\t\t\t\t\t                 o-o _//        /-~_>---<__-~      /                           ";)
	@(echo "\t\t\t\t\t                 (^(~          /~_>---<__-      _-~                            ";)
	@(echo "\t\t\t\t\t                ,/|           /__>--<__/     _-~                               ";)
	@(echo "\t\t\t\t\t             ,//('(          |__>--<__|     /                  .----_          ";)
	@(echo "\t\t\t\t\t            ( ( '))          |__>--<__|    |                 /' _---_~\\        ";)
	@(echo "\t\t\t\t\t         \`-)) )) (           |__>--<__|    |               /'  /     ~\\\`\\      ";)
	@(echo "\t\t\t\t\t        ,/,'//( (             \\__>--<__\\    \\            /'  //        ||      ";)
	@(echo "\t\t\t\t\t      ,( ( ((, ))              ~-__>--<_~-_  ~--____---~' _/'/        /'       ";)
	@(echo "\t\t\t\t\t    \`~/  )\` ) ,/|                 ~-_~>--<_/-__       __-~ _/                  ";)
	@(echo "\t\t\t\t\t  ._-~//( )/ )) \`                    ~~-'_/_/ /~~~~~~~__--~                    ";)
	@(echo "\t\t\t\t\t   ;'( ')/ ,)(                              ~~~~~~~~~~                         ";)
	@(echo "\t\t\t\t\t  ' ') '( (/                                                                   ";)
	@(echo "\n\n\t\t\t        O";)
	@(echo "\t\t\t     ,-.|________________\033[31m____\033[0m";)
	@(echo "\t\t\t   O==+-|(>-------- \033[31m--  -     .>\033[0m";)
	@(echo "\t\t\t     \`- |\"\"\"\"\"\"\"d88b\033[31m\"\"\"\"\"\"\"\"\"\033[0m";)
	@(echo "\t\t\t      | O     d8P 88b       \033[31;5m\"\033[0m             ";)
	@(echo "\t\t\t      |  \    88= ,=88\033[0m      \033[31;5m'\033[0m             ";)
	@(echo "\t\t\t      |   )   9b _. 88b\033[0m                     ";)
	@(echo "\t\t\t      \`._ \`.   8\`--'888\033[0m                  ";)
	@(echo "\t\t\t       |    \\--'\\   \`-8\033[0m___               ";)
	@(echo "\t\t\t        \\\`-.              \\ ";)
	@(echo "\t\t\t         \`. \ -       _ / <";)
	@(echo "\t\t\t           \ \`---   ___/|_-\\ ";)
	@(echo "\t\t\t             |._      _. |_-|";)
	@(echo "\t\t\t            \\  _     _  /.-\\ ";)
	@(echo "\t\t\t             | -! . !- ||   | ";)
	@(echo "\t\t\t             \\ \"| ! |\" /\\   | ";)
	@(echo "\t\t\t              =oO)X(Oo=  \\  / ";)
	@(echo "\t\t\t       \033[33;5m)\033[31m((\033[0;31m())888888888\033[33m)\033[0m   < \\ ";)
	@(echo "\t\t\t   \033[33;5m)(\033[31m((\033[0;31m))(())d888888888b\033[33m)\033[0m  \\_/ Ojo 98 >";)
	@(echo "\t\t    \033[33;5m)\033[31;5m(())((\033[0;31m))(())(())88888888888)()(())(())(())\033[31;5m(())\033[0m ";)
	@(echo "\t\t    ██████╗ ██████╗ ██████╗ ███████╗    ██╗    ██╗ █████╗ ██████╗ ");
	@(echo "\t\t   ██╔════╝██╔═══██╗██╔══██╗██╔════╝    ██║    ██║██╔══██╗██╔══██╗");
	@(echo "\t\t   ██║     ██║   ██║██████╔╝█████╗      ██║ █╗ ██║███████║██████╔╝");
	@(echo "              (O)  ██║     ██║   ██║██╔══██╗██╔══╝      ██║███╗██║██╔══██║██╔══██╗");
	@(echo "              <M   ╚██████╗╚██████╔╝██║  ██║███████╗    ╚███╔███╔╝██║  ██║██║  ██║");
	@(echo "   o          <M   ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝     ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝  ╚═╝");
	@(echo "  /| ......  /:M\--------------------------------------------------------------------,,,,,,";)
	@(echo "(O)[]XXXXXX[]I:K+}=====<{H}>====================================================------------>";)
	@(echo "  \| ^^^^^^  \:W/--------------------------------------------------------------------''''''";)
	@(echo "   o          <W ";)
	@(echo "              <W";)
	@(echo "              (O)";)

$(LIB) :
	@(cd $(LIB_DIR) && MAKE)

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(OBJ2_DIR) :
	mkdir $(OBJ2_DIR)

$(OBJ3_DIR) :
	mkdir $(OBJ3_DIR)

$(OBJ_DIR)%.o : $(addprefix $(SRC_DIR), %.c) $(INC_FILES)
	@(echo "\033[35m Preparation du terrin \033[31m\t\c")
	@(echo "{\t$@\t}")
	@($(CC) $(FLAGS) -I$(INC) -c -o $@ $< $(EXTRA_FLAGS))
	@(echo "\033[2F\033[2K")

$(OBJ_DIR)%.o : $(addprefix $(SRC2_DIR), %.c) $(INC_FILES)
	@(echo "\033[33m Preparation des armes \033[31m\t\c")
	@(echo "{\t$@\t}")
	@($(CC) $(FLAGS) -I$(INC) -c -o $@ $< $(EXTRA_FLAGS))
	@(echo "\033[2F\033[2K")

$(OBJ_DIR)%.o : $(addprefix $(SRC3_DIR), %.c) $(INC_FILES)
	@(echo "\033[93m Demarage de la retransmition video \033[31m\t\c")
	@(echo "{\t$@\t}")
	@($(CC) $(FLAGS) -I$(INC) -c -o $@ $< $(EXTRA_FLAGS))
	@(echo "\033[2F\033[2K")

clean :
	@(rm -f $(addprefix $(OBJ_DIR), $(OBJ)) $(addprefix $(OBJ_DIR), $(OBJ2)) $(addprefix $(OBJ_DIR), $(OBJ3)))
	@(echo "\033[32m Destruction des infrastructures De l'arène\033[0m")
	@(cd $(LIB_DIR) && MAKE $@)

fclean : clean
	@(rm -f $(NAME))
	@(echo "\033[32m Destruction de l'arène de combat\033[0m")
	@(cd $(LIB_DIR) && MAKE $@)

re : fclean all

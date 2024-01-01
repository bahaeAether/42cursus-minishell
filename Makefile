# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/07 20:06:56 by hnaama            #+#    #+#              #
#    Updated: 2023/12/31 23:26:40 by baboulou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

VPATH = parsing/ execution/ builtin/

SRC_MAIN =	minishell.c frees.c
SRC_PAR =	parsing.c heredoc_expansion.c\
			update_token.c tokenizer.c check_quote.c\
			cmd_check_utils.c cmd_check.c error_handling.c\
			helper.c heredoc.c redirections.c expansion.c\
			expansion_utils.c lexer.c lexer_utils.c
SRC_EXE = 	execution.c builtin_utils.c builtin_utils2.c\
			ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c \
			ft_pwd.c ft_unset.c exec_builtins.c \
			pipes_and_redirections.c error_msgs.c\

			
OBJ = $(addprefix objs/, $(SRC_MAIN:.c=.o) $(SRC_PAR:.c=.o) $(SRC_EXE:.c=.o))



CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -fsanitize=address -g3 #-Wpedantic 

all: $(NAME)

# You must have the envirenment variable HOME set correctly to your home directory. If not, export it or change the $(HOME) below to the absolute path of your home directory 

${NAME}: libft/libft.a $(OBJ) 
	$(CC) $(CFLAGS) -L $(HOME)/readline/lib -l readline -o $(NAME) $(OBJ) -L libft -l ft

objs/%.o: %.c
		@mkdir -p objs
		$(CC) $(CFLAGS) -c $< -o $@

libft/libft.a :
	 make -C libft
	 make bonus -C libft

clean:
		@rm -f $(OBJ) $(OBJ_B)
		@rm -rf objs
		@make clean -C libft

fclean: clean
		@rm -f $(NAME)
		@make fclean -C libft

re: fclean all

readline:
	chmod +x ./readline_script.sh
	sh ./readline_script.sh

push: fclean
		git add . && git commit -m "back up" && git push

.PHONY : all clean fclean re bonus

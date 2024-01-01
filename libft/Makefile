# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hnaama <hnaama@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/23 04:03:36 by hnaama            #+#    #+#              #
#    Updated: 2023/05/25 14:47:44 by hnaama           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

VPATH = get_next_line/ ft_printf/

SRC = ft_atoi.c ft_bzero.c ft_calloc.c\
	ft_isalnum.c ft_isalpha.c ft_isascii.c\
	ft_isdigit.c ft_isprint.c ft_putnbr_fd.c ft_memchr.c\
	ft_memcmp.c ft_memmove.c ft_putendl_fd.c ft_memset.c\
	ft_strchr.c ft_strdup.c ft_itoa.c ft_memcpy.c\
	ft_strjoin.c ft_strlcat.c ft_strmapi.c ft_strlcpy.c\
	ft_strlen.c ft_strncmp.c ft_striteri.c ft_strnstr.c\
	ft_strrchr.c ft_strtrim.c ft_putchar_fd.c ft_substr.c\
	ft_tolower.c ft_toupper.c ft_putstr_fd.c ft_split.c\
	get_next_line.c get_next_line_utils.c ft_printf.c\
	ft_putchar_str.c ft_putnbr_bass.c

SRC_B = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c\
		ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c\
		get_next_line_bonus.c get_next_line_utils_bonus.c

OBJ = $(addprefix objs/, $(SRC:.c=.o))


objs/%.o: %.c
		@mkdir -p objs
		$(CC) $(CFLAGS) -c $< -o $@

OBJ_B = $(addprefix objs/, $(SRC_B:.c=.o))


objs/%.o: %.c
		@mkdir -p objs
		$(CC) $(CFLAGS) -c $< -o $@

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rcs $(NAME) $(OBJ)

bonus: $(OBJ_B)
	@ar -rcs $(NAME) $(OBJ_B)

clean:
	@rm -f $(OBJ) $(OBJ_B)

fclean: clean
	@rm -f $(NAME)
	
re: fclean all
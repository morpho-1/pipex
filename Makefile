# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aylemrab <aylemrab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/07 10:17:34 by aylemrab          #+#    #+#              #
#    Updated: 2023/06/08 10:36:37 by aylemrab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = pipex.c utils.c

OBJS = $(SRCS:.c=.o)

all:$(NAME)

libft_tools/libft.a:
	make -C libft_tools

%.o:%.c pipex.h libft_tools/libft.h
	@$(CC) $(CFLAGS) -c $<

$(NAME):$(OBJS) libft_tools/libft.a
	@$(CC) $(CFLAGS) $(OBJS) libft_tools/libft.a -o $(NAME) 

clean:
	@rm -f $(OBJS)
	@make clean -C libft_tools

fclean: clean 
	@rm -f $(NAME)
	@make fclean -C libft_tools

re: fclean all 

.PHONY: clean fclean re all

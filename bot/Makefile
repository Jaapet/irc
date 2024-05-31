# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edfirmin <edfirmin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 14:02:35 by edfirmin          #+#    #+#              #
#    Updated: 2024/05/31 16:42:07 by edfirmin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.cpp
NAME = bot_irc
CC = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic -g
OBJS = $(SRCS:.cpp=.o)
$(NAME): $(OBJS)
		$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)

all:    $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
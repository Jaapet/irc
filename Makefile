SRCS = main.cpp Server.cpp Session.cpp debug.cpp command.cpp reply.cpp error.cpp Message.cpp utils.cpp
NAME = ircserv
CC = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 #-pedantic -g
OBJS = $(SRCS:.cpp=.o)
$(NAME): $(OBJS)
		$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)

all:    $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
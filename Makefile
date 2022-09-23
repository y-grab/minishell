NAME = minishell

SRCS =  change_line.c change_pwd.c check_arg_or_and.c check_arg.c check_arg2.c check_arg3.c define_cmd.c error.c execution.c execution2.c\
		executor.c ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_quote.c ft_unset.c handle_dollar.c handle_dollar2.c\
		here_doc.c init_cmd.c init_new_cmd.c main.c check_process.c search_in_dir.c signal.c utils.c utils2.c wildcard.c parser.c\
		parser2.c parser3.c

OBJ		=	$(SRCS:%.c=%.o)

LIB		=	libft/libft.a

HEADER	=	minishell.h

CC		=	clang

FLAGS	=	-Wall -Wextra -Werror #-fsanitize=address -g

READLINE = -lreadline

RM		= rm -rf

.PHONY:		all	clean	fclean	re

%.o:		%.c $(HEADER)
			$(CC) $(FLAGS) -I $(HEADER) -c $< -o $@


all:		$(NAME)

$(NAME):	$(LIB) $(OBJ) $(HEADER)
			$(CC) $(FLAGS) $(READLINE) $(OBJ) $(LIB) -o $(NAME)

$(LIB):
			@$(MAKE) -C libft/

clean:
			@$(RM) $(OBJ)
			@$(MAKE) -C libft/ clean

fclean:		clean
			@$(RM) $(NAME)
			@$(MAKE) -C libft/ fclean

re:			fclean all
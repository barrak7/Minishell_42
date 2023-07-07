FILE_C =	Execution/built_in_fun_1.c     Execution/execution_help_1.c   Parsing/help_fun_1.c         Parsing/open_files_utils.c   Execution/signals_term.c \
			Execution/built_in_fun_2.c     Execution/executioner_1.c      Parsing/help_fun_2.c         Parsing/open_files_utils1.c  Parsing/syntax_check.c \
			Execution/envp_management_1.c  Execution/executioner_2.c      Parsing/huge_parser.c        Parsing/open_utils.c         Parsing/syntax_check_utils.c \
			Execution/envp_management_2.c  Execution/executioner_3.c      Parsing/huge_split.c         Parsing/pars_utils1.c        Parsing/token_split.c \
			Execution/envp_management_3.c  Execution/export_1.c           main.c               Parsing/pars_utils2.c        Parsing/token_split_utils.c \
			Parsing/errors.c             Execution/export_2.c           Parsing/open_files.c         Parsing/remove_files.c       Execution/wildcard.c    \
			Parsing/wildcard_utils.c     Parsing/wild_expand.c        Execution/wildcard_help.c      Parsing/better_split.c

FILE_O = $(FILE_C:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra
#-fsanitize=address

NAME = minishell

.SILENT:

all: $(NAME)

$(NAME): $(FILE_O)
	@echo "Building!"
	@Make -C libft/
	@$(CC) $(CFLAGS) $(FILE_O) libft/libft.a -o $(NAME) -L ~/local/lib/ -lreadline
	@echo "Done!!"

clean:
	@rm -f $(FILE_O)
	@make clean -C libft/
	@echo "Done!!"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft/
	@echo "Done!!"

re: fclean all

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:01:29 by hbouabda          #+#    #+#             */
/*   Updated: 2023/04/04 13:28:41 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_wildcard
{
	char				*file_name;
	int					pointer;
	struct s_wildcard	*next;
}						t_wildcard;

typedef struct s_wild_norm
{
	t_wildcard			*files_list;
	t_wildcard			*tmp;
	int					del;
}						t_wild_norm;

typedef struct s_cmds
{
	int					in;
	int					out;
	char				**args;
	char				*heredoc;
	int					doc_expand;
	int					*reds_p;
	int					ambiguious;
	char				*ambi_re;
	struct s_cmds		*next;
}						t_cmds;

typedef struct s_envp
{
	char				*var_name;
	char				*var_content;
	struct s_envp		*next;
	int					equal_sign;
}						t_envp;

typedef struct s_global
{
	t_cmds				*cmds;
	int					exs;
	t_envp				*env;
	int					signaled;
}						t_global;

extern t_global			g_lb;

/*========================= BUILT-IN =========================*/

void					pwd(t_cmds *cmd, int fd, int flag);
void					echo(t_cmds *cmd, int fd, int flag);
void					env(t_cmds *cmd, int fd, int flag);
void					cd(t_cmds *cmd, int fd, int flag);
void					ft_exit(t_cmds *cmd, int fd, int flag);
void					export(t_cmds *cmd, int fd, int flag);
void					unset(t_cmds *cmd, int fd, int flag);

void					rl_replace_line(const char *text, int clear_undo);
int						includes(char *str, char c);
char					**copy_envp(char **envp);
int						ft_strcmp(char *str1, char *str2);
t_envp					*new_node(char *var_line);
t_envp					*get_last_node(t_envp *head);
void					add_back(t_envp **head, t_envp *new);
t_envp					*envp_to_list(char **envp);
void					delete_node(t_envp **list_envp, char *var_name);
t_envp					*sort_envp(t_envp *list_envp);
void					initial_value(t_envp *envp);
void					clear_list(t_envp **list_envp);
char					**ft_join_elem_to_matrix(char **matrix, char *elem);
int						valid_flag_n(char *str);
int						ft_check_val(char *str);
int						is_built_in(t_cmds *cmd);
int						export_valid_varname(char *str, int flag);
char					*ft_getenv(char *var_name);
char					*check_access(char *cmd);
int						get_list_len(t_envp *list_envp);
char					**list_to_env(void);
void					free_matrix(char **matrix);
void					execute_cmds(t_cmds *cmds);
int						export_helper(t_envp **envp, char *var);

/*========================= ENV =========================*/

int						cp_env(char *dest, char *src, int *l, int q);
int						expand_len(char *str);
int						skip_limiter(char *str);
int						env_len(char *str, int *l, int *s, int q);
char					*get_env(char *str, char c, int q);
int						is_token(char *str);
int						huge_parser(char *str);
int						ft_copy(char *dst, char *src, int len);
int						is_expandable(char c, int i);
void					huge_split(char *str);
int						syntax_check(char *str);
void					token_split(t_cmds *cmds);
int						is_redirection(char *str);
int						skip_quotes(char *str);
void					open_files(void);
void					remove_files(void);
int						includes_v2(char *str, char c);
void					sigint_handler(int signum);
void					sigint_handler_2(int signum);
void					sigint_handler_3(int signum);
void					setup_term(void);
void					childs_bloc_in_multi(int i, int pipefd[2][2],
							t_cmds *cmd);
void					exit_fun(int status, char *cmd);
void					first_child(int *pipefd1, t_cmds *cmd);
void					last_child(int *pipefd1, t_cmds *cmd);
void					multi_pipe(t_cmds *cmd, int pipefd[2][2]);
void					parent_bloc(int pipefd[2][2], int fk2);
int						set_exit(char *err, int exs);
int						check_endl(int i, char *str);
int						check_pipes(char *str);
int						check_quotes(char *str);
int						check_tokens(char *str);
void					check_heredoc_count(char *str);
void					malloc_err(void *ptr);
char					*expand(char *str);
int						quotes_len(char *str, int *len);
void					fd_error(int fd);
int						files_error(int fd, char *file);
void					create_herdoc(t_cmds *cmds);
char					*read_doc_app(char *buffer, char *limiter, int fd);
char					*heredoc_expand(char *str);
void					heredoc_handler(int a);
void					expand_doc(t_cmds *cmds);
void					read_doc(t_cmds *cmds);
void					open_out(t_cmds *cmds, char *file, int *br);
void					open_append(t_cmds *cmds, char *file, int *br);
void					copy_in_quotes(char *dst, char *src, int *p, int *p1);
int						token_split_len(char *str, int start);
void					token_split_count(char *str, int *c);
void					ft_printf(char *s1, char *s2, char *s3, int fd);
t_wildcard				*wild_card(char *str);
char					*wild_expand(char *str);
void					delete_list_wildcard(t_wildcard **head);
char					*join_files(t_wildcard *files);
char					*expand_wild(char *str);
char					*get_expanded(char *str, int start, int end, \
							int is_doc);
int						skip_spaces(char *str);
t_wildcard				*wild_new_node(char *file_name);
void					add_back_wildcard(t_wildcard **head, t_wildcard *new);
void					delete_node_wildcard(t_wildcard **head,
							t_wildcard *to_delete);
void					delete_list_wildcard(t_wildcard **head);
t_wildcard				*create_wildcard_list(char *str);
char					*is_var_set(char *var);
char					**better_split(char const *s, char c);
int						fail(char *str);
void					check_doc_exit(void);
char					*ft_lower(char *str);
int						ambiguity_re(char *str);

#endif

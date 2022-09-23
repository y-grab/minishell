/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:02:19 by gjohana           #+#    #+#             */
/*   Updated: 2022/07/02 12:22:16 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <sys/wait.h>

# define SYNTAX_ERROR " Minishell:\
 syntax error: unexpected end of file\n"
# define SEP	"\t\n\r\a "

typedef struct s_cmd
{
	int				use;
	int				t_type;
	int				in;
	int				out;
	char			**here_doc;
	char			**rid;
	int				*type;
	char			**cmd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_all
{
	char				*line[100000000];
	int					line_c;
	int					cmd;
	int					red;
	char				*d_name;
	char				*old_arg;
	int					last_in;
	pid_t				pid;
	pid_t				pid_cmd;
	int					nb_cmd;
	int					no_init;
	char				*herd;
	int					pip;
	int					p;
	int					exit_code;
	char				**argv;
	char				**exec_envp;
	int					orand;
	int					heredoc;
	struct sigaction	sig;
	t_lstk				*local;
	t_lstk				*env;
}	t_all;

t_all	g_all;

char				*process_backslash(char *str, int *i);
int					is_bslash(char *s, int i);
void				syn_error_qoutes(char *str, int i, int *sq, int *dq);
int					syn_backslash(char *str);
int					syn_backslash_exit(void);
int					syn_error_util(char *str, char a, int *sq, int *dq);
int					syn_error_check(char *str, char a);
char				*parser(char *str);
void				copy_env(char **envp);
int					ft_env(char *s, int fd_out);
int					ft_export(char **cmd, t_lstk **envp, int fd, int flag);
int					find_equal(char *s);
t_lstk				*find_key2(char *key, t_lstk *env);
void				init_local(void);
void				signals_handler(int sign);
void				signal_child(int sign);
int					valid_brackets(char *s);
char				*check_unclosed(char *arg);
int					check_pipe(char *str, int len);
int					check_quote(char *str);
int					check_or_and(char *str);
int					ft_echo(char **cmd, int fd_out);
char				**env_to_str(t_lstk *lst);
void				ft_sort_arry(char **env);
void				ft_free(char **s);
char				*skip_qoute(char *str);
void				p_error(char c);
void				check_space(char *str);
int					check_space_and(char *str);
int					check_space_pipe(char *str);
int					check_line_pipe(char *str);
char				*ft_quote(char *line);
char				*ft_pipe(char *line);
int					skip_qoute_inside(char *str);
char				*ft_or_and(char *line);
void				executor(char	*line);
void				executor2(char *line);
char				**ft_split_shell(char *l, char no_splt);
t_cmd				*init_cmd(void);
int					pars_error(char **s);
int					check_cmd_flag(t_cmd *cmd, char **s);
void				init_new_cmd(t_cmd *new, char **s);
void				add_back_node(t_cmd **lst, t_cmd *new);
void				ft_free_list(t_cmd **lst);
char				*change_line(char *s);
void				clear_line(char *arg);
char				*del_quote(char *str);
void				del_brackets(char *str);
char				*handle_dollar(char *l);
char				*handle_dollar2(char *l);
void				wildcard(char *ll);
char				*change_wildcard2(char *s);
char				*find_key(char *key, t_lstk *env);
void				ft_norm5(int *i, char *l, int *in_dquote);
void				f1(char **line, char *l, int *ll, int *r);
void				f2(char **line, char *l, int *ll, int *r);
void				f3(char **line, char *l, int *ll, int *r);
int					search_in_dir(char *d, char **pfix_sfix, char **n_f, int l);
int					is_matching(char *dir, char *to_search);
int					define_cmd(t_cmd *cmd);
int					in_file(t_cmd *cmd, char *s);
int					errors_return_red(char *s, t_cmd *cmd);
int					errors_return(char *s);
int					appand_file(t_cmd *cmd, char *s);
int					out_file(t_cmd *cmd, char *s);
int					here_doc(t_cmd *cmd, char *limiter);
char				*del_quote2(char *str);
int					execution(t_cmd *cmd);
char				**list_to_str(t_lstk *lst);
int					check_path(char **str, t_lstk *path);
int					check_blt(char *cmd);
int					exec_blt(t_cmd *cmd);
int					ft_cd(char *path);
void				change_pwd(void);
void				change_old_pwd(char *s);
int					ft_pwd(char *p, int fd_out);
int					ft_exit(char **cmd);
int					ft_unset(char **cmd);
int					chaild_wait(int up_to);
void				ft_norm2(char *line, int *a);
void				pr_error(void);
char				*join_p(char *p, char **s_path, int i, char **str);
void				print_here2(void);

#endif
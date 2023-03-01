/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:11:27 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/11 11:15:52 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <limits.h>

extern long long int	g_code;

typedef struct s_here_handler
{
	int		**pipe_fd;
	int		pid;
	int		size;
	char	**result;
	int		i;
}	t_here_handler;

typedef struct s_tmp
{
	DIR				*folder;
	struct dirent	*entry;
	int				read;
	int				no_match;
}	t_tmp;

typedef struct s_wild_args
{
	DIR				*folder;
	struct dirent	*entry;
	int				no_match;
	int				res_match;
}	t_wild_args;

typedef struct s_cmd_args
{
	char			**cmd_wild;
	char			*cur_exec;
	int				index;
	int				args_nbr;
}	t_cmd_args;

typedef struct s_cmd_path
{
	int		index1;
	int		path_len;
	int		index2;
	char	*save_cmd;
}	t_cmd_path;

typedef struct s_wild_handler
{
	char	*chunk;
	char	*str;
	int		chunk_type;
	int		file_match;
	int		ind1;
	int		ind2;
}	t_wild_handler;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

typedef struct s_db_list
{
	t_token	*first;
	t_token	*last;
	t_token	*new_env;
	int		lenght;
}	t_db_list;

typedef struct s_extension
{
	char				*ancient;
	char				*new;
	struct s_extension	*previous;
}	t_extension;

typedef struct s_p_exec
{
	int					is_built_in;
	int					denied;
	int					exit_code;
	char				*infile;
	char				*outfile;
	char				*app_outfile;
	int					cmds_nbr;
	int					save_cmds_nbr;
	int					args_nbr;
	int					s_in;
	int					s_out;
	int					input;
	int					output;
	int					pipe_fd[2];
	int					prev_pipe_in;
	int					here_pipe_fd[2];
	char				**here;
	int					here_index;
	int					first_cmd;
	char				*cmd;
	char				*path;
	char				*bin;
	char				**args;
	char				***env;
	int					here_doc;
	int					here_inf;
	struct s_minishell	*gate;
	int					*envi;
}	t_p_exec;

typedef struct s_minishell
{
	char				*line;
	char				*result;
	t_token				*token;
	t_db_list			*info;
	t_extension			*extension;
	int					quote;
	char				***env;
	int					grammar;
	int					here_doc;
	char				**here;
	t_p_exec			*suppressor;
	int					envi;
	int					check;
	int					erasemn;
	int					ishd;
}	t_minishell;

void					initialize_args_handler(t_p_exec *p_exec);
int						alpha_sort(char *str1, char *str2);
void					initialize_tmp_array(t_tmp *tmp,
							char **tmp_arr, int args_nbr);
void					initialize_cmd_path(t_cmd_path	*cmd_path, char *path);
void					dispatcher(t_token **token, t_p_exec *p_exec);
void					exit_execution3(t_p_exec *p_exec);
void					exit_execution2(t_p_exec *p_exec);
void					exit_execution(t_p_exec *p_exec);
void					echo_execution(t_p_exec *p_exec);
void					pwd_execution(t_p_exec *p_exec);
void					env_execution(t_p_exec *p_exec);
void					unset_execution(t_p_exec *p_exec);
void					export_execution(t_token **token, t_p_exec *p_exec);
void					cd_execution(t_p_exec *p_exec);
void					free_args(char **args, int args_nbr);
size_t					ft_strlen(const char *s);
int						wildcard_match(char *file_name, char *wildcard);
int						match_pattern(char **file_name, char *chunk,
							int chunk_type);
int						extract_pattern(char **chunk, int chunk_type);
void					determine_chunk_type(char *chunk, int *chunk_type);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					determine_chunk(char *wildcard, int *index2);
void					restore_fd(int save_input, int save_output);
int						move_next_cmds_pipe(t_token **token);
int						handle_execution(t_token **token, t_p_exec *p_exec,
							int *pid);
int						count_wild_args(char *wildcard, int *args_nbr,
							t_wild_args wd_args);
void					handle_error(char *cmd, char **args, int args_nbr);
void					determine_cmd_path(t_p_exec *p_exec);
void					determine_cmd_no_path(t_p_exec *p_exec);
void					determine_path(char *cmd, char **path, char **env);
void					free_me_from_minishell(t_p_exec *p_exec, int sortie,
							void *pointer, int force);
void					echo(char **str);
char					**unset_env(char *str, char **env, int *envi);
int						export(t_token **token, t_p_exec *p_exec);
int						handle_execve(t_p_exec *p_exec);
int						inf_outf_redirections(t_token *token, t_p_exec *p_exec);
int						pipe_redirections(int pipe_fd[2], int *input,
							int *output, int first_cmd);
int						handle_wild_args(char *wildcard, char **args,
							int *index);
char					*cmd_to_args(t_token *token, char *cmd,
							t_p_exec *p_exec);
int						count_args(t_token *token, int *args_nbr);
int						is_a_directory(char *str);
int						ft_strncmp(char *s1, char *s2, unsigned int n);
void					write_here_doc(int here_pipe_fd_out,
							char **here_doc_tab);
int						find_operator(t_token **token);
int						handle_continue(int status, int operator);
int						move_next_cmds(t_token **token, int status);
int						execute_commands(t_token *token, t_p_exec *p_exec);
int						execute_line(t_minishell *minishell);
void					determine_pipe_num(t_token *token, t_p_exec *p_exec);

//REDIRECTION2
int						inf_error(int *exit_code, int *input, int tmp_input);
int						out_error(t_p_exec *p_exec, int tmp_output);

//UTILS_1		
void					ft_putstr_fd(char const *s, int fd);
int						arg_is_numeric(char *str);
int						ft_itoa_size(int n);
char					*ft_itoa(int nbr);

//UTILS_2		
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strcmpe(char *s1, char *s2);
int						ft_isdigit(int c);
int						ft_isalpha(int c);
int						ft_strncmp(char *s1, char *s2, unsigned int n);

//UTILS_3		
void					ft_putchar(char c);
void					ft_putstr(char *str);
void					ft_putendl(char *s);
size_t					ft_strlen(const char *s);
void					deletestr(int delete, char *s1, char *s2);
char					*custom_strjoin(char *s1, char *s2, int delete);

//UTILS_4		
char					*ft_substr(char *s, unsigned int start, size_t len);
char					*ft_strdup(const char *s);
void					add_char(char c, char *str);
void					rec_itoa(long nb, char *result);
int						ft_getlen(int nbr);

//LIST_1		
t_token					*push_empty_list(t_db_list *info, char *str, int type);
t_token					*push_full_list(t_db_list *info, char *str, int type);
t_token					*push_list(t_db_list *info, char *str, int type);
t_db_list				*init_list(t_db_list *info);
void					free_me_from_minishell(t_p_exec *p_exec, int sortie,
							void *pointer, int force);

//LIST_2		
int						type(int type);
int						ft_grammar(t_token *token);
int						verif_quote(char *str);
void					free_me_from_minishell_end(t_minishell *minishell);

//BUILDIN_1		
int						built_in(t_p_exec *pipe_exec);
char					**export_env(char *str, char **env, int *envi);
int						*free_envi(int *envi, char **env);
char					*check_extension(char *str, t_minishell *minishell);
char					**inside_export_env(int i, char *same,
							char **new_env, char *str);

//BUILDIN_2		
int						export(t_token **token, t_p_exec *pipe_exec);
char					**unset_env(char *str, char **env, int *envi);
int						print_pwd(t_p_exec *p_exec);
int						check_arg_echo(char *str);

//BUILDIN_3		
void					sort_env(char **env);
void					echo(char **str);
char					*already_in_env(char *str, char **env);
char					**inside_sort_env(char **env, int j, int len_env,
							char **result);

//HANDLE_HERE_DO		C
char					**here_doc(t_token *token, t_token *start,
							struct sigaction *sig, t_minishell *minishell);
char					*put_here_doc(t_token *token);
void					free_here_doc(t_minishell *minishell);
int						redirection(t_minishell *minishell, int *i,
							int type, char *result);

//HANDLE_HERE_DO		C2
char					*read_pipe_fd(int *fds, char *str, int time);
void					create_here_doc(t_token *token, t_token *start,
							t_here_handler here_handler, struct sigaction *sig);
int						*generate_pipe_here(void);

//HANDLE_TOKENS		
int						simple_pipe(t_minishell *minishell, int *i,
							char *result);
int						eperluette(t_minishell *minishell, int *i,
							char *result);
int						parenthese(t_minishell *minishell, int *i,
							char *result);
int						double_operator(t_minishell *minishell, int *i,
							int type, char *result);
int						is_infile_or_outfile(t_minishell *minishell,
							int *i, char *result);

//HANDLE_SPE		
char					*ft_34(t_minishell *minishell, int *i);
char					*ft_39(t_minishell *minishell, int *i);
int						verification(char **result,
							t_minishell *minishell, int *i);
char					*dollars_sign(t_minishell *minishell,
							int *i, int quote);
int						not_token(char c);

//HANDLE_PARSING		
int						is_wildcard(char *str, int a, t_minishell *minishell);
int						inside_regular(t_minishell *minishell, int *i,
							char **result);
int						regularstr(t_minishell *minishell, int *i,
							char *result);
int						inside_parse_line(t_minishell *minishell,
							int *i, char *result);
int						parse_line(t_minishell *minishell, int i);
int						is_13(char *result);

//MAIN		
int						main(int argc, char *argv[], char *env[]);
int						prepare_handler(t_minishell *minishell,
							struct sigaction *sig);
t_db_list				*init_minishell(t_minishell *minishell, char **env[],
							struct sigaction *sig);
void					handler(int signal);
void					handler_infinite_command(int signal);
int						prepare_readline(int argc, char **argv,
							t_minishell *minishell,
							struct sigaction *sig);

//MAIN_EXTENDED		
int						is_a_directory(char *str);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					free_args(char **args, int args_nbr);
void					*ft_memset(void *s, int c, size_t n);

//HANDLERS		
void					launch_infinite(struct sigaction *sig);
void					launch_classic(struct sigaction *sig);
void					launch_default(struct sigaction *sig);
signed long long int	ft_atoi(const char *str);

//FONCTION_SUPPLIER
int						not_34(char *str, int i);
void					determine_size(t_token *token, int *size);
char					*create_result(void);

#endif
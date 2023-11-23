/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 01:34:44 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/21 18:46:29 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libs/Libft/libft.h" 

extern int	g_error;

typedef struct s_envp
{
	char	**env_array;
	int		env_len;
}	t_envp;

typedef struct s_utils
{
	int	n_flag;
	int	quote_flag;
	int	cnt_pipe;
	int	split_start;
	int	split_last;
}	t_utils;

// init
t_envp	*init_envp(char **envp);
t_envp	*init(char **envp);

// envp_utils
int		env_len(char **envp);
int		ft_var_is_in_env(char *env_var, char *my_var);
int		get_index(char *var_name, t_envp *s_envp);
void	realloc_env_array(t_envp *s_envp);
char	**sort_envp(char **envp);
void	print_export(t_envp *s_envp);

// signals
void	ft_signals(int signum);

// parsing_command
void	parsing_command(char *str, t_envp *s_envp);

// utils
int		count(char *str, char c);
char	*sub_redir(char **str, int i);

// exec_simple
void	run_child(char **parse, t_envp *s_envp);
void	run_simple(char *str, t_envp *s_envp);

// find_path
char	*check_path(char *command, int i);
char	*find_path(char *command);

// free
void	ft_free_str(char **str);
void	ft_free_list(t_list **list);
void	ft_free_env(t_envp *s_envp);
void	ft_lstdelete(t_list *lst);

// is_builtin
int		is_builtin(char *temp);
void	run_builtin(char *str, t_envp *s_envp);

// is_echo
int		is_echo(char *str);
char	*remove_quotes(char *str, int i);
int		count_quotes(char *str);	

// run cd
void	run_cd(char *temp);

// export
void	run_export(char *str, t_envp *s_envp);
void	run_export2(char *sub2, t_envp *s_envp);
void	export_with_equal(char **str, t_envp *s_envp, int i);
void	ft_export(char *var_name, char *var_val, t_envp *s_envp);


// export_utils
int	ft_strlen_equal(char *str);

// export_exec
void	export_exec_exist(char *var_name, char *var_val, t_envp *s_envp, int i);
void	export_exec_non_existent(char *var_name, char *var_val,	
			t_envp *s_envp, int i);

// run env
void	run_env(char **env_array);

// run pwd
void	run_pwd(char *temp);

// echo
void	run_echo(char *str, t_envp *s_envp);
void	echo_management(char *str, t_utils utils, t_envp *s_envp);
// echo_utils
int		check_flag_n(char *str);
void	exec_echo_without_n(char *str, t_envp *s_envp);
void	exec_echo_with_n(char *str, t_envp *s_envp);
void	print_echo_single_quote(char *str, int *i);
void	print_echo_double_quote(char *str, int *i);
int		echo_dollar_env(char *str, int *i, t_envp *s_envp);

// check_quotes
int		check_quotes(char *str, t_utils utils);

//unset
void	run_unset(char *str, t_envp *s_envp);

// redir
void	run_redir(char *str, t_envp *s_envp);
int		redir_in(char **str, int i, t_envp *s_envp);
int		redir_out(char **str, int i, t_envp *s_envp);
void	redir2_out_handle(char **str, int i, t_envp *s_envp);
void	redir_out_handle(char **str, int i, t_envp *s_envp);
int		check_another_redir(char **str, int i);
void	redir2_in_handle(char **str, int i, t_envp *s_envp);
void	redir_in_handle(char **str, int i, t_envp *s_envp);
void	mixed_redir(char *str, char *temp, int fd, t_envp *s_envp);
void	mixed_redir2(char *str, char *temp, int fd, t_envp *s_envp);
void	here_doc(char *file, char *eof);
void	exec_dir(char *str, int fd, int i, t_envp *s_envp);
void	exec_redir(char *str, int fd, int new_fd, t_envp *s_envp);

// lst
t_list	**add_list(char **str, t_list **mini);

// pipe
void	run_pipe(char *str, int n_pipe, t_envp *s_envp);
void	pipe_handler(t_list **mini, int countpipe, t_envp *s_envp);
void	exec_pipe(int *fd, int j, t_list *temp, t_envp *s_envp);

#endif
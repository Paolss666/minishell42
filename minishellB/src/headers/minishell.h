/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:58:13 by npaolett          #+#    #+#             */
/*   Updated: 2024/01/08 20:36:39 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft/libft.h"
# include "pipex.h"
# include <errno.h>
# include <math.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define EXIT_FAILURE 1
# define RESET_COLOR "\001\033[0m\002"
# define COLOR_VIOLET "\001\033[0;35m\002"
# define COLOR_RED "\001\033[1;31m\002"
# define STDIN 0
# define STDOUT 1
# define INFILE 0
# define OUTFILE 1

extern int	g_exit_status; 

// readline --> read a line from the terminal and return it , using prompt (char
		// * prompt<-----
//

// typedef struct s_pipex
// {
// 	char	**envp;
// 	char	**cmd;
// 	char	*fd_infile;
// 	char	*fd_outfile;
// 	int		fd[2];
// 	int		prev;
// 	int		nmbr_mcd;
// 	pid_t	pid[1024];
// 	int		here_doc;
// }			t_pipex;


// ------ commande -- //

typedef struct s_cmd
{
	char			*cmd;
	int				count;
	struct s_cmd	*next;
}					t_cmd;

//--------- double data pour split = dans la variable et utiliser export
// char *path et char *path_split avec =


// typedef struct 	s_pipe
// {
// 	char		*path;
// 	int			fd[2];
// 	pid_t		pid[1024];
// 	char		*cmd;
// 	int			pipe;
// 	int			size;
// 	char		*commande_split;
// 	s_cmd		*to_pars;
// }				t_pipe;


typedef struct s_minishell
{
	char	*line;
	int		fd[2];
	pid_t	pid[1024];
	struct s_envp	*enviroment;
	struct s_cmd	*to_pars;
	struct s_exp	*export;
}			t_minishell;


typedef struct s_cd
{
	char			*path;
	int				index;
	struct s_cd		*next;
}					t_cd;

typedef struct 	s_envp
{
	char			*path;
	char			*name;
	char			*value;
	struct s_envp 	*next;
}					t_envp;


typedef struct 	s_exp
{
	char			*path;
	char			*name;
	char			*value;
	struct s_exp 	*next;
}					t_exp;

// ----------- ERRORI --------------- //
void			freeList(t_cmd *head);
void 			free_list_to_pars(t_cmd *to_pars);
void			ft_error_commande_not_to_pars(t_cmd *to_pars);
// ----------- PARSING --------------//
t_cmd				*add_cmd_list(t_cmd *list, char **commande_split, char *line);
int					join_found_flag(t_cmd **to_pars);
char				*display_prompt(void);
void				commande_split_toParse(char **commande_split, char *line);
char 				***split_commands(t_cmd *to_pars);

// ----------- PIPE--------------//
//
char 				***found_pipw_for_parse_commands(t_cmd *to_pars);
void				child(t_cmd *to_pars, char **enviroment, int i, char *get_good_path, int tmp_fd, int *fd);
void				redirection(int *fd, int tmp_fd, int i, int n_pipe);
void				parent(int *fd, int i, int tmp_fd);
/* char				***division_en_pipe(t_cmd *to_pars); */
/* int					ft_pipex(t_cmd *to_pars, int size,  t_envp *enviroment, char **commande_split); */
/* int exec(t_cmd *to_pars, t_envp *enviroment); */
t_pipex	*ft_init_stack(t_cmd *to_pars, int ac, char **av);
int     ft_execve(t_cmd *to_pars, t_envp *enviroment);
char 				**envp_list_to_new_env(t_envp *enviroment);
char				*ft_good_path_access(t_cmd	*to_pars, t_envp *enviroment);
// void		ft_init_stack(stack, size, &to_pars, commande_split);

// ------------ BUILDING ----------- // 
int					ft_pwd(t_cmd *to_pars);
int					ft_cd(t_cmd *to_pars);
int     			found_export(t_cmd *to_pars);
int					found_unset(t_cmd *to_pars);
int					found_exit(t_cmd *to_pars);
// int					print_pwd(t_envp *envp);
int					found_echo(t_cmd *to_pars);
int					ft_envp(t_cmd *to_pars);
int					found_count_pipe(t_cmd *cmd);
int					valid_variable_char(char c);
t_envp				*found_and_add_env(char **env, t_envp *enviroment);
void				found_cd_pwd_update(t_cmd *to_pars, t_envp *enviroment, t_exp *export);
/* void				add_export_env(t_cmd *to_pars, t_envp **enviroment); */
void				found_dollar_print_variable(t_cmd *to_pars, t_envp *enviroment);
void				logic_print_variable(int start, int	i, t_envp *enviroment, t_cmd *arg_cmd);
void				add_export_env(t_cmd *to_pars, t_envp **enviroment, t_exp **export);
t_exp				*add_env_with_export(t_envp *enviroment);
void    			unset_delete_variable(t_cmd *to_pars, t_envp **enviroment, t_exp **export);
char 				*ft_strcpy(char *dest, const char *src, size_t size);
void				ft_echo(t_cmd	*to_pars);
void				print_list_envp(t_envp *head);
void				print_export_list(t_exp *export);
void 				ft_swap(t_exp *a, t_exp *b);
void				export_env_sort(t_exp *exp_env);
// ------------ ERROR SYNTAX ----------- // 
void    			ft_exit(t_cmd   *to_pars);
int					error_manager(char *str);
int					ft_error_case_1(char c);
int					ft_error_blank(char *str);
int					ft_error_shift_operator(char *str);
int					ft_error_directory3(char *str);
int					ft_error_pipe(char *str);
int					ft_error_operand(char *str);
char*				epur_str(char *to_epur);
int					ft_count_sign(char *str, char c);
int					ft_error_parenthesis(char *str);
int					ft_error_semicol(char *str);
int					ft_error_stx(char *str);


#endif
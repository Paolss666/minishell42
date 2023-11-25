/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:56:10 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/25 11:12:45 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft/libft.h"
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

// readline --> read a line from the terminal and return it , using prompt (char
		// * prompt<-----
//
typedef struct s_mshell
{
	char			*commande;
	char			**envp;
	char			*fd_infile;
	char			*fd_outfile;
	int				fd[2];
	pid_t			pid[1024];
}					t_mshell;

// ------ commande -- //

typedef struct s_cmd
{
	char			*cmd;
	struct s_cmd	*next;
}					t_cmd;

//--------- double data pour split = dans la variable et utiliser export
// char *path et char *path_split avec =

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


// ----------- PARSING --------------//
t_cmd				*add_cmd_list(t_cmd *list, char **commande_split, char *line);
void				join_found_flag(t_cmd **to_pars);
char				*display_prompt(void);
void				commande_split_toParse(char **commande_split, char *line);

char 	*ft_strcpy(char *dest, const char *src, size_t size);
// ------------ BUILDING ----------- // 
int					ft_pwd(t_cmd *to_pars);
int					ft_cd(t_cmd *to_pars);
int     			found_export(t_cmd *to_pars);
int					found_unset(t_cmd *to_pars);
int					print_pwd(t_envp *envp);
int					found_echo(t_cmd *to_pars);
int					ft_envp(t_cmd *to_pars);
int					found_pipe(t_cmd *cmd);
t_envp				*found_and_add_env(char **env, t_envp *enviroment);
/* void				add_export_env(t_cmd *to_pars, t_envp **enviroment); */
void	add_export_env(t_cmd *to_pars, t_envp **enviroment, t_exp **export);
t_exp				*add_env_with_export(t_envp *enviroment);
void    			unset_delete_variable(t_cmd *to_pars, t_envp **enviroment);
char 				*ft_strcpy(char *dest, const char *src, size_t size);
void				print_list_envp(t_envp *head);
void				print_export_list(t_exp *export);
void 				ft_swap(t_exp *a, t_exp *b);
void				export_env_sort(t_exp *exp_env);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:33:51 by npaolett          #+#    #+#             */
/*   Updated: 2024/01/07 14:39:29 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int     ft_execve(t_cmd *to_pars, t_envp *enviroment, char *line)
{
    char		*good_path_access;
    char		**new_enviroment;
	char		**avant_pipe = NULL;
    pid_t		pid;
    int         status;
	int			fd[2];


	if (found_count_pipe(to_pars))
	{
		if (pipe(fd) == -1)
			perror("pipe error");
		avant_pipe = division_en_pipe(to_pars);
	}
    pid = fork();
	if (pid == 0)
	{
		// ft_execve(to_pars, enviroment, line);
		new_enviroment = envp_list_to_new_env(enviroment);
		good_path_access = ft_good_path_access(to_pars, enviroment);
		if (!good_path_access)
			return (ft_error_commande_not_to_pars(to_pars), 0);
		if (found_count_pipe(to_pars) && (dup2(fd[1], 1) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
		if (avant_pipe)
		{
			execve(good_path_access, avant_pipe, new_enviroment);
			perror("execve");
		}
		else
		{
			execve(good_path_access, ft_split(line, ' '), new_enviroment);
			perror("execve");
		}
/* 		ft_free_tab(new_enviroment); */
	}
	if (pid)
	{
		int i = 0;
		int p = found_count_pipe(to_pars);
		while(i <=  p)
		{
			if (dup2(fd[0], 0) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1)
				perror("fail dup close");
			if (waitpid(pid, &status, 0) == -1)
				perror("waitpid error");
			i++;
		}
	}
    return (0);
}


char  **division_en_pipe(t_cmd *to_pars)
{
    t_cmd *prev;
    char **commande_div_en_pipe = NULL;
    int i = 0;

	prev = to_pars;
    while(to_pars)
    {
        if (ft_strcmp(to_pars->cmd,"|") == 0)
			break;
		i++;
		to_pars = to_pars->next;
	}
	commande_div_en_pipe = (char **)malloc(sizeof(char *) * (i + 1));
	if (!commande_div_en_pipe)
		return(NULL);
	while(prev && i)
	{
		commande_div_en_pipe[i--] = ft_strdup(prev->cmd);
/* 		free(prev->cmd); */
		prev = prev->next;
	}
/* 	free(prev); */
    return (commande_div_en_pipe);
}

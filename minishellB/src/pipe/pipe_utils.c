/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:18:52 by npaolett          #+#    #+#             */
/*   Updated: 2024/01/04 16:37:51 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


int	open_file(t_pipex *stack, int file)
{
	int	fd;

	fd = 0;
	if (file == 0)
		fd = fd_in_open(fd, stack);
	if (file == stack->nmbr_mcd - 1)
		fd = fd_out_open(fd, stack);
	return (fd);
}

void	ft_redirect(t_pipex *stack, int i)
{
	int	fd;

	if (i == 0)
	{
		fd = open_file(stack, i);
		dup2(fd, 0);
		close(fd);
	}
	if (i == stack->nmbr_mcd - 1)
	{
		fd = open_file(stack, i);
		dup2(fd, 1);
		close(fd);
	}
	if (i != 0)
	{
		dup2(stack->prev, 0);
		close(stack->prev);
	}
	if (i != stack->nmbr_mcd - 1)
		dup2(stack->fd[1], 1);
	close(stack->fd[0]);
	close(stack->fd[1]);
}

char	*cmd_with_good_path(t_pipex *stack, char **cmd)
{
	int		i;
	char	*path_part;
	char	*exec;

	i = -1;
	while (stack->envp[++i])
	{
		path_part = ft_strjoin(stack->envp[i], "/");
		if (!path_part)
			return (free(path_part), NULL);
		exec = ft_strjoin(path_part, cmd[0]);
		if (!exec)
			return (free(exec), NULL);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
		free(exec);
	}
	return (ft_free_tab(stack->envp), NULL);
}

char	*get_good_path(t_pipex *stack, char **cmd, char **env)
{
	char	*exec;

	if (cmd[0][0] == '/')
	{
		exec = cmd[0];
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
		return (NULL);
	}
	stack->envp = ft_split(find_path(env), ':');
	if (!stack->envp)
		return (ft_free_tab(stack->envp), NULL);
	exec = cmd_with_good_path(stack, cmd);
	return (exec);
}

char	*find_path(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

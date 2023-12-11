/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:54:16 by npaolett          #+#    #+#             */
/*   Updated: 2023/12/11 16:25:29 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	found_pipe(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		if (ft_strncmp(cmd->cmd, "|", ft_strlen("|")) == 0)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

void	ft_child_process(t_pipex *stack, int i, t_envp *enviromet)
{
	char	*good_path;
	char	**s_cmd;

	ft_redirect(stack, i);
	if (ft_strcmpchr(stack->cmd[i], ' ') == 0)
		s_cmd = ft_split(stack->cmd[i], '\0');
	else
		s_cmd = ft_split(stack->cmd[i], ' ');
	if (!s_cmd[0] || !s_cmd)
		ft_error_split(stack, s_cmd);
	good_path = get_good_path(stack, s_cmd, enviromet);
	if (!good_path)
		ft_error_path(stack, s_cmd, good_path, i);
	execve(good_path, s_cmd, enviromet);
	perror("execve");
	ft_free_tab(s_cmd);
	free(good_path);
	free(stack);
	exit(1);
}

void	parent_process(t_pipex *stack, int i)
{
	close(stack->fd[1]);
	if (i)
		close(stack->prev);
	stack->prev = stack->fd[0];
}

void	exec_pipes(t_pipex *stack, char **envp)
{
	int	i;
	int	status;

	i = -1;
	if (!envp)
		return (ft_free_tab(envp), exit(1));
	while (++i < stack->nmbr_mcd)
	{
		if (pipe(stack->fd) == -1)
			perror("pipe error");
		stack->pid[i] = fork();
		if (stack->pid[i] == -1)
			perror("fork err");
		if (stack->pid[i] == 0)
			ft_child_process(stack, i, envp);
		else
			parent_process(stack, i);
	}
	i = 0;
	while (i < stack->nmbr_mcd)
		if (waitpid(stack->pid[i++], &status, 0) == -1)
			perror("waitpid error");
	return ;
}

int	ft_pipex(t_cmd *to_pars, t_envp *envp)
{
	t_pipex *stack;
	
	if (found_pipe(to_pars))
	{	
		stack = (t_pipex *)malloc(sizeof(t_pipex));
		if (!stack)
			return (free(stack), 0);
		stack->here_doc = 0;
		// if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0
		// 	&& ac >= 6)
		// {
		// 	ft_here_doc(stack, av[2]);
		// 	stack->here_doc = 1;
		// 	ac -= 1;
		// 	av += 1;
		// }
		ft_init_stack(stack, to_pars);
		exec_pipes(stack, envp);
		close(stack->fd[0]);
		free(stack);
		unlink("/tmp/here_doc");
		return (1);
	}
	return (0);
}

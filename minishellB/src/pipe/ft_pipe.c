/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:54:16 by npaolett          #+#    #+#             */
/*   Updated: 2024/01/08 16:01:30 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/pipex.h"

int	found_count_pipe(t_cmd *cmd)
{
	int	pipe;

	pipe = 0;
	while (cmd != NULL)
	{
		if (ft_strncmp(cmd->cmd, "|", ft_strlen("|")) == 0)
			pipe++;
		cmd = cmd->next;
	}
	return (pipe);
}



void	ft_child_process(t_pipex *stack, int i, char **enviromet)
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
	// printf("--->%s\n", s_cmd[i]);
	good_path = get_good_path(stack, s_cmd, enviromet);
	if (!good_path)
		ft_error_path(stack, s_cmd, good_path, i);
	execve(good_path, s_cmd, enviromet);
	perror("execve");
	ft_free_tab(s_cmd);
	free(good_path);
	free(stack);
	// exit(1);
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

char **cpy_enviroment_char(char **cpy_enviroment, t_envp *enviroment, int size)
{
	int	i;

	i = -1;
	if (!enviroment || !cpy_enviroment)
		return (printf("FAILLLLLLL cpy_enviro\n"), free(enviroment), NULL);
	while(enviroment &&  ++i < size - 1)
	{
		cpy_enviroment[i] = ft_strdup(enviroment->path);
		if (!cpy_enviroment[i])
			return (printf("FAIL StrDUP CPY ENVIRO\n"), NULL);
		enviroment = enviroment->next;
	}
	cpy_enviroment[size + 1] = NULL;
	return (cpy_enviroment);
}


// void	ft_redirect(t_pipex *stack, int i)
// {
// 	int	fd;

// 	fd = 0;
// 	if (i == 0)
// 	{
// 		// fd = open_file(stack, i);
// 		dup2(fd, 0);
// 		close(fd);
// 	}
// 	if (i == stack->nmbr_mcd - 1)
// 	{
// 		// fd = open_file(stack, i);
// 		dup2(fd, 1);
// 		close(fd);
// 	}
// 	if (i != 0)
// 	{
// 		dup2(stack->prev, 0);
// 		close(stack->prev);
// 	}
// 	if (i != stack->nmbr_mcd - 1)
// 		dup2(stack->fd[1], 1);
// 	close(stack->fd[0]);
// 	close(stack->fd[1]);
// }

/* 
	creation pipe... cat | ls | cat
	
	cat --> mot
	| --- > pipe
	ls ---> mot
	| ---> pipe
	cat --> mot
*/

// int	pipe_modif(t_cmd *to_pars, )
// {
// 	t_cmd	*current;
	
// 	while(to_pars->next)
// 	{
// 		if (ft_strcmp(to_pars->next->cmd, "|") == 0)
// 			break;
// 		to_pars =to_pars->next; 
// 	}
// 	current = to_pars; // la on est AVANT la pipe
// 	printf("%s\n", current->cmd);
// 	return (0);
// }

int	ft_pipex(t_cmd *to_pars, int size,  t_envp *enviroment, char **commande_split)
{
	t_pipex *stack;
	char 	**enviroment_cpy;

	enviroment_cpy = (char **)malloc(sizeof(char *) * size + 1);
	enviroment_cpy = cpy_enviroment_char(enviroment_cpy, enviroment, size);
	if (!enviroment_cpy)
			printf("shittttttttt\n");
	if (found_count_pipe(to_pars))
	{	
		// stack = (t_pipex *)malloc(sizeof(t_pipex));
		// if (!stack)
			// return (free(stack), 0);
		stack = ft_init_stack(to_pars, size, commande_split, found_count_pipe(to_pars));
		exec_pipes(stack, enviroment_cpy);
		close(stack->fd[0]);
		free(stack);
		// unlink("/tmp/here_doc");
		return (1);
	}
	return (0);
}

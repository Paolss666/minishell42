/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:17:32 by npaolett          #+#    #+#             */
/*   Updated: 2023/12/11 15:17:44 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_error_directory(t_pipex *stack)
{
	ft_putstr_fd("bash : ", 2);
	ft_putstr_fd(stack->fd_infile, 2);
	perror(" ");
	close(stack->prev);
	close(stack->fd[1]);
	close(stack->fd[0]);
	free(stack);
	exit(1);
}

void	ft_error_directory_fd_out(t_pipex *stack)
{
	ft_putstr_fd("bash : ", 2);
	ft_putstr_fd(stack->fd_outfile, 2);
	perror(" ");
	close(stack->prev);
	close(stack->fd[1]);
	close(stack->fd[0]);
	free(stack);
	exit(1);
}

void	ft_error_path(t_pipex *stack, char **s_cmd, char *good_path, int i)
{
	ft_putstr_fd(stack->cmd[i], 2);
	ft_putstr_fd(": command not found\n", 2);
	free(good_path);
	ft_free_tab(s_cmd);
	free(stack);
	exit(0);
}

void	ft_error_split(t_pipex *stack, char **s_cmd)
{		
	ft_putstr_fd(": command not found\n", 2);
	ft_free_tab(s_cmd);
	free(stack);
	exit(1);
}

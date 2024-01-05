/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:18:12 by npaolett          #+#    #+#             */
/*   Updated: 2024/01/05 18:42:22 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_strcmpchr(const char *s, int c)
{
	char		*new_s;
	char		find;
	size_t		lenstr;

	new_s = (char *)s;
	find = (unsigned char)c;
	lenstr = 0;
	if (!new_s)
		return (1);
	while (new_s[lenstr])
	{
		if (new_s[lenstr] == find)
			lenstr++;
		else
			return (1);
	}
	return (0);
}


t_cmd	*scrolling_list_last(t_cmd *to_pars)
{
	if (!to_pars)
		return (NULL);
	while(to_pars->next)
		to_pars = to_pars->next;
	return (to_pars);
}

void	ft_init_stack(t_pipex *stack, int ac, char **av, int count_n_pipe)
{
	// int	fd;

	stack->envp = 0;
	stack->cmd = av + count_n_pipe;
	stack->nmbr_mcd = ac - count_n_pipe;
	// if (stack->here_doc)
	// 	stack->fd_infile = "here_doc";
	// else
	// stack->fd_infile = fd;
	stack->fd_outfile = av[ac];
	stack->prev = 0;
	stack->fd[0] = 0;
	stack->fd[1] = 0;
}

int	fd_in_open(int fd, t_pipex *stack)
{
	if (stack->here_doc)
	{
		fd = open("/tmp/here_doc", O_RDONLY, 0666);
		if (fd == -1)
			ft_error_directory(stack);
	}
	else
	{
		fd = open(stack->fd_infile, O_RDONLY | O_CREAT, 0666);
		if (fd == -1)
			ft_error_directory(stack);
	}
	return (fd);
}

int	fd_out_open(int fd, t_pipex *stack)
{
	if (stack->here_doc)
	{
		fd = open(stack->fd_outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
			ft_error_directory_fd_out(stack);
	}
	else
	{
		fd = open(stack->fd_outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			ft_error_directory_fd_out(stack);
	}
	return (fd);
}

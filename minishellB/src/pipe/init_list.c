/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:18:12 by npaolett          #+#    #+#             */
/*   Updated: 2023/12/12 17:00:49 by npaolett         ###   ########.fr       */
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
		return (free_list_to_pars(to_pars), NULL);
	while(to_pars->next)
		to_pars = to_pars->next;
	return (to_pars);
}

void	ft_init_stack(t_pipex *stack, int size, t_cmd *to_pars, char **commande_split)
{
	t_cmd	*last_cmd;
	// int	i = -1;
	
	// // while(commande_split[++i])
	if (!commande_split)
		printf("commande_split est null\n");
	// printf("commande split[i] --> %s\n", commande_split[1]);
	
	last_cmd = scrolling_list_last(to_pars);
	if (!last_cmd)
	 	printf("fail last_cmd\n");
	/* je doit fare un boucle.. pour chaque to_pars->cmd */
	stack->envp = 0;
	stack->cmd = commande_split + 2;
	stack->nmbr_mcd = size - 3;
	stack->fd_infile = to_pars->cmd;// 
	// printf("last->cmd %s\n", last_cmd->cmd);
	// printf("to_pars->cmd infile %s\n", to_pars->cmd);
	stack->fd_outfile = last_cmd->cmd;
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
		fd = open(stack->fd_infile, O_RDONLY, 0666);
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

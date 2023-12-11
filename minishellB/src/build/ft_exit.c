/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:36:54 by npaolett          #+#    #+#             */
/*   Updated: 2023/12/11 14:07:55 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_envp	*free_envp_list(t_envp *head)
{
	t_envp	*history;

	history = head;
	if (history)
	{
		free(history->path);
		free(history->name);
		free(history->value);
		free(history);
		return NULL;
	}
	else
		return(head);

}

int	found_exit(t_cmd *to_pars)
{
	while (to_pars != NULL)
	{
		if (ft_strncmp(to_pars->cmd, "exit", ft_strlen("exit")) == 0
			&& ft_strlen("exit") == 4)
			return (1);
		to_pars = to_pars->next;
	}
	return (0);
}

void    ft_exit(t_cmd   *to_pars)
{
    if (!to_pars->next)
    {
        ft_putstr_fd("exit\n", 1);
        free_list_to_pars(to_pars);
        // if (enviroment)
            // free_envp_list(enviroment);
        /* il faut bien tout free */
        exit(0);
    }
    else
        ft_putstr_fd("many arguments pour exit\n", 2);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:52:57 by npoalett          #+#    #+#             */
/*   Updated: 2023/11/23 14:33:55 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	found_unset(t_cmd *to_pars)
{
	while (to_pars != NULL)
	{
		if (ft_strncmp(to_pars->cmd, "unset", ft_strlen("unset")) == 0
			&& ft_strlen("unset") == 5)
			return (1);
		to_pars = to_pars->next;
	}
	return (0);
}

void    unset_delete_variable(t_cmd *to_pars, t_envp **enviroment)
{
    t_envp  *current;
    t_envp  *prev;
    t_cmd  *next;
    prev = NULL;
    current = *enviroment;
    next = to_pars->next;

    while(current != NULL && ft_strncmp(next->cmd, current->path, ft_strlen(next->cmd))!= 0)
    {
        prev = current;
        current = current->next;
    }
    if (current != NULL)
    {
        if (prev == NULL)
            *enviroment = current->next;
        else
            prev->next = current->next;
		free(current->name);
		free(current->path);
		free(current->value);
		free(current);
    }
}
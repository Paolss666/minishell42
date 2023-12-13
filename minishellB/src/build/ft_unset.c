/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:52:57 by npoalett          #+#    #+#             */
/*   Updated: 2023/12/13 16:35:24 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/* Il FAUT CREER UN DOSSIER QUE POUR LA COMMANDE UNSET */

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

void	unset_delete_variable(t_cmd *to_pars, t_envp **enviroment, t_exp **export)
{
	t_envp	*current;
	t_envp	*prev;
	t_exp	*current_exp;
	t_exp	*prev_exp;
	t_cmd	*next;

	prev = NULL;
	current = *enviroment;
	current_exp = *export;
	if (!to_pars->next)
	    return(ft_putstr_fd("unset need arguments\n", 2), (void)0);
	else
	    next = to_pars->next;
	while(next)
	{
		while (current != NULL && (ft_strncmp(next->cmd, current->path,
					ft_strlen(next->cmd)) != 0))
		{
			prev = current;
			current = current->next;
		}
		while (current_exp != NULL && (ft_strncmp(ft_strjoin("export ", next->cmd),
					current_exp->path, ft_strlen(ft_strjoin("export ",
							next->cmd))) != 0))
		{
			prev_exp = current_exp;
			current_exp = current_exp->next;
		}
		if (current_exp != NULL)
		{
			if (prev_exp == NULL)
				*export = current_exp->next;
			else
				prev_exp->next = current_exp->next;
			free(current_exp->path);
			free(current_exp);
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
		next = next->next;
	}
}

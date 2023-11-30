/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:28:37 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/30 17:10:09 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int		found_echo(t_cmd *to_pars)
{
	while (to_pars != NULL)
	{
		if (ft_strncmp(to_pars->cmd, "echo", ft_strlen("echo")) == 0
			&& ft_strlen(to_pars->cmd) == 4)
			return (1);
		to_pars = to_pars->next;
	}
	return (0);
}

void	ft_echo(t_cmd	*to_pars)
{
	if (!to_pars->next)
		ft_putstr_fd("\n", 1);
	else
		ft_putstr_fd(ft_strjoin(to_pars->next->cmd, "\n"), 1);
	if (ft_strcmp("echo -n", to_pars->cmd) == 0 && !to_pars->next)
		ft_putstr_fd("", 2);
/* 	else /* if (ft_strcmp("echo -n", to_pars->cmd) == 0 && to_pars->next) */
		printf("found\n"); */
		// ft_putstr_fd(to_pars->next->cmd, 1);

}

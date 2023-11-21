/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:29:14 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/21 16:40:26 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// PWD NE PRENDES PAS DES ARGUMETNS ---//
// EX; 	PWD ASDASDAS	----> MEGGAGE D'ERREUR => pwd: too many arguments

int	ft_pwd(t_cmd *to_pars)
{
	while (to_pars != NULL)
	{
		if (ft_strncmp(to_pars->cmd, "pwd", ft_strlen("pwd")) == 0
			&& ft_strlen(to_pars->cmd) == 3 && to_pars->next == NULL)
			return (1);
		else
		{
			ft_putstr_fd("pwd: too many arguments\n", 2);
			break ;
		}
		// to_pars = to_pars->next;
	}
	return (0);
}

// ----- afficher le d'ou nous sommes ------- // 
// check pouquoi l'history d'erange l 'affichage // 

int	print_pwd(t_envp *envp)
{
	int		i;

	i = 3;
	if (!envp)
		return (perror("ENVP FAIL"), 0);
	while (envp != NULL)
	{
		if (ft_strncmp(envp->path, "PWD=", ft_strlen("PWD=")) == 0)
		{
			while (envp->path[++i])
				ft_putchar_fd(envp->path[i], 1);
			ft_putchar_fd('\n', 1);
		}
		envp = envp->next;
	}
	return (0);
}

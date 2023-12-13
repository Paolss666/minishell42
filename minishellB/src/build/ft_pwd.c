/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:29:14 by npaolett          #+#    #+#             */
/*   Updated: 2023/12/13 14:23:13 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/* Il FAUT CREER UN DOSSIER QUE POUR LA COMMANDE PWD */
// CA MARCHE PAS
// PWD NE PRENDES PAS DES ARGUMETNS ---//
// EX; 	PWD ASDASDAS	-----> MEGGAGE D'ERREUR => pwd: too many arguments
// il doit avoir que pwd dans les argv;

int	ft_pwd(t_cmd *to_pars)
{
	char	*get_pwd;

	get_pwd = NULL;
	while (to_pars != NULL)
	{
		if (ft_strncmp(to_pars->cmd, "pwd", ft_strlen("pwd")) == 0 && !to_pars->next)
		{
			get_pwd = getcwd(NULL, 0);
			if (!get_pwd)
				ft_putstr_fd("shell-init: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
			printf("%s\n", get_pwd);
			break;
		}
		to_pars = to_pars->next; //<<== non serve
	}
	return (0);
}


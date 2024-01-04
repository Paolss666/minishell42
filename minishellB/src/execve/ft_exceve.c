/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:33:51 by npaolett          #+#    #+#             */
/*   Updated: 2024/01/04 15:51:24 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void    ft_execve(t_cmd *to_pars, t_envp *enviroment, char *line)
{
    char	**new_enviroment;
    char	*good_path_access;

    new_enviroment = envp_list_to_new_env(enviroment);
    good_path_access = ft_good_path_access(to_pars, enviroment);
    if (!good_path_access)
    	return (ft_error_commande_not_to_pars(to_pars), (void)0);
    execve(good_path_access, ft_split(line, ' '), new_enviroment);
	perror("execve");
	ft_free_tab(new_enviroment);
	return ((void)0);
}
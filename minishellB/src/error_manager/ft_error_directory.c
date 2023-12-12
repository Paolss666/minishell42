/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_directory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:36:57 by armeyer           #+#    #+#             */
/*   Updated: 2023/12/12 11:56:55 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_error_directory3(char *str)
{
	extern int	g_exit_status;
	int			i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '.' && str[i] != '/' && str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	ft_printf("\nbash: %s Is a directory\n", str);
	g_exit_status = 126;
	return (1);
}

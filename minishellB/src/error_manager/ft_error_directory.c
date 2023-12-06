/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_directory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:36:57 by armeyer           #+#    #+#             */
/*   Updated: 2023/12/06 14:42:29 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_error_directory(char *str)
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

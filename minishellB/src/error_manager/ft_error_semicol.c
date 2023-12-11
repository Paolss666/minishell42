/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_semicol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:47:04 by armeyer           #+#    #+#             */
/*   Updated: 2023/12/11 16:48:51 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_error_semicol(char *str)
{
	int i;
	extern int	g_exit_status;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ';' && str[i + 1] && str[i + 1] == ';')
		{
			ft_printf("\n bash: Syntax error near unexcpected token ';;'\n");
			g_exit_status = 2;
			return (1);
		}
		if (str[i] == ';')
		{
			ft_printf("\n bash: Syntax error near unexcpected token ';'\n");
			g_exit_status = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

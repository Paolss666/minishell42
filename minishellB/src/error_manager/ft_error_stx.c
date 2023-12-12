/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_stx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:02:53 by armeyer           #+#    #+#             */
/*   Updated: 2023/12/12 14:10:15 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_error_stx(char *str)
{
	int i;
	extern int	g_exit_status;
	char	c;
	char	d;

	i = 0;
	c = '"';
	d = 39;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			printf("\n bash: Syntax error near unexcpected token %c\n", c);
			g_exit_status = 2;
			return (1);
		}
		if (str[i] == 39)
		{
			printf("\n bash: Syntax error near unexcpected token %c\n", d);
			g_exit_status = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

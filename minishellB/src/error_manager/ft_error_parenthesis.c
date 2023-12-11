/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_parenthesis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:40:01 by armeyer           #+#    #+#             */
/*   Updated: 2023/12/11 16:45:44 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_error_parenthesis(char *str)
{
	int i;
	extern int	g_exit_status;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(')
		{
			ft_printf("\n bash: Syntax error near unexcpected token '('\n");
			g_exit_status = 2;
			return (1);
		}
		if (str[i] == ')')
		{
			ft_printf("\n bash: Syntax error near unexcpected token ')'\n");
			g_exit_status = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

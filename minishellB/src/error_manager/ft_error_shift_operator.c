/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_shift_operator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:03:04 by armeyer           #+#    #+#             */
/*   Updated: 2023/12/06 14:18:16 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int ft_error_shift_operator(char *str)
{
	extern int	g_exit_status;
	int			i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '<' && str[i] != '>' && str[i] != '\t' && str[i] != ' ')
			return (0);
		i++;
	}
	i = 0;
	if (ft_strlen(str) == 2)
	{
		ft_printf("\nbash: syntax error near unexpected token 'newline'\n");
		g_exit_status = 2;
		return (1);
	}
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '>')
		{
			if (str[i + 1] == '>')
				printf("\nbash: syntax error near unexpected token '>>'\n");
			else
				printf("\nbash: syntax error near unexpected token '>'\n");
			g_exit_status = 2;
			return (1);
		}
		if (str[i] == '<')
		{
			if (str[i + 1] == '<')
				printf("\nbash: syntax error near unexpected token '<<'\n");
			else
				printf("\nbash: syntax error near unexpected token '<'\n");
			g_exit_status = 2;
			return (1);
		}
	}
	return (0);
}

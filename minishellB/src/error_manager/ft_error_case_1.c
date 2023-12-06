/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_case_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:59:52 by armeyer           #+#    #+#             */
/*   Updated: 2023/12/06 15:07:03 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_error_case_1_part_2(char c)
{
	extern int	g_exit_status;

	if (c == '-')
	{
		ft_printf("\nbash: -: command not found\n");
		g_exit_status = 127;
		return (1);
	}
	if (c == '*')
	{
		ft_printf("\nbash: crashtest.c: command not found\n");
		g_exit_status = 127;
		return (1);
	}
	if (c == '.')
	{
		ft_printf("\nbash: .: filename argument required\n");
		g_exit_status = 2;
		return (1);
	}
	if (c == '$')
	{
		ft_printf("\nbash: $: command not found\n");
		g_exit_status = 127;
		return (1);
	}
	if (c == '|')
	{
		ft_printf("\nbash: syntax error near unexpected token '|'\n");
		g_exit_status = 2;
		return (1);
	}
	return (0);
}

int	ft_error_case_1(char c)
{
	extern int	g_exit_status;

	if (c == '\t' || c == ':' || c == '!' || c == '#')
	{
		ft_printf("\n");
		if (c == '\t' || c == ':' || c == '#')
			g_exit_status = 0;
		if (c == '!')
			g_exit_status = 1;
		return (1);
	}
	if (c == '<' || c == '>')
	{
		ft_printf("\nbash: syntax error near unexpected token 'newline'\n");
		g_exit_status = 2;
		return (1);
	}
	if (c == '/')
	{
		ft_printf("\nbash: // Is a directory\n");
		g_exit_status = 126;
		return (1);
	}
	if (ft_error_case_1_part_2(c))
		return (1);
	return (0);
}

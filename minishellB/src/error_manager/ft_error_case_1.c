/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_case_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:59:52 by armeyer           #+#    #+#             */
/*   Updated: 2023/12/05 14:24:44 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_error_case_1_part_2(char c)
{
	if (c == '*')
	{
		ft_printf("\nbash: crashtest.c: command not found\n");
		return (1);
	}
	if (c == '.')
	{
		ft_printf("\nbash: .: filename argument required\n");
		return (1);
	}
	if (c == '$')
	{
		ft_printf("\nbash: $: command not found\n");
		return (1);
	}
	return (0);
}

int	ft_error_case_1(char c)
{
	if (c == '\t' || c == ':' || c == '!' || c == '#')
	{
		ft_printf("\n");
		return (1);
	}
	if (c == '<' || c == '>')
	{
		ft_printf("\nbash: syntax error near unexpected token 'newline'\n");
		return (1);
	}
	if (c == '/')
	{
		ft_printf("\nbash: // Is a directory\n");
		return (1);
	}
	if (c == '-')
	{
		ft_printf("\nbash: -: command not found\n");
		return (1);
	}
	if (ft_error_case_1_part_2(c))
		return (1);
	return (0);
}

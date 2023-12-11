/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:10:10 by armeyer           #+#    #+#             */
/*   Updated: 2023/12/11 17:09:30 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_error_pipe(char *str)
{
	int i;
	int j;
	int	count;
	int flag;
	extern int	g_exit_status;
	
	i = 0;
	j = 0;
	count = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	if (count == 0)
		return (0);
	if (count == 1)
	{
		i = 0;
		count = 0;
		while (str[i] != '|')
		{
			if (str[i] >= 'a' && str[i] <= 'z')
				count++;
			if (str[i] >= 'A' && str[i] <= 'Z')
				count++;
			i++;
		}
		if (count == 0)
		{
			ft_printf("\nbash syntax error near unexpected token '|'\n");
			g_exit_status = 2;
			return (1);
		}
		i++;
		if (str[i] == '\0')
		{
			ft_printf("\nbash syntax error near unexpected token '|'\n");
			g_exit_status = 2;
			return (1);
		}
		count = 0;
		while (str[i] != '\0')
		{
			if (str[i] >= 'a' && str[i] <= 'z')
				count++;
			if (str[i] >= 'A' && str[i] <= 'Z')
				count++;
			i++;
		}
		if (count == 0)
		{
			ft_printf("\nbash syntax error near unexpected token '|'\n");
			g_exit_status = 2;
			return (1);
		}
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
		{
			if (str[i + 1] == '|')
			{
				ft_printf("\nbash syntax error near unexpected token '||'\n");
				g_exit_status = 2;
				return (1);
			}
			j = 0;
			flag = 0;
			while (j < i)
			{
				if (str[j] >= 'a' && str[j] <= 'z')
					flag = 1;
				if (str[j] >= 'A' && str[j] <= 'Z')
					flag = 1;
				j++;
			}
			if (flag == 0)
			{
				ft_printf("\nbash syntax error near unexpected token '|'\n");
				g_exit_status = 2;
				return (1);
			}
			j++;
			while (str[j] != '\0')
			{
				if (str[j] >= 'a' && str[j] <= 'z')
					flag = 1;
				if (str[j] >= 'A' && str[j] <= 'Z')
					flag = 1;
				j++;
			}
			if (flag == 0)
			{
				ft_printf("\nbash syntax error near unexpected token '|'\n");
				g_exit_status = 2;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

// FIX when multiple pipe at the end
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_operand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:53:13 by armeyer           #+#    #+#             */
/*   Updated: 2023/12/11 16:16:30 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_error_operand(char *str)
{
	extern int	g_exit_status;
	int	index;
	int	i;
	int	previousWord;
	int	nextWord;

	index = 0;
	if (ft_count_sign(str, '&') % 2 == 1)
	{
		ft_printf("\nbash syntax error near unexpected token '&'\n");
		g_exit_status = 2;
		return (1);
	}
	while (str[index] != '\0')
	{
		if (str[index] == '&' && str[index + 1] && str[index + 1] != '&' && str[index - 1] != '&')
		{
			ft_printf("\nbash syntax error near unexpected token '&'\n");
			g_exit_status = 2;
			return (1);
		}
		if (str[index] == '&' && (str[index - 1] == '&' || str[index + 1] == '&'))
		{
			previousWord = 0;
			nextWord = 0;
			i = index;
			while (i > 0)
			{
				if (ft_isalpha(str[i]))
					previousWord = 1;
				i--;
			}
			i = index;
			while (str[i] != '\0')
			{
				if (ft_isalpha(str[i]))
					nextWord = 1;
				i++;
			}
			if (previousWord == 0 || nextWord == 0)
			{
				ft_printf("\nbash syntax error near unexpected token '&&'\n");
				g_exit_status = 2;
				return (1);
			}
		}
		index++;
	}
    return (0);
}



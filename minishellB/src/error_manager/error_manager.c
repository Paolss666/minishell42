/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:05:20 by armeyer           #+#    #+#             */
/*   Updated: 2023/12/12 11:56:29 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_error(char *to_epur)
{
	int			len;
	char		*str;
/* 	extern int	g_exit_status; */

	str = epur_str(to_epur);
	if (str == NULL || str[0] == '\0')
		return (1);
	len = ft_strlen(str);
	if (len == 1)
	{
		if (ft_error_case_1(str[0]))
			return (1);
	}
	if (ft_error_blank(str))
		return (1);
	if (ft_error_shift_operator(str))
		return (1);
	if (ft_error_directory3(str))
		return (1);
	if (ft_error_pipe(str))
		return (1);
	if (ft_error_operand(str))
		return (1);
	if (ft_error_parenthesis(str))
		return (1);
	if (ft_error_semicol(str))
		return (1);
	return (0);
}


int	error_manager(char *str)
{
	if (is_error(str))
		return (1);
	return (0);
}



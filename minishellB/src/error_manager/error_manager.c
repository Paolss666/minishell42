/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:05:20 by armeyer           #+#    #+#             */
/*   Updated: 2023/12/11 17:09:26 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_error(char *str)
{
	int			len;
	extern int	g_exit_status;

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
	if (ft_error_directory(str))
		return (1);
	if (ft_error_pipe(str))
		return (1);
	return (0);
}


int	error_manager(char *str)
{
	if (is_error(str))
		return (1);
	return (0);
}



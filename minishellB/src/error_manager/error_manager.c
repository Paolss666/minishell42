/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armeyer <armeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:05:20 by armeyer           #+#    #+#             */
/*   Updated: 2023/12/05 14:06:21 by armeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_error(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (len == 1)
	{
		if (ft_error_case_1(str[0]))
			return (1);
	}
	return (0);
}


int	error_manager(t_cmd *to_parse)
{
	t_cmd	*command;
	char	*str;

	command = to_parse;
	if (command)
		str = ft_strdup(command->cmd);
	command = command->next;
	while (command)
	{
		str = ft_strjoin(str, command->cmd);
		command = command->next;
	}
	if (is_error(str))
		return (1);
	return (0);
}



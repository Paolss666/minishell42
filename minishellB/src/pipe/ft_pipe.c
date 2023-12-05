/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:54:16 by npaolett          #+#    #+#             */
/*   Updated: 2023/12/05 15:56:54 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	found_pipe(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		if (ft_strncmp(cmd->cmd, "|", ft_strlen("|")) == 0)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}
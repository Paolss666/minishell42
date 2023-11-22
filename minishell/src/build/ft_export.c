/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:52:41 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/22 17:44:36 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	found_export(t_cmd *to_pars)
{
	while (to_pars != NULL)
	{
		if (ft_strncmp(to_pars->cmd, "export", ft_strlen("export")) == 0
			&& ft_strlen("export") == 6)
			return (1);
		to_pars = to_pars->next;
	}
	return (0);
}


void	add_export_env(t_cmd *to_pars, t_envp **enviroment)
{
	char			*line;
	char			*found_egual;
	char			*name_v;
	char			*value;
	unsigned int	len;
	t_envp			*current = NULL;
	t_envp			*new_variable = NULL;


	line = to_pars->next->cmd;
	found_egual = ft_strchr(line, '=');
	if (found_egual)
	{
		len = found_egual - line;
		name_v = malloc(sizeof(char) * len + 1);
		if (!name_v)
			return (printf("FAIL MALLOC name_v\n"), (void)0);
		value = ft_strdup(found_egual + 1);
		if (!value)
			return (printf("FAIL strdup value\n"), (void)0);
		// printf("test2\n");
		ft_strcpy(name_v, line, len + 1);
		// printf("test3\n");
		current = *enviroment;
		// printf("testw\n");
		while (current != NULL && ft_strncmp(current->path, name_v, ft_strlen(name_v)) != 0)
			current = current->next;
		if (current != NULL)
		{
			free(current->value);
			current->value = value;
			free(name_v);
		}
		else
		{
			new_variable = malloc(sizeof(t_envp));
			if (!new_variable)
				return (perror("FAIL MALLOC NEW_VARIABLE"), (void)0);
			new_variable->path = name_v;// probleme
			new_variable->value = value;// probleme
			new_variable->path = ft_strjoin(name_v, ft_strjoin("=", value));
			new_variable->next = *enviroment;
			*enviroment = new_variable;
		}
	}
	else
		return (ft_putstr_fd("Not valid in this context: ", 2), ft_putstr_fd(line, 2), write(2, "\n", 1), (void)0);
}

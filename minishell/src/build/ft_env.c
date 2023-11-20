/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:27:26 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/20 16:01:44 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// <<------- copier l'env dans des listes chainees ------ >>

char *ft_strcpy(char *dest, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	i = 0;
	srclen = ft_strlen(src);
	if (size == 0)
		return (NULL);
	while (src[i] && i < (size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	init_lst_envp(t_envp *enviroment)
{
	if (!enviroment)
		return ;
	enviroment = malloc(sizeof(t_envp));
	if (!enviroment)
		ft_putstr_fd("FAIL malloc enviroment\n", 2);
	enviroment->path = NULL;
	enviroment->next = NULL;
}



void    found_and_add_env(char **env, t_envp *enviroment)
{
	// char	**env_split;
	int		i;

	i = -1;
	init_lst_envp(enviroment);
	while(env[++i] && enviroment != NULL)
	{
		printf("whileeee\n");
		enviroment->path = ft_strdup(ft_strcpy(enviroment->path, env[i], ft_strlen(env[i])));
		enviroment = enviroment->next;
	}
}

int	ft_envp(t_cmd *to_pars)
{
	while (to_pars != NULL)
	{
		if (ft_strncmp(to_pars->cmd, "env", ft_strlen("env")) == 0
			&& ft_strlen(to_pars->cmd) == 3)
			return (1);
		to_pars = to_pars->next;
	}
	return (0);
}



void	print_list_envp(t_envp *head)
{
	t_envp	*current;

	current = head;
	while (current != NULL)
	{
		printf("Command-path --> : %s\n", current->path);
		current = current->next;
	}
}
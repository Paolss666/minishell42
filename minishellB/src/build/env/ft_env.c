/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:27:26 by npaolett          #+#    #+#             */
/*   Updated: 2024/01/03 16:50:21 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/* Il FAUT CREER UN DOSSIER QUE POUR LA COMMANDE ENV*/

// <<------- copier l'env dans des listes chainees ------ >>
char 	*ft_strcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
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


t_envp	*found_and_add_env(char **env, t_envp *enviroment)
{
	t_envp	*current;
	t_envp	*envp;
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (env[++i])
	{
		current = (t_envp *)malloc(sizeof(t_envp));
		if (!current)
			return (perror("FAIL malloc t_envp"), NULL);
		current->path = ft_strdup(env[i]);
		current->value = ft_strdup(ft_strchr(current->path, '=') + 1);
		len = ft_strlen(current->path) -  ft_strlen(current->value);
		current->name = ft_substr(current->path, 0, len - 1);
		if (!current->name)
			return (perror("FAIL"), NULL);
		// printf("current->name %s\n", current->name);
		if (!current->path || !current->name || !current->value)
			return (perror("ft_strdup found_and_add_env"), NULL);
		current->next = NULL;
		if (!enviroment)
			enviroment = current;
		else
		{
			envp = enviroment;
			while (envp->next != NULL)
				envp = envp->next;
			envp->next = current;
		}
	}
	return (enviroment);
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

	if (!head)
		printf("env -i\n");
	current = head;
	while (current != NULL)
	{
		printf("%s\n", current->path);
		current = current->next;
	}
}

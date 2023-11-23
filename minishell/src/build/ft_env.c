/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:27:26 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/23 12:44:22 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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

// void	init_lst_envp(t_envp *enviroment)
// {
// 	if (!enviroment)
// 		return ;
// 	enviroment = malloc(sizeof(t_envp));
// 	if (!enviroment)
// 		ft_putstr_fd("FAIL malloc enviroment\n", 2);
// 	enviroment->path = NULL;
// 	enviroment->next = NULL;
// }



t_envp	*found_and_add_env(char **env, t_envp *enviroment)
{
	t_envp	*current;
	t_envp	*envp;
	int		i;

	i = -1;
	while (env[++i])
	{
		current = (t_envp *)malloc(sizeof(t_envp));
		if (!current)
			return (perror("FAIL malloc t_envp"), NULL);
		current->path = ft_strdup(env[i]);
		if (!current->path)
			return (perror("ft_strdup"), NULL);
		current->next = NULL;
		if (!enviroment)
			// Se la lista è vuota, il nuovo nodo diventa la testa della lista
			enviroment = current;
		else
		{
			// Se la lista non è vuota, aggiungi il nuovo nodo alla fine
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:52:41 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/24 20:59:34 by npoalett         ###   ########.fr       */
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

// Funzione per lo swap di due nodi nella lista concatenata
void ft_swap(t_exp *a, t_exp *b) 
{
	char *temp;

    temp = a->path;
    a->path = b->path;
    b->path = temp;
}


void	export_env_sort(t_exp *exp_env) /* serve a ordinare la lista in ordine ASCII alpha */ 
{
	int	swap;
	t_exp	*next;
	t_exp	*current;

	swap = 1;
	if (!exp_env)
		printf("fail exp_env\n");
	while(swap)
	{
		current = exp_env;
		swap = 0;
		while(current->next)
		{
			next = current->next;
			if (ft_strcmp(current->path, next->path) > 0)
			{
					ft_swap(current, next);
					swap = 1;
			}
			current = current->next;
		}
	}
}


t_exp	*add_env_with_export(t_envp *enviroment)
{
	t_exp	*export_list;
	t_exp	*current_export;
	t_exp	*new_export;

	export_list = NULL;
	current_export = NULL;
	while (enviroment != NULL)
	{
		new_export = (t_exp *)malloc(sizeof(t_exp));
		if (!new_export)
		{
			perror("ERROR: malloc t_exp");
			exit(EXIT_FAILURE);
		}
		new_export->path = ft_strjoin("export ", enviroment->path);
		new_export->name =  NULL; //ft_strdup(enviroment->name);
		new_export->value =  NULL; //ft_strdup(enviroment->value);
		if (!new_export->path)
		{
			perror("ERROR: strdup");
			exit(EXIT_FAILURE);
		}
		new_export->next = NULL;
		if (export_list == NULL)
		{
			export_list = new_export;
			current_export = export_list;
		}
		else
		{
			current_export->next = new_export;
			current_export = new_export;
		}
		enviroment = enviroment->next;
	}
	return (export_list);
}

void	print_export_list(t_exp *export)
{
	while (export != NULL)
	{
		printf("%s\n", export->path);
		export = export->next;
	}
}

void	add_export_env(t_cmd *to_pars, t_envp **enviroment)
{
	t_envp			*current;
	t_envp			*new_variable;
	t_envp			*last;
	unsigned int	len;
	char			*name_v;
	char			*value;
	char			*line;
	char			*found_equal;

	last = NULL;
	current = NULL;
	new_variable = NULL;
	line = to_pars->next->cmd;
	found_equal = ft_strchr(line, '=');
	if (found_equal)
	{
		len = found_equal - line;
		name_v = ft_substr(line, 0, len);
		value = ft_strdup(found_equal + 1);
		if (!name_v || !value)
		{
			perror("Memory allocation error");
			free(name_v);
			free(value);
			return ;
		}
		current = *enviroment;
		while (current != NULL && ft_strncmp(current->path, name_v,
				ft_strlen(name_v)) != 0)
			current = current->next;
		if (current != NULL)
		{
			free(current->value);
			current->value = value;
			free(name_v);
		}
		else
		{
			new_variable = (t_envp *)malloc(sizeof(t_envp));
			if (!new_variable)
			{
				perror("Memory allocation error");
				free(name_v);
				free(value);
				return ;
			}
			new_variable->path = ft_strjoin(name_v, ft_strjoin("=", value));
			new_variable->value = value;
			new_variable->next = NULL;
			if (*enviroment == NULL)
				*enviroment = new_variable;
					// La lista è vuota,// il nuovo nodo diventa la testa;
			else
			{
				// Aggiungi il nuovo nodo alla fine della lista
				last = *enviroment;
				while (last->next != NULL)
					last = last->next;
				last->next = new_variable;
			}
		}
	}
	else
	{
		ft_putstr_fd("Not valid in this context: ", 2);
		ft_putstr_fd(line, 2);
		write(2, "\n", 1);
	}
}

// void	add_export_env(t_cmd *to_pars, t_envp **enviroment)
// {
// 	char			*line;
// 	char			*found_egual;
// 	char			*name_v;
// 	char			*value;
// 	unsigned int	len;
// 	t_envp			*current = NULL;
// 	t_envp			*new_variable = NULL;

// 	line = to_pars->next->cmd;
// 	found_egual = ft_strchr(line, '=');
// 	if (found_egual)
// 	{
// 		len = found_egual - line;
// 		name_v = malloc(sizeof(char) * len + 1);
// 		if (!name_v)
// 			return (printf("FAIL MALLOC name_v\n"), (void)0);
// 		value = ft_strdup(found_egual + 1);
// 		if (!value)
// 			return (printf("FAIL strdup value\n"), (void)0);
// 		// printf("test2\n");
// 		ft_strcpy(name_v, line, len + 1);
// 		// printf("test3\n");
// 		current = *enviroment;
// 		// printf("testw\n");
// 		while (current != NULL && ft_strncmp(current->path, name_v,
// ft_strlen(name_v)) != 0)
// 			current = current->next;
// 		if (current != NULL)
// 		{
// 			free(current->value);
// 			current->value = value;
// 			free(name_v);
// 		}
// 		else
// 		{
// 			new_variable = malloc(sizeof(t_envp));
// 			if (!new_variable)
// 				return (perror("FAIL MALLOC NEW_VARIABLE"), (void)0);
// 			new_variable->path = name_v;// probleme
// 			new_variable->value = value;// probleme
// 			new_variable->path = ft_strjoin(name_v, ft_strjoin("=", value));
// 			new_variable->next = *enviroment;
// 			*enviroment = new_variable;
// 		}
// 	}
// 	else
// 		return (ft_putstr_fd("Not valid in this context: ", 2),
// ft_putstr_fd(line, 2), write(2, "\n", 1), (void)0);
// }

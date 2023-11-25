/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:52:41 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/25 12:50:22 by npoalett         ###   ########.fr       */
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
		new_export->name = NULL; /* ft_strdup(enviroment->name); */
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

void	add_export_env(t_cmd *to_pars, t_envp **enviroment, t_exp **export)
{
	t_envp			*current;
	t_envp			*new_variable;
	t_exp			*new_export;
	t_exp			*last_exp;
	t_envp			*last;
	unsigned int	len;
	char			*name_v;
	char			*value;
	char			*line;
	char			*found_equal;

	last = NULL;
	current = NULL;
	new_variable = NULL;
	new_export = NULL;
	line = to_pars->next->cmd;
	found_equal = ft_strchr(line, '=');
	if (found_equal)
	{
		len = found_equal - line;
		name_v = ft_substr(line, 0, len);
		value = ft_strdup(found_equal + 1);
		if (!name_v || !value)
			return (perror("Memory allocation FAIL"), free(name_v), free(value));
		current = *enviroment;
		while (current != NULL && ft_strncmp(current->path, name_v, ft_strlen(name_v))!= 0)
			current = current->next;
		if (current != NULL)
		{
			free(current->path);
			current->path = ft_strjoin(name_v,ft_strjoin("=", value));
			free(value);
			free(name_v);
		}
		else
		{
			new_variable = (t_envp *)malloc(sizeof(t_envp));
			if (!new_variable)
					return (perror("Memory allocation FAIL"), free(name_v), free(value));
			new_variable->path = ft_strjoin(name_v, ft_strjoin("=", value));
			new_variable->value = value;
			new_variable->name = name_v;
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
/* 		export = add_env_with_export(enviroment);
		export_env_sort(export); */
	}
	else if (line)
    {
        name_v = ft_strdup(line);
        value = NULL; // Nessun valore assegnato

        if (!name_v)
            return (perror("Memory allocation FAIL name_v exp"), free(name_v));
        new_export = (t_exp *)malloc(sizeof(t_exp));
        if (!new_export)
            return (perror("Memory allocation FAIL"), free(name_v));
        new_export->path = ft_strjoin("export ", name_v);
        new_export->name = NULL;
        new_export->value = value;
        new_export->next = NULL;
        if (*export == NULL)
            *export = new_export; // La lista è vuota, il nuovo nodo diventa la testa
        else
        {
            // Aggiungi il nuovo nodo alla fine della lista senza valore
            last_exp = *export;
            while (last_exp->next != NULL)
                last_exp = last_exp->next;
            last_exp->next = new_export;
        }
/* 			export = add_env_with_export(enviroment);
			export_env_sort(export); */
    }
}

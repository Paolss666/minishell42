/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:52:41 by npaolett          #+#    #+#             */
/*   Updated: 2023/12/04 18:49:48 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
/* Il FAUT CREER UN DOSSIER QUE POUR LA COMMANDE EXPORT */

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
void	ft_swap(t_exp *a, t_exp *b)
{
	char	*temp;

	temp = a->path;
	a->path = b->path;
	b->path = temp;
}

/* serve a ordinare la lista in ordine ASCII alpha */
void	export_env_sort(t_exp *exp_env)
{
	int		swap;
	t_exp	*next;
	t_exp	*current;

	swap = 1;
	if (!exp_env)
		printf("fail exp_env\n");
	while (swap)
	{
		current = exp_env;
		swap = 0;
		while (current->next)
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
/// ajoute export avec env et je le modif export variable="value" // 
t_exp	*add_env_with_export(t_envp *enviroment)
{
	t_exp			*export_list;
	t_exp			*current_export;
	t_exp			*new_export;
	char			*egual_position;
	char			*name;
	char			*value;

	export_list = NULL;
	current_export = NULL;
	// egual_index = 0;
	egual_position = NULL;
	while (enviroment != NULL)
	{
		new_export = (t_exp *)malloc(sizeof(t_exp));
		if (!new_export)
			return (perror("ERROR: t_exp"), exit(EXIT_FAILURE), NULL);
		egual_position = ft_strchr(enviroment->path, '=');
		name = ft_substr(enviroment->path, 0, egual_position - enviroment->path);
		value = ft_strdup(egual_position + 1);
		// BUILDIN NOUVEAU PARCOURS EXP
		new_export->path = ft_strjoin("export ", name);
		new_export->path = ft_strjoin(new_export->path, "=\"");
		new_export->path = ft_strjoin(new_export->path, value);
		new_export->path = ft_strjoin(new_export->path, "\"");
		new_export->name = NULL;  /* ft_strdup(enviroment->name); */
		new_export->value = ft_strdup(ft_strchr(new_export->path, '='));
		if (!new_export->path)
			return (perror("ERROR: strdup"), exit(EXIT_FAILURE), NULL);
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

t_envp	*add_node_to_end(t_envp **list, const char *name, const char *value)
{
	t_envp	*new_node;
	t_envp	*current;

	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (!new_node)
		return (perror("Memory allocation failed"), NULL);
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	if (!new_node->name || !new_node->value)
		return (perror("Memory allocation failed"), free(new_node->name), free(new_node->value), free(new_node), NULL);
	new_node->path = ft_strjoin(name, ft_strjoin("=", value));
	if (!new_node->path)
		return (perror("Memory allocation failed"), free(new_node->name), free(new_node->value), free(new_node), NULL);
	new_node->next = NULL;
	if (*list == NULL)
	{
		*list = new_node;
		return (*list);
	}
	current = *list;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	return (*list);
}

void	add_export_env(t_cmd *to_pars, t_envp **enviroment, t_exp **export)
{
	t_envp			*current;
	t_exp			*new_current;
	t_exp			*new_upgrade_exp;
	t_envp			*new_variable;
	t_exp			*new_export;
	t_exp			*last_exp;
	t_exp			*check_equal_list;
	t_envp			*last;
	unsigned int	len;
	char			*name_v;
	char			*value;
	char			*line;
	char			*found_equal;
	char			*good_path;
	char			*check_equal;
	char			*check_name_v;
	char			*found_plus;
	char			*modif_variable;

	// unsigned int	len_for_equal;
	good_path = NULL;
	check_name_v = NULL;
	last = NULL;
	current = NULL;
	new_variable = NULL;
	new_export = NULL;
	new_upgrade_exp = *export;
	modif_variable = NULL;
	line = to_pars->next->cmd;
	found_equal = ft_strchr(line, '=');
	check_equal_list = *export;
	found_plus = ft_strchr(line, '+'); /* CA PRT SI ON TROUVE UN + */
	if (found_plus)
		modif_variable = ft_substr(found_plus, 2, ft_strlen(found_plus));
	printf("found_plus --> %s\n", found_plus);
	printf("modif_variable --> %s\n", modif_variable);
	printf("found_equal --> %s\n", found_equal);
	if ((line && found_equal)) // SI IN TROUVE UN EGALE ET LINE NEXT->CMD 
	{
		len = found_equal - line;
		name_v = ft_substr(line, 0, len);
		value = ft_strdup(found_equal + 1);
		if (!name_v || !value)
			return (perror("Memory allocation FAIL"), free(name_v), free(value),
				(void)0);
		current = *enviroment;
		good_path = ft_strjoin("export ", name_v);
		while (current != NULL && ft_strncmp(current->path, name_v,
				ft_strlen(name_v)) != 0) /*  */
			current = current->next;
		while (new_upgrade_exp != NULL && ft_strncmp(new_upgrade_exp->path,
				good_path, ft_strlen(good_path)) != 0) /*  */
			new_upgrade_exp = new_upgrade_exp->next;
		if (current && new_upgrade_exp) /* SI O A OUVE LA NOM VARIABLE ET EST DANS LES DEUX LIST */
		{
			current->path = ft_strjoin(name_v, ft_strjoin("=", value));
			free(new_upgrade_exp->path);
			// if (found_plus)
				// new_upgrade_exp->path = ft_strjoin(good_path, (ft_strjoin("=\"",ft_strjoin(ft_strjoin (value, modif_variable), "\""))));
			new_upgrade_exp->path = ft_strjoin(good_path, (ft_strjoin("=\"",ft_strjoin(value, "\""))));
			free(value);
			free(name_v);
		}
		else if (!current && new_upgrade_exp ) /* SI ON A TROUVE LA NOM VARIABLE ET EST QUE DANS export */
		{
			current = add_node_to_end(enviroment, name_v, value);
			free(new_upgrade_exp->path);
			new_upgrade_exp->path = ft_strjoin(good_path, (ft_strjoin("=\"",
							ft_strjoin(value, "\""))));
			free(value);
			free(name_v);
		}
		else 
		{
			new_variable = (t_envp *)malloc(sizeof(t_envp));
			if (!new_variable)
				return (perror("Memory allocation FAIL"), free(name_v),
					free(value), (void)0);
			new_variable->path = ft_strjoin(name_v, ft_strjoin("=", value));
			new_variable->value = value;
			new_variable->name = name_v;
			new_variable->next = NULL;
			if (*enviroment == NULL)
				*enviroment = new_variable;
			else
			{
				last = *enviroment;
				while (last->next != NULL)
					last = last->next;
				last->next = new_variable;
			}
			new_export = (t_exp *)malloc(sizeof(t_exp));
			if (!new_export)
				return (perror("Memory allocation FAIL"), free(name_v),
					free(value), (void)0);
			good_path = ft_strjoin(name_v, "=\"");
			new_export->value = value;
			new_export->path = ft_strjoin("export ", ft_strjoin(good_path, ft_strjoin(value, "\"")));
			new_export->name = name_v;
			new_export->next = NULL;
			new_current = *export;
			free(good_path);
			if (!new_current)
				new_current = new_export;
			else
			{
				last_exp = new_current;
				while (last_exp->next != NULL)
					last_exp = last_exp->next;
				last_exp->next = new_export;
			}
		}
	}
	else /* AJOUT QUE DANS EXPORT ET CHECK CASES -PRT */
	{
		name_v = ft_strdup(line);
		check_equal = ft_strjoin("export ", ft_strjoin(name_v, "=\""));
		check_name_v = ft_strjoin("export ", name_v);
		while (check_equal_list)
		{
			if (ft_strncmp(check_equal_list->path, check_equal,
					ft_strlen(check_equal)) == 0)
				return (free(check_equal), (void)0);
			if (ft_strncmp(check_equal_list->path, check_name_v,
					ft_strlen(check_name_v)) == 0)
				return (free(check_name_v), (void)0);
			check_equal_list = check_equal_list->next;
		}
		if (!found_equal)
			found_equal = ft_strdup("");
		value = found_equal;
		if (!name_v)
			return (perror("Memory allocation FAIL name_v exp"), free(name_v));
		new_export = (t_exp *)malloc(sizeof(t_exp));
		if (!new_export)
			return (perror("Memory allocation FAIL"), free(name_v));
		new_export->path = ft_strjoin("export ", ft_strjoin(name_v, value));
		new_export->name = ft_strdup(name_v); /* SECURISE */
		new_export->value = ft_strdup(value);/* SECURISE */
		new_export->next = NULL;
		if (*export == NULL)
			*export = new_export;
		else
		{
			last_exp = *export;
			while (last_exp->next != NULL)
				last_exp = last_exp->next;
			last_exp->next = new_export;
		}
	}
}

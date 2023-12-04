/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:28:37 by npaolett          #+#    #+#             */
/*   Updated: 2023/12/04 17:56:03 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/* Il FAUT CREER UN DOSSIER QUE POUR LA COMMANDE ECHO  */

int	found_echo(t_cmd *to_pars)
{
	char	**splits = NULL;

	while (to_pars != NULL)
	{
		if (ft_strcmp(to_pars->cmd, "echo") == 0
			&& ft_strlen(to_pars->cmd) == 4)
			return (1);
		if (ft_strcmp(to_pars->cmd, "echo -n") == 0
			&& ft_strlen(to_pars->cmd) == 7)
			return (2);
		if (ft_strncmp(to_pars->cmd, "echo -", ft_strlen("echo -")) == 0 && !to_pars->next)
		{
			splits = ft_split(to_pars->cmd, ' ');
			printf("%s\n", splits[1]);
			return (0);
		}
		to_pars = to_pars->next;
	}
	return (0);
}

void	ft_echo(t_cmd *to_pars)
{
	char	**splits;

	splits = NULL;
	if (found_echo(to_pars) == 1 && to_pars->next)
		ft_putstr_fd(ft_strjoin(to_pars->next->cmd, "\n"), 1);
	else if (found_echo(to_pars) == 1 && !to_pars->next)
		ft_putstr_fd("\n", 1);
	else if (found_echo(to_pars) == 2 && to_pars->next)
		ft_putstr_fd(to_pars->next->cmd, 1);
}


static int	valid_variable_char(char c)
{
	return (ft_isalpha(c) || c == '_');
}

/* modif mais ne marche pas strcmp pas bonne etc etc  */
char	*find_variable_value(const char *var_name, t_envp *enviroment)
{
	char	*found_egual;
	char	*value;

	value = NULL;
	while (enviroment != NULL)
	{
		if (ft_strcmp(enviroment->name, ft_strjoin(var_name, "=")) == 0)
		{
			found_egual = ft_strchr(enviroment->path, '=');
			value = ft_strdup(found_egual + 1);
			if (!value)
				return (ft_putstr_fd("Fail malloc strdup\n", 2), NULL);
			return (value);
		}
		else
			enviroment = enviroment->next;
	}
	return (NULL);
}



char	*found_chr_forjoin(t_cmd *to_pars)
{
	char	*current;
	int		i;
	int		start;
	char	*found;

	i = -1;
	start = 0;
	found = NULL;
	current = to_pars->next->cmd;
	while (current[++i])
	{
		if (current[i] == '-' || current[i] == '[' || current[i] == ']' || current[i] == '='
			|| current[i] == '{' || current[i] == '}' || current[i] == ':'
			|| current[i] == '/' || current[i] == '.' || current[i] == '+'
			|| current[i] == '@' || current[i] == '#' || current[i] == '!'
			|| current[i] == '?' || current[i] == '~' || current[i] == '^')
		{
			start = i;
			break;
		}
	}
	found = ft_substr(current, start, ft_strlen(current));
	if (found[0] == '$')
		return (NULL);
	else
		return (found);
}

void	found_dollar_print_variable(t_cmd *to_pars, t_envp *enviroment)
{
	char	*commande;
	char	*var_name;
	char	*var_value;
	char	*var_check;
	char	*found;
	int		i;
	int		start;
	int		len;

	i = 0;
	start = 0;
	len = 0;
	var_name = NULL;
	var_value = NULL;
	var_check = NULL;
	found = NULL;
	commande = to_pars->next->cmd;
	if (found_echo(to_pars) == 1) // NO -N 
	{	
		while (commande[++i])
		{
			if (commande[0] == '$' && valid_variable_char(commande[i]))
			{
				start = i;
				while (valid_variable_char(commande[i]))
					++i;
				len = i - start;
				var_name = (char *)malloc(sizeof(char) * len + 1);
				if (!var_name)
					return (ft_putstr_fd("FAIL MALLOC\n", 2), (void)0);
				ft_strlcpy(var_name, commande + start, len + 1);
				var_value = find_variable_value(var_name, enviroment);
				found = found_chr_forjoin(to_pars);
				if (var_value && found)
					return (printf("%s\n", ft_strjoin(var_value, found)), (void)0);
				if (!var_value && found)
					return (printf("%s\n", found), (void)0);
				if (!var_value && !found)
					return (ft_putstr_fd("\n", 1), (void)0);
				return (printf("%s\n", var_value), free(var_name), (void)0);
			}
		}
	}
	if (found_echo(to_pars) == 2) // AVEC -N ECHO -N LOL
	{
		while (commande[++i])
		{
			if (commande[0] == '$' && valid_variable_char(commande[i]))
			{
				start = i;
				while (valid_variable_char(commande[i]))
					++i;
				len = i - start;
				var_name = (char *)malloc(sizeof(char) * len + 1);
				if (!var_name)
					return (ft_putstr_fd("FAIL MALLOC\n", 2), (void)0);
				ft_strlcpy(var_name, commande + start, len + 1);
				var_value = find_variable_value(var_name, enviroment);
				found = found_chr_forjoin(to_pars);
				if (var_value && found)
					return (printf("%s", ft_strjoin(var_value, found)), (void)0);
				if (!var_value && found)
					return (printf("%s", found), (void)0);
				if (!var_value && !found)
					return (ft_putstr_fd("", 1), (void)0);
				return (printf("%s", var_value), free(var_name), (void)0);
			}
		}
	}
	return (ft_echo(to_pars), (void)0);
	/* return ((void)0); QUANDO NON HA PARAMETRI SEGFAULT */
}


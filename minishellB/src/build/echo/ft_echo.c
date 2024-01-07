/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:28:37 by npaolett          #+#    #+#             */
/*   Updated: 2024/01/07 12:28:46 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/* Il FAUT CREER UN DOSSIER QUE POUR LA COMMANDE ECHO  */

int	found_echo(t_cmd *to_pars)
{
	char	**splits;

	splits = NULL;
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
			if (!splits)
				return (ft_free_tab(splits), 0);
			printf("%s\n", splits[1]);
			return (0);
		}
		to_pars = to_pars->next;
	}
	return (0);
}

void	ft_echo(t_cmd *to_pars)
{
	if (found_echo(to_pars) == 1 && to_pars->next)
		ft_putstr_fd(ft_strjoin(to_pars->next->cmd, "\n"), 1);
	if (found_echo(to_pars) == 1 && !to_pars->next)
		ft_putstr_fd("\n", 1);
	if (found_echo(to_pars) == 2 && to_pars->next)
		ft_putstr_fd(to_pars->next->cmd, 1);
}


int	valid_variable_char(char c)
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
		if (ft_strcmp(enviroment->name, var_name) == 0)
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
	current = to_pars->cmd;
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

void	found_echo_with_flag(t_cmd	*arg_cmd, int i, int start, t_envp *enviroment)
{
/* 	int	len; */
	char *arg_value;
/* 	char *var_value;
	char *var_name; */


/* 	len = 0; */
/* 	var_value = NULL;
	var_name  = NULL; */
	while (arg_cmd)
	{
		start = 0;
		i = 1;
		arg_value = arg_cmd->cmd;
		if (arg_value[0] == '$' && valid_variable_char(arg_value[1]))
			logic_print_variable(start, i, enviroment, arg_cmd);
		else
			printf("%s ", arg_value); // Stampa l'argomento
		arg_cmd = arg_cmd->next; // Passa all'argomento successivo
	}
}

void	logic_print_variable(int start, int	i, t_envp *enviroment, t_cmd *arg_cmd)
{
	char	*var_name;
	char	*var_value;
	char	*found;
	int		len;
	char 	*arg_value;

	len = 0;
	start = i;
	arg_value = arg_cmd->cmd;
	while (valid_variable_char(arg_value[i]))
		++i;
	len = i - start;
	var_name = (char *)malloc(sizeof(char) * len + 1);
	if (!var_name)
		return (ft_putstr_fd("FAIL MALLOC\n", 2), (void)0);
	ft_strlcpy(var_name, arg_value + start, len + 1);
	var_value = find_variable_value(var_name, enviroment);
	found = found_chr_forjoin(arg_cmd);
	if (var_value && found) 
		printf("%s ", ft_strjoin(var_value, found));
	if (!var_value && found)
		printf("%s ", found);
	if (var_value && !found)
		printf("%s ", var_value);
}

void	found_echo_not_flag(t_cmd *arg_cmd, int i, int start, t_envp *enviroment)
{
/* 	char	*var_name;
	char	*var_value;
	int		len;

	len = 0;
	var_name = NULL;
	var_value = NULL; */
	if (!arg_cmd)
		return (printf("\n"), (void)0);
	while (arg_cmd)
	{
		start = 0;
		i = 1;
		if (arg_cmd->cmd[0] == '$' && valid_variable_char(arg_cmd->cmd[1]))
			logic_print_variable(start, i, enviroment, arg_cmd);
		else
			printf("%s ", arg_cmd->cmd);
		arg_cmd = arg_cmd->next;
	}
	printf("\n");
}

void found_dollar_print_variable(t_cmd *to_pars, t_envp *enviroment)
{
	int		i;
	int		start;
/* 	int		len; */
	t_cmd	*arg_cmd;

	i = 0;
	start = 0;
/* 	len = 0; */
	while (to_pars)
	{
		if (to_pars->cmd && ft_strcmp(to_pars->cmd, "echo") == 0)
		{
			arg_cmd = to_pars->next;
			if (ft_strcmp(arg_cmd->cmd, "$?") == 0)
				return (printf("%d\n", g_exit_status), (void)0);
			found_echo_not_flag(arg_cmd, i, start, enviroment);
		}
		if (to_pars->cmd && ft_strcmp(to_pars->cmd, "echo -n") == 0)
		{
			arg_cmd = to_pars->next;
			found_echo_with_flag(arg_cmd, i, start, enviroment);
		}
		to_pars = to_pars->next;
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:28:37 by npaolett          #+#    #+#             */
/*   Updated: 2023/12/03 19:56:13 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/* Il FAUT CREER UN DOSSIER QUE POUR LA COMMANDE ECHO  */

int		found_echo(t_cmd *to_pars)
{
	while (to_pars != NULL)
	{
		if (ft_strncmp(to_pars->cmd, "echo", ft_strlen("echo")) == 0
			&& ft_strlen(to_pars->cmd) == 4)
			return (1);
		if (ft_strncmp(to_pars->cmd, "echo -n", ft_strlen("echo -n")) == 0
			&& ft_strlen(to_pars->cmd) == 7)
			return (2);
		to_pars = to_pars->next;
	}
	return (0);
}

void	ft_echo(t_cmd	*to_pars)
{
	if (found_echo(to_pars) == 1 && to_pars->next)
		ft_putstr_fd(ft_strjoin(to_pars->next->cmd, "\n"), 1);
	else if (found_echo(to_pars) == 1 && !to_pars->next)
		ft_putstr_fd("\n", 1);
	if (found_echo(to_pars) == 2 && to_pars->next)
		ft_putstr_fd(to_pars->next->cmd, 1);

}
static int valid_variable_char(char c)
{
    return (ft_isascii(c));
}

/* modif mais ne marche pas strcmp pas bonne etc etc  */

char *find_variable_value(const char *var_name, t_envp *enviroment)
{
	char	*found_egual;
	char	*value;

	value = NULL;
    // BOUCLE POUR TROUVER PATH DANS ENV	
    while (enviroment != NULL)
    {
        if (ft_strncmp(enviroment->path, var_name, ft_strlen(var_name)) == 0)
        {
			found_egual = ft_strchr(enviroment->path, '=');
			value = ft_strdup(found_egual + 1);
			if(!value)
				return (ft_putstr_fd("Fail malloc strdup\n", 2), NULL);
			return (value);
        }
        enviroment = enviroment->next;
    }
    // NOT FOUND 
    return(NULL);
}


/* marche mais il faut reglere des cases particulier comment $ , et echo -n $variable */
void	found_dollar_print_variable(t_cmd *to_pars, t_envp *enviroment)
{
	char	*commande;
	char	*var_name;
	char	*var_value;
	char	*var_check;
	int		i;
	int		start;
	int		len;

	i = 0;
	start = 0;
	len = 0;
	var_name = NULL;
	var_value = NULL;
	var_check = NULL;
	commande = to_pars->next->cmd;
	while(commande[++i])
	{
		if (commande[0] =='$' /* && valid_variable_char(commande[i]) */) /* trouve $ */
		{
				start = i;
				while(valid_variable_char(commande[i]))
					++i;
				len = i - start;
				var_name = (char *)malloc(sizeof(char) * len + 1);
				if (!var_name)
					return(ft_putstr_fd("FAIL MALLOC\n", 2), (void)0);
				ft_strlcpy(var_name, commande + start, len + 1);
				var_check = ft_strrchr(var_name, '-');
				if (!var_check)
					printf("---> %s\n", var_check);
				else
					printf("---> %s\n", var_check);
				printf("var_name ---> %s\n", var_name);
/* 				var_check = ft_strrchr(var_name, '-');
				if (var_check)
					printf("---> %s\n", var_check); */
				var_value = find_variable_value(var_name, enviroment);
				if (!var_value)
					return (ft_putstr_fd("\n", 1), free(var_name), (void)0);
				return (printf("%s\n", var_value),free(var_name), (void)0);
		}
		return (ft_echo(to_pars), (void)0);
	}
}

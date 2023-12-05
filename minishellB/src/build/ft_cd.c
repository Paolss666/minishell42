/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:28:47 by npaolett          #+#    #+#             */
/*   Updated: 2023/12/05 18:00:00 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_cd(t_cmd *to_pars)
{
	while (to_pars != NULL)
	{
		if (ft_strcmp(to_pars->cmd, "cd") == 0)
			return (1);
		to_pars = to_pars->next;
	}
	return (0);
}

char	*found_variable_env(t_envp	*enviroment, char *name_v)
{
	while (enviroment != NULL)
	{
		if (ft_strcmp(enviroment->name, name_v) == 0)
			return (enviroment->path);
		enviroment = enviroment->next;
	}
	return (NULL);
}

t_cd	*cpy_cd_list(char **splits, t_cd *commande_cd)
{
	t_cd	*current;
	t_cd	*envp;
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (splits[++i])
	{
		current = (t_cd *)malloc(sizeof(t_cmd));
		if (!current)
			return (perror("FAIL malloc t_cd"), NULL);
		current->path = ft_strdup(splits[i]);
		printf("t_cd current->name %s\n", current->path);
		if (!current->path)
			return (perror("ft_strdup cpy_cd_list"), NULL);
		current->next = NULL;
		if (!commande_cd)
			commande_cd = current;
		else
		{
			envp = commande_cd;
			while (envp->next != NULL)
				envp = envp->next;
			envp->next = current;
		}
	}
	return (commande_cd);
}

/* JE DOIT IMPLEMENTER D'ABORD LE PIPE E LE PARSING */

void	found_cd_pwd_update(t_cmd *to_pars, t_envp *enviroment, t_exp *export)
{
	char	*current_path_name;
	char	*pwd;
	char	*home;
	t_cd	*commande_cd;

	current_path_name = NULL;
	commande_cd = NULL;
	pwd = found_variable_env(enviroment, "PWD");
	home = found_variable_env(enviroment, "HOME");
	home = ft_substr(home, ft_strlen("HOME="), ft_strlen(home));
	if (!home)
		return (perror("fail ft_substr"));
	printf("%s\n",current_path_name = getcwd(NULL, 0));
	if (ft_cd(to_pars) && !to_pars->next && home)
	{
		if (chdir(home) == 0) /* COMMANDE CD SANS ARGV */
		{
			while(enviroment)
			{
				if (ft_strcmp(enviroment->name, "PWD") == 0)
					break ;
				enviroment = enviroment->next;
			}
			free(enviroment->path);
			free(enviroment->value);
			enviroment->value = ft_strdup(home);
			enviroment->path = ft_strjoin(enviroment->name, ft_strjoin("=", home));
			while(export)
			{
				if (ft_strncmp(export->path, "export PWD", ft_strlen("export PWD")) == 0)
					break ;
				export = export->next;
			}
			free(export->path);
			export->path =  ft_strjoin(ft_strjoin("export ", enviroment->name), (ft_strjoin("=\"",ft_strjoin(home, "\""))));
			if (!export->path || !enviroment->name || !home)
				return(ft_putstr_fd("ERROR FAIL malloc strjoin\n", 2), (void)0);
			free(home);
		}
		perror("FAIL");
	}
	if (ft_cd(to_pars)  && to_pars->next)
	{
		if (chdir(to_pars->next->cmd) == 0)
			printf("%s\n", to_pars->next->cmd);
		else
			perror("FAIL");
	}
	else
		printf("HOME NOT FOUND\n");
}

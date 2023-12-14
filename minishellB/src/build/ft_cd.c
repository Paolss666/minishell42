/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:28:47 by npaolett          #+#    #+#             */
/*   Updated: 2023/12/14 18:13:20 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_cd(t_cmd *to_pars)
{
	while (to_pars != NULL)
	{
		if (ft_strcmp(to_pars->cmd, "cd") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "cd -") == 0)
			return (2);
		to_pars = to_pars->next;
	}
	return (0);
}

char	*found_variable_env(t_envp *enviroment, char *name_v)
{
	while (enviroment != NULL)
	{
		if (ft_strcmp(enviroment->name, name_v) == 0)
			return (enviroment->path);
		enviroment = enviroment->next;
	}
	return (NULL);
}

void	change_env_export_old_pwd(t_envp *enviroment, t_exp *export, char *old_pwd)
{
	if (!enviroment || !export)
		return (ft_putstr_fd("ENV ou EXPO not\n", 2), (void)0);
	if (!old_pwd)
		return ((void)0);
	while (enviroment)
	{
		if (ft_strcmp(enviroment->name, "OLDPWD") == 0)
			break ;
		enviroment = enviroment->next;
	}
	if (!enviroment->next)
		return ((void)0);
	free(enviroment->path);
	free(enviroment->value);
	enviroment->value = ft_strdup(old_pwd);
	if (!enviroment->value)
		return (printf("ft_strdup FAIL\n"),  (void)0);
	enviroment->path = ft_strjoin(enviroment->name, ft_strjoin("=", old_pwd));
	if (!enviroment->path)
		return (printf("ft_strjoin FAIL\n"), (void)0);
	while (export)
	{
		if (ft_strncmp(export->path, "export OLDPWD",
				ft_strlen("export OLDPWD")) == 0)
			break ;
		export = export->next;
	}
	// if (export->next == NULL)
	// 	return ((void)0);
	free(export->path);
	export->path = ft_strjoin(ft_strjoin("export ", enviroment->name),
								(ft_strjoin("=\"", ft_strjoin(old_pwd, "\""))));
	if (!export->path || !enviroment->name || !old_pwd)
		return (ft_putstr_fd("ERROR FAIL malloc strjoin\n", 2),
				(void)0);
	free(old_pwd);
}

void	change_env_export_pwd(t_envp *enviroment, t_exp *export, char *new_pwd)
{
	if (!enviroment || !export)
		return (ft_putstr_fd("ENV ou EXPO not\n", 2));
	while (enviroment)
	{
		if (ft_strcmp(enviroment->name, "PWD") == 0)
			break ;
		enviroment = enviroment->next;
	}
	free(enviroment->path);
	free(enviroment->value);
	enviroment->value = ft_strdup(new_pwd);
	enviroment->path = ft_strjoin(enviroment->name, ft_strjoin("=", new_pwd));
	while (export)
	{
		if (ft_strncmp(export->path, "export PWD",
				ft_strlen("export PWD")) == 0)
			break ;
		// if (!export->next)
			// return ((void)0);
		export = export->next;
	}
	free(export->path);
	export->path = ft_strjoin(ft_strjoin("export ", enviroment->name),
								(ft_strjoin("=\"", ft_strjoin(new_pwd, "\""))));
	if (!export->path || !enviroment->name || !new_pwd)
		return (ft_putstr_fd("ERROR FAIL malloc strjoin\n", 2),
				(void)0);
	// free(new_pwd);
}

t_cd	*cpy_cd_list(char **splits, t_cd *commande_cd)
{
	t_cd	*current;
	t_cd	*envp;
	int		i;

	i = -1;
	while (splits[++i])
	{
		current = (t_cd *)malloc(sizeof(t_cmd));
		if (!current)
			return (perror("FAIL malloc t_cd"), NULL);
		current->path = ft_strdup(splits[i]);
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
	char	*old_pwd;
	char	*line;

	pwd = NULL;
	line  = NULL;
	old_pwd = NULL;
	current_path_name = NULL;
	pwd = getcwd(NULL, 0);
	home = found_variable_env(enviroment, "HOME");
	old_pwd = found_variable_env(enviroment, "OLDPWD");
	old_pwd = ft_substr(old_pwd, ft_strlen("OLDPWD="), ft_strlen(old_pwd));
	home = ft_substr(home, ft_strlen("HOME="), ft_strlen(home));
	if (!home)
		return (perror("fail ft_substr"));
	if (ft_cd(to_pars) == 1 && !to_pars->next && home)
	{
		// printf("on est ici\n");
		if (chdir(home) == 0) /* COMMANDE CD SANS ARGV */
		{
			change_env_export_pwd(enviroment, export, home);
			change_env_export_old_pwd(enviroment, export, pwd);
		}
		else
			ft_putstr_fd("FAIL chdir home path not found\n", 2);
	}
	if (ft_cd(to_pars) && to_pars->next && !to_pars->next->next)
	{
		if (chdir(to_pars->next->cmd) == 0)
		{
			old_pwd = pwd;
			change_env_export_old_pwd(enviroment, export, old_pwd);
			pwd = getcwd(NULL, 0);
			change_env_export_pwd(enviroment, export, pwd);
		}
		else
		{
			ft_putstr_fd(to_pars->next->cmd, 2);
			ft_putstr_fd("  is not a directory\n", 2);
		}
	}
	if (ft_cd(to_pars) == 2 && !to_pars->next)
	{	
		if (chdir(old_pwd) == 0)
		{
			old_pwd = pwd;
			change_env_export_old_pwd(enviroment, export, old_pwd);
			pwd = getcwd(NULL, 0);
			change_env_export_pwd(enviroment, export, pwd);
			line = ft_substr(pwd, ft_strlen(home), ft_strlen(pwd));
			if (!line)
				return(perror("FAIL ft_substr cd"), (void)0);
			line = ft_strjoin("~", line);
			if (!line)
				return (perror("FAIL JOIN line"), (void)0);
			printf("%s\n", line);
		}
		else
			perror("fail chdir ");
	}
	// printf("nous sommes ici\n");
}


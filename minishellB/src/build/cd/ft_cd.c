/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:28:47 by npaolett          #+#    #+#             */
/*   Updated: 2024/01/07 12:29:19 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

char	*found_variable_exp(t_exp *export, char *name_v)
{
	while (export!= NULL)
	{
		if (ft_strcmp(export->name, name_v) == 0)
			return (export->path);
		export = export->next;
	}
	return (NULL);
}

void	found_old_pwd_env_and_modif(t_envp *enviroment, char *old_pwd)
{
	while (enviroment != NULL)
	{
		if (ft_strcmp(enviroment->name, "OLDPWD") == 0)
			break;
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
}

void	found_old_pwd_exp_and_modif(t_exp *export, char *old_pwd)
{
	char	*old_modif;

	while (export!= NULL)
	{
		if (ft_strncmp(export->path, "export OLDPWD", ft_strlen("export OLDPWD")) == 0)
			break;
		export = export->next;
	}
	if (!export->next)
		return((void)0);
	free(export->path);
	free(export->value);
	old_modif = ft_strjoin(old_pwd, "\"");
	if (!old_modif)
		return ((void)0);
	export->value = ft_strjoin("=\"", old_modif);
	if (!export->value)
		return(free(old_modif), (void)0);
	export->path = ft_strjoin("export OLDPWD", export->value);
	if (!export->path)
		return (free(old_modif), free(export->value), (void)0);
	free(old_modif);
}

void	change_env_export_old_pwd(t_envp *enviroment, t_exp *export, char *old_pwd)
{
	if (!enviroment || !export)
		return (ft_putstr_fd("ENV ou EXPO not\n", 2), (void)0);
	if (!old_pwd)
		return(perror("OLDPWD "));
	found_old_pwd_env_and_modif(enviroment, old_pwd);
	found_old_pwd_exp_and_modif(export, old_pwd);
	free(old_pwd);
}

void	found_pwd_in_env_modif(t_envp *enviroment, char *new_pwd)
{
	if(!enviroment || !new_pwd)
		return((void)0);
	while (enviroment)
	{
		if (ft_strcmp(enviroment->name, "PWD") == 0)
			break ;
		enviroment = enviroment->next;
	}
	free(enviroment->path);
	free(enviroment->value);
	enviroment->value = ft_strjoin("=", new_pwd);
	if (!enviroment->value)
		return((void)0);
	enviroment->path = ft_strjoin(enviroment->name, enviroment->value);
	if (!enviroment->path)
		return(free(enviroment->value), (void)0);
}

void	change_env_export_pwd(t_envp *enviroment, t_exp *export, char *new_pwd)
{
	if (!enviroment || !export)
		return (ft_putstr_fd("ENV ou EXPO\n", 2));
	found_pwd_in_env_modif(enviroment, new_pwd);
	while (export)
	{
		if (ft_strncmp(export->path, "export PWD",
				ft_strlen("export PWD")) == 0)
			break ;
		export = export->next;
	}
	free(export->path);
	free(export->value);
	enviroment->value = ft_strjoin(new_pwd, "\"");
	if (!export->value)
		return ((void)0);
	export->value = ft_strjoin("=\"", enviroment->value);
	if (!export->value)
		return (free(export->value), (void)0);
	export->path = ft_strjoin("export PWD",export->value);
	if (!export->path)
		return (free(export->value), (void)0);
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


void found_cd_et_pass(t_cmd *to_pars, t_envp *enviroment, t_exp *export, char *pwd)
{
	char	*old_pwd;

	old_pwd = NULL;
	if (chdir(to_pars->next->cmd) == 0)
	{
		old_pwd = pwd;
		change_env_export_old_pwd(enviroment, export, old_pwd);
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (ft_putstr_fd(to_pars->next->cmd, 2), perror(" :"), (void)0);
		change_env_export_pwd(enviroment, export, pwd);
	}
	else
	{
		ft_putstr_fd(to_pars->next->cmd, 2);
		ft_putstr_fd("  is not a directory\n", 2);
	}
}

void	found_cd_oldpwd(t_exp *export, t_envp *enviroment, char *old_pwd, char *home)
{
	char	*line;
	char	*pwd;

	line = NULL;
	pwd = getcwd(NULL, 0);
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
		perror("fail chdir cd -");
}

void	found_cd_home(t_exp *export, t_envp *enviroment, char *home, char *pwd)
{
	if (chdir(home) == 0)/* COMMANDE CD SANS ARGV */
	{
		change_env_export_pwd(enviroment, export, home);
		change_env_export_old_pwd(enviroment, export, pwd);
	}
	else
		ft_putstr_fd("FAIL chdir home path not found\n", 2);
}

/* JE DOIT IMPLEMENTER D'ABORD LE PIPE E LE PARSING */
void	found_cd_pwd_update(t_cmd *to_pars, t_envp *enviroment, t_exp *export)
{
	char	*pwd;
	char	*home;
	char	*old_pwd;
/* 	char	*line;

	line  = NULL; */
	pwd = getcwd(NULL, 0);
	home = found_variable_env(enviroment, "HOME");
	old_pwd = found_variable_env(enviroment, "OLDPWD");
	old_pwd = ft_substr(old_pwd, ft_strlen("OLDPWD="), ft_strlen(old_pwd));
	home = ft_substr(home, ft_strlen("HOME="), ft_strlen(home));
	if (!home)
		return (perror("fail ft_substr"), (void)0);
	if (ft_cd(to_pars) == 1 && !to_pars->next && home)
		found_cd_home(export, enviroment, home, pwd);
	if (ft_cd(to_pars) && to_pars->next && !to_pars->next->next)
		found_cd_et_pass(to_pars, enviroment, export, pwd);
	if (ft_cd(to_pars) == 2 && !to_pars->next)
		found_cd_oldpwd(export, enviroment, old_pwd, home);
}

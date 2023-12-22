/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_commandes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:11:47 by npaolett          #+#    #+#             */
/*   Updated: 2023/12/18 06:53:43 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/minishell.h"

int	g_exit_status = 0;


char	*display_prompt(void)
{
	char	*line;

	line = readline(COLOR_VIOLET"ADOshell$ "RESET_COLOR);
	add_history(line); // working history
	return (line);
}

// void	init_struct(t_mshell *minishell)
// {
// 	minishell = malloc(sizeof(t_mshell));
// 	if (!minishell)
// 		return ;
// 	minishell->commande = NULL;
// 	minishell->envp = NULL;
// 	// minishell->pid = 0;
// }

void	commande_split_toParse(char **commande_split, char *line)
{
	int	i;

	i = -1;
	commande_split = ft_split(line, ' ');
	if (commande_split)
	{
		// Utilizza un ciclo while per stampare ciascuna stringa fino a NULL
		while (commande_split[++i])
			printf("split %d -> %s\n", i, commande_split[i]);
		ft_free_tab(commande_split);
	}
	return ;
}

void	freeList(t_cmd *head)
{
	t_cmd	*current;
	t_cmd	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->cmd);
		free(current);
		current = next;
	}
}

t_cmd	*free_cmds_list(t_cmd *head)
{
	t_cmd	*history;

	history = head;
	if (history)
	{
		free(history->cmd);
		free(history);
		return NULL;
	}
	else
		return(head);

}

t_exp	*free_exp_list(t_exp *head)
{
	t_exp	*history;

	history = head;
	if (history)
	{
		free(history->path);
		free(history->value);
		free(history->name);
		free(history);
		return NULL;
	}
	else
		return(head);

}

void free_cmd_list(t_cmd *head)
{
	if (head)
	{
		free(head->cmd);
		free(head);
	}
	return ((void)0);

}

/// <<-------- se trovo un flag " - " lo aggiungo alla comanda precedente, anche se ne trovo di piu 
int	join_found_flag(t_cmd **to_pars)
{
	t_cmd	*current;
	t_cmd	*next;
	int		count;
	char	*temp_cmd;

	next = NULL;
	count = 0;
	current = *to_pars;
	if (!*to_pars)
		printf("joind flag to_pars null\n");
	while (current != NULL && current->cmd != NULL)
	{
		next = current->next;
		while (next != NULL && next->cmd != NULL && next->cmd[0] == '-')
		{
			temp_cmd = ft_strjoin(current->cmd, ft_strjoin(" ", next->cmd));
			if (!temp_cmd)
				return (ft_putstr_fd("FAIL trjoin\n", 2), 0);
			free(current->cmd);
			current->cmd = ft_strdup(temp_cmd);
			if (!current->cmd)
				return (ft_putstr_fd("FAIL ft_strdup\n", 2), 0);
			free(temp_cmd);
			current->next = next->next;
			free_cmd_list(next);
			next = current->next;
		}
		count++;
		current = current->next;
	}
	return (count);
}

// --->>>>> toutes les commandes mis dans les listes chainees <<-------- ///

t_cmd	*add_cmd_list(t_cmd *list, char **commande_split, char *line)
{
	t_cmd	*cmd;
	t_cmd	*current;
	int		i;

	i = -1;
	if (!commande_split)
		commande_split = ft_split(line, ' ');
	while (commande_split[++i])
	{
		cmd = (t_cmd *)malloc(sizeof(t_cmd));
		if (!cmd)
			return (perror("FAIL malloc stock_cmd"), NULL);
		cmd->cmd = ft_strdup(commande_split[i]);
		if (!cmd->cmd)
			return (perror("strdup FAIL"), free(cmd), NULL);
		cmd->count = 0;
		cmd->next = NULL;
		if (!list)
			list = cmd; // Se la lista è vuota,il nuovo comando diventa la testa
		else
		{
			current = list;
			while (current->next)
				current = current->next;
			current->next = cmd;
			// Aggiungi il nuovo comando alla fine della lista
		}
		// free(commande_split[i]);
	}
	return (list);
}

void	print_list(t_cmd *head)
{
	t_cmd	*current;

	current = head;
	if (!head)
		printf("test2\n");
	while (current != NULL)
	{
		printf("Command --> : %s\n", current->cmd);
		current = current->next;
	}
}

void free_list_to_pars(t_cmd *to_pars)
{
    t_cmd *current = to_pars;
    t_cmd *next;

    if (!to_pars)
    {
        printf("test2 to_pars == NULL\n");
        return;
    }

    while (current)
    {
        next = current->next;
        free(current->cmd);
        free(current);
        current = next;
    }
	to_pars = NULL;
}


// ----> devo split le line... in modo tale da creare dei segmenti e prendere tutte le commande possibili...
//in modo tale da suddividere tutte le commande.
// --> applicare l'albero di sintaxxxx -->>> non so come <<--------


int	len_liste_envp(t_envp *enviromet)
{
	int	index;

	index = 0;
	if (!enviromet)
		return (0);
	while(enviromet)
	{
		index++;
		enviromet = enviromet->next;
	}
	return (index + 1);
}

int	found_token(t_cmd *to_pars)
{
	if (!to_pars)
		return (printf("to_pars not found\n"), 0);
	while(to_pars)
	{
		if (ft_strcmp(to_pars->cmd, "export") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "unset") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "echo") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "echo -n") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "env") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "cd") == 0)
			return (1);
		if (ft_strcmp(to_pars->cmd, "exit") == 0)
			return (1);
		to_pars = to_pars->next;
	}
	return (0);
}

/// VARIABLE GLOBALE //// 
// --->>>> IL FAUL EMPLEMENTER LA COMMANDE ECHO $? AVEC LE STATUS D'ERROR RENVOYE DEPUIS LA VARIABLE GLOBALE

char	*found_path_envp_list(t_envp *enviroment)
{
	if (!enviroment)
		return (NULL);
	while(enviroment)
	{
		if (ft_strcmp(enviroment->name, "PATH") == 0)
			return (enviroment->path);
		enviroment = enviroment->next;
	}
	return (NULL);
}

void	found_SHLVL(t_envp *enviroment, t_exp *export)
{
	if (!enviroment || !export)
		return ((void)0);
	while(enviroment && export)
	{
		if (ft_strcmp(enviroment->name, "SHLVL") == 0 && ft_strncmp(export->path, "export SHLVL", ft_strlen("export SHLVL")) == 0)
			{
				printf("je suis IN\n");
				enviroment->value = ft_strdup("2");
				printf("enviroment->value %s\n", enviroment->value);
				// printf("export->value --> %s\n", export->value);
				export->value = ft_strdup("2");
				printf("export->value --> %s\n", export->value);
			}
		enviroment = enviroment->next;
		export = export->next;
	}
	return ((void)0);
}

char	*ft_good_path_access(t_cmd	*to_pars, t_envp *enviroment)
{
	char	*exec;
	char	*try_line;
	char	**env_split;
	char 	**with_flag;
	int		i;

	i = 0;
	with_flag= ft_split(to_pars->cmd, ' '); 
	env_split = ft_split(found_path_envp_list(enviroment), ':');
	if (access(with_flag[0], F_OK | X_OK) == 0)
		return (with_flag[0]);
	while(env_split[i])
	{
		if (with_flag)
		{
			try_line = ft_strjoin(env_split[i], "/");
			exec = ft_strjoin(try_line, with_flag[0]);
			free(try_line);
			if (access(exec, F_OK | X_OK) == 0)
				return (exec);
			free(exec);
			i++;
		}
		else
		{	
			try_line = ft_strjoin(env_split[i], "/");
			exec = ft_strjoin(try_line, to_pars->cmd);
			free(try_line);
			if (access(exec, F_OK | X_OK) == 0)
				return (exec);
			free(exec);
			i++;
		}
	}
	return (NULL);
}

char 	**envp_list_to_new_env(t_envp *enviroment)
{
	char	**new_enviroment;
	int		i;

	i = 0;
	new_enviroment = (char **)malloc(sizeof(char *) * len_liste_envp(enviroment) + 1);
	if (!new_enviroment)
		return (NULL);
	if (!enviroment  || len_liste_envp(enviroment) <= 0)
		return (printf("ENV ??? \n"), NULL);
	while(enviroment)
	{
		new_enviroment[i] = ft_strdup(enviroment->path);
		if (!new_enviroment[i])
			return (free(new_enviroment[i]), NULL);
		enviroment = enviroment->next;
		i++;
	}
	new_enviroment[i] = NULL;
	return (new_enviroment);
}

int	main(int ac, char **av, char **env)
{
	// t_mshell	*minishell;
	t_exp		*export;
	char		*line;
	t_cmd		*to_pars;
	char		**commande_split;
	t_envp		*enviroment;
	int			status;
	pid_t		pid;
	int			count;
	char		**new_enviroment;
	char		*good_path_access;

	(void)av;
	to_pars = NULL;
	pid = 0;
	commande_split = NULL;
	// minishell = NULL;
	enviroment = NULL;
	new_enviroment = NULL;
	export = NULL;
	if (ac != 1)
		return (ft_putstr_fd("Don't need arguments\n", 2), 1);
	while (1)
	{
		line = display_prompt();
		count = 0;
/* 		line = epur_str(line); */
		if (!error_manager(line))
		{
			commande_split_toParse(commande_split, line);
			to_pars = add_cmd_list(to_pars, commande_split, line);
			if (!to_pars)
				line = display_prompt();
			count = join_found_flag(&to_pars);
			print_list(to_pars);
/* 			join_found_flag(&to_pars); */
//			printf("<<<<< ---------printf list avec flag --------------- >>\n");
			// printf("found pipe --> %d\n", found_pipe(to_pars));
			// printf("count to_pars --> %d\n", to_pars->count);
			printf("found echo --> %d\n", found_echo(to_pars));
			printf("found cd --> %d\n", ft_cd(to_pars));
			printf("found export --> %d\n", found_export(to_pars));
			printf("found unset --> %d\n", found_unset(to_pars));
			printf("found exit --> %d\n", found_exit(to_pars));
			printf("size list --> %d\n", count);
			printf("<<<<< ---------printf list BUILDING --------------- >>\n");
			if (!enviroment)
				enviroment = found_and_add_env(env, enviroment);
			if (!export)
				export = add_env_with_export(enviroment);
			export_env_sort(export);
			// if (ft_strcmp(to_pars->cmd, "./minishell") == 0)
			// {
			// 	printf("je suis la\n");
			// 	found_SHLVL(enviroment, export);
			// }
			// printf("size envp pour pipex -> %d\n", len_liste_envp(enviroment));
			if (!found_token(to_pars))
			{
				pid = fork();
				if (pid == 0)
				{
					new_enviroment = envp_list_to_new_env(enviroment);
					good_path_access = ft_good_path_access(to_pars, enviroment);
					if (!good_path_access)
						return (ft_error_commande_not_to_pars(to_pars), 0);
					execve(good_path_access, ft_split(line, ' '), new_enviroment);
					perror("execve");
					ft_free_tab(new_enviroment);
				}
			}
			if (pid)
				if (waitpid(pid, &status, 0) == -1)
					perror("waitpid error");
	/* 		if (found_pipe(to_pars) && found_token(to_pars))
				ft_pipex(to_pars, len_liste_envp(enviroment), enviroment, commande_split); */
				printf("je suis la1\n");
			if (found_echo(to_pars) && found_token(to_pars))
				found_dollar_print_variable(to_pars, enviroment);
			if (found_token(to_pars))
				ft_pwd(to_pars);
			if (found_unset(to_pars) && found_token(to_pars))
				unset_delete_variable(to_pars, &enviroment, &export);
			if (!to_pars->next && found_export(to_pars))
				print_export_list(export);
			if (ft_envp(to_pars))
				print_list_envp(enviroment);
			if (found_export(to_pars) && to_pars->next)
				add_export_env(to_pars, &enviroment, &export);
			if (found_exit(to_pars))
				ft_exit(to_pars);
			printf("je suis la2\n");
			if (ft_cd(to_pars) /* && found_token(to_pars) */)
				found_cd_pwd_update(to_pars, enviroment, export);
			to_pars = free_cmds_list(to_pars);
			if (found_echo(to_pars))
				found_dollar_print_variable(to_pars, enviroment);
		}
		to_pars = free_cmds_list(to_pars );
		// free_exp_list(export);
	}
}

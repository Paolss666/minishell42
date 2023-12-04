/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_commandes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:11:47 by npaolett          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/04 15:45:52 by npaolett         ###   ########.fr       */
=======
/*   Updated: 2023/12/04 16:55:03 by npaolett         ###   ########.fr       */
>>>>>>> buildingNico
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*display_prompt(void)
{
	char	*line;

	line = readline("bbshell$ ");
	add_history(line); // working history
	return (line);
}

void	init_struct(t_mshell *minishell)
{
	minishell = malloc(sizeof(t_mshell));
	if (!minishell)
		return ;
	minishell->commande = NULL;
	minishell->envp = NULL;
	// minishell->pid = 0;
}

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

// ---> found a pipe <<--- COMM.pipex

int	found_pipe(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		if (ft_strncmp(cmd->cmd, "|", ft_strlen("|")) == 0)
			return (1);
		cmd = cmd->next;
	}
	return (0);
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
void	join_found_flag(t_cmd **to_pars)
{
	t_cmd	*current;
	t_cmd	*next;
	char	*temp_cmd;

	next = NULL;

	current = *to_pars;
	if (!*to_pars)
		printf("joind flag to_pars null\n");
	while (current != NULL && current->cmd != NULL)
	{
		next = current->next;
		while (next != NULL && next->cmd != NULL && next->cmd[0] == '-')
		{
			// Concatena la stringa corrente con quella successiva
			temp_cmd = ft_strjoin(current->cmd, ft_strjoin(" ", next->cmd));
			// Aggiorna la stringa nella struttura corrente
			free(current->cmd);
			current->cmd = ft_strdup(temp_cmd);
			free(temp_cmd);
			// Rimuove il nodo successivo dalla lista
			current->next = next->next;
			free_cmd_list(next);
			// Resetta il puntatore al nodo successivo
			next = current->next;
		}
		// Passa al prossimo nodo nella lista
		current = current->next;
	}
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
		free(commande_split[i]);
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

int	main(int ac, char **av, char **env)
{
	t_mshell	*minishell;
	t_exp		*export;
	char		*line;
	t_cmd		*to_pars;
	char		**commande_split;
	t_envp		*enviroment;

	(void)av;
	to_pars = NULL;
	commande_split = NULL;
	minishell = NULL;
	enviroment = NULL;
	export = NULL;
	if (ac != 1)
		return (ft_putstr_fd("Don't need arguments\n", 2), 1);
	init_struct(minishell);
	while (1)
	{
		line = display_prompt();
		commande_split_toParse(commande_split, line);
		to_pars = add_cmd_list(to_pars, commande_split, line);
		if (!to_pars)
			line = display_prompt();
		join_found_flag(&to_pars);
		printf("<<<<< ---------printf list NON JOIN flag --------------- >>\n");
		print_list(to_pars);
		join_found_flag(&to_pars);
		printf("<<<<< ---------printf list avec flag --------------- >>\n");
		print_list(to_pars);
		printf("found pipe --> %d\n", found_pipe(to_pars));
		printf("found echo --> %d\n", found_echo(to_pars));
		printf("found cd --> %d\n", ft_cd(to_pars));
		printf("found export --> %d\n", found_export(to_pars));
		printf("found unset --> %d\n", found_unset(to_pars));
		printf("found exit --> %d\n", found_exit(to_pars));
		printf("<<<<< ---------printf list BUILDING --------------- >>\n");
		if (!enviroment)
			enviroment= found_and_add_env(env, enviroment);
		if (!export)
			export = add_env_with_export(enviroment);
		export_env_sort(export);
		if (ft_envp(to_pars))
			print_list_envp(enviroment);
		if (ft_pwd(to_pars) == 1)
			print_pwd(enviroment);
		if (!to_pars->next && found_export(to_pars))
			print_export_list(export);
		if (found_export(to_pars) && to_pars->next)
			add_export_env(to_pars, &enviroment, &export);
		if (found_unset(to_pars))
			unset_delete_variable(to_pars, &enviroment, &export);
		if (found_exit(to_pars))
			ft_exit(to_pars);
		if (found_echo(to_pars))
			found_dollar_print_variable(to_pars, enviroment);
/* 		if (found_echo(to_pars) == 1)
			ft_echo(to_pars);
		if (found_echo(to_pars) == 2)
			ft_echo(to_pars); */
		to_pars = free_cmds_list(to_pars);
		 //<<-------
	}
}
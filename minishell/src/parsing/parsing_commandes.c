/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_commandes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:11:47 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/20 16:02:25 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*display_prompt(void)
{
	char	*line;

	line = readline("minishell$ ");
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

// ---> found a pipe <<--- bisogna vedere come adattarlo a  .pipex

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

void	free_cmd_list(t_cmd *head)
{
	if (head)
	{
		free(head->cmd);
		free(head);
	}
}

// (cmd -lsadasdas) lol lol  <<---- gerer les flags <<====
/// <<-------- se trovo un flag " - " lo aggiungo alla comanda precedente, anche se ne trovo di piu 
void	join_found_flag(t_cmd *to_pars)
{
	t_cmd	*current;
	t_cmd	*prev;
	t_cmd	*next;
	char	*temp_cmd;

	prev = NULL;
	next = NULL;
	current = to_pars;
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
		prev = current;
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
	while (current != NULL)
	{
		printf("Command --> : %s\n", current->cmd);
		current = current->next;
	}
}

// ----> devo split le line... in modo tale da creare dei segmenti e prendere tutte le commande possibili...
//in modo tale da suddividere tutte le commande.
// --> applicare l'albero di sintaxxxx -->>> non so come <<--------

int	main(int ac, char **av, char **env)
{
	t_mshell	*minishell;
	char		*line;
	t_cmd		*to_pars;
	char		**commande_split;
	t_envp		*enviroment;

	(void)av;
	to_pars = NULL;
	commande_split = NULL;
	minishell = NULL;
	enviroment = NULL;
	if (ac != 1)
		return (ft_putstr_fd("Don't need arguments\n", 2), 1);
	init_struct(minishell);
	while (1)
	{
		line = display_prompt();
		printf("--> %s\n", line);
		commande_split_toParse(commande_split, line);
		to_pars = add_cmd_list(to_pars, commande_split, line);
		if (!to_pars)
			printf("-->to_parse est NULL \n");
		printf("<<<<< ---------printf list NON JOIN flag --------------- >>\n");
		print_list(to_pars);
		join_found_flag(to_pars);
		printf("<<<<< ---------printf list avec flag --------------- >>\n");
		print_list(to_pars);
		printf("found pipe --> %d\n", found_pipe(to_pars));
		printf("found pwd --> %d\n", ft_pwd(to_pars));
		printf("found env --> %d\n", ft_envp(to_pars));
		if (ft_envp(to_pars))
		{
			// printf("env----<\n");
			found_and_add_env(env, enviroment);
			print_list_envp(enviroment);
		}
		// freeList(to_pars); //<<-------
	}
}

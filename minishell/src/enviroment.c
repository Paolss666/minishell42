/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:11:47 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/16 14:12:05 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/minishell.h"

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

	// char *commande_to_split;
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
			current->next = cmd;			// Aggiungi il nuovo comando alla fine della lista
		}
	}
	return (list);
}

void printList(t_cmd *head) {
    t_cmd *current = head;

    while (current != NULL) {
        printf("Command --> : %s\n", current->cmd);
        current = current->next;
    }
}

// ----> devo split le line... in modo tale da creare dei segmenti e prendere tutte le commande possibili...
//in modo tale da suddividere tutte le commande.
// --> applicare l'albero di sintaxxxx -->>> non so come <<--------

int	main(int ac, char **av, char **env)
{
	(void)av;
	(void)env;
	t_mshell *minishell;
	char *line;
	t_cmd *to_pars = NULL;
	char **commande_split =NULL;
	minishell = NULL;
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
		printList(to_pars);
		// freeList(to_pars);
	}
}

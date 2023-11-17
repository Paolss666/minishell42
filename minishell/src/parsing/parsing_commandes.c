/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_commandes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:11:47 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/17 17:50:52 by npaolett         ###   ########.fr       */
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

 // ---> found a pipe <<--- bisogna vedere come adattarlo a  .pipex

int	faund_pipe(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		if (ft_strncmp(cmd->cmd, "|", ft_strlen("|")) == 0)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

// (cmd -lsadasdas) lol lol  <<---- gerer les flags <<==== 

// char *faund_flag_commande(char *line)
// {
// 	int	i;

// 	i = -1;
// 	while(line[++i])
// 	{
// 		if (line[i] == ' ' && line[i + 1] == '-')
			
// 	}
// }

void	join_found_flag(t_cmd *to_pars)
{
	t_cmd	*prev;
	t_cmd	*next;

	// printf("%p -> to_pars\n%p -> to_pars.cmd\n%c -> to_pars.cmd[0]\n", to_pars, to_pars->cmd, to_pars->cmd[0]);
	while(to_pars != NULL && to_pars->cmd != NULL)
	{
		next = to_pars->next;
		if (next && next->cmd[0] == '-')
		{
			prev = malloc(sizeof(t_cmd));
			if (!prev)
				return ;
			prev->cmd = (char *)malloc(sizeof(char) + 2);
			if (!prev->cmd)
				return (printf("test1\n"), (void)0); // inizializz prev-cmd char * vuota;
			to_pars->cmd = ft_strjoin(to_pars->cmd, ft_strjoin(" ", next->cmd));
			printf("%s\tcmd\n", to_pars->cmd);
			printf("%p -> to_pars\n%p -> to_pars.cmd\n%c -> to_pars.cmd[0]\n", to_pars, to_pars->cmd, to_pars->cmd[0]);
			// char *temp = ft_strjoin(new_line, to_pars->cmd);
			// free(prev->cmd);
			// to_pars->cmd = temp;
			// tmp = to_pars;
			// prev->next = to_pars->next;
			// free(tmp->cmd);
			// free(tmp)
			// --?? free(to_pars->next->cmd); ?? <<-----
		}
			to_pars = to_pars->next;
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

void	printList(t_cmd *head)
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
	int			clear;

	clear = 0;
	(void)av;
	(void)env;
	to_pars = NULL;
	commande_split = NULL;
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
		printf("<<<<< ---------printf list NON JOIN flag --------------- >>\n");
		printList(to_pars);
		join_found_flag(to_pars);
		printf("<<<<< ---------printf list avec flag --------------- >>\n");
		printList(to_pars);
		printf("found pipe --> %d\n", faund_pipe(to_pars));
		printf("found pwd --> %d\n",ft_pwd(to_pars));
		// freeList(to_pars); //<<-------
	}
}

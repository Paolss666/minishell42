/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npoalett <npoalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:33:51 by npaolett          #+#    #+#             */
/*   Updated: 2024/01/08 21:30:28 by npoalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// void printTripleStringArray(char ***array);


void printTripleStringArray(char ***array) {
    if (!array) {
        printf("Array is NULL\n");
        return;
    }

    // Itera attraverso l'array principale
    for (int i = 0; array[i] != NULL; i++) {
        // Itera attraverso l'array di stringhe corrente
        for (int j = 0; array[i][j] != NULL; j++) {
            printf("%s ", array[i][j]);
        }
        printf("\n");
    }
}

 int	found_count_pipe(t_cmd *cmd)
{
	int	pipe;

	pipe = 0;
	while (cmd != NULL)
	{
		if (ft_strncmp(cmd->cmd, "|", ft_strlen("|")) == 0)
			pipe++;
		cmd = cmd->next;
	}
	return (pipe);
}

char **parseCommand(t_cmd **to_pars)
{
    if (!to_pars || !*to_pars)
        return NULL;

    char **command = NULL;
    t_cmd *temp = *to_pars;

    // Trova la posizione della prossima pipe o della fine della lista
    while (temp && strcmp(temp->cmd, "|") != 0)
        temp = temp->next;
    if (temp)
    {
        // Alloca l'array di stringhe per contenere il comando
        command = (char **)malloc(sizeof(char *) * 2); // +1 per il comando e il terminatore NULL
        if (!command) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        int i = 0;
        t_cmd *temp_cmd = *to_pars;
        while (temp_cmd != temp) {
            command[i] = strdup(temp_cmd->cmd);
            temp_cmd = temp_cmd->next;
            i++;
        }

        command[i] = NULL; // Aggiungi il terminatore NULL
        *to_pars = temp->next; // Imposta la testa della lista alla prossima posizione dopo la pipe
    } 
    else
    {
        // Nessuna pipe trovata, considera tutto il resto della lista come un comando
        // Alloca l'array di stringhe per contenere il comando
        command = (char **)malloc(sizeof(char *) * 2); // +1 per il comando e il terminatore NULL
        if (!command) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }
        int i = 0;
        t_cmd *temp_cmd = *to_pars;
        while (temp_cmd) {
            command[i] = strdup(temp_cmd->cmd);
            temp_cmd = temp_cmd->next;
            i++;
        }
        command[i] = NULL; // Aggiungi il terminatore NULL
        *to_pars = NULL;   // Imposta la testa della lista a NULL
    }
    return command;
}

char ***found_pipw_for_parse_commands(t_cmd *to_pars)
{
    char ***commands = NULL;
    int command_count = 0;

	if (!to_pars)
        return NULL;
    // Calcola il numero di comandi
    t_cmd *temp = to_pars;
    while (temp) {
        if (ft_strcmp(temp->cmd, "|") == 0) {
            command_count++;
        }
        temp = temp->next;
    }
    if (command_count == 0) {
        // Nessuna pipe trovata, ritorna un char *** con un singolo elemento
        commands = (char ***)malloc(sizeof(char **) * 2); // +1 per l'ultimo comando e il terminatore NULL
        if (!commands) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }
        commands[0] = parseCommand(&to_pars);
        commands[1] = NULL;
        return commands;
    }
    // Alloca l'array di stringhe triplo
    commands = (char ***)malloc(sizeof(char **) * (command_count + 2)); // +2 per l'ultimo comando e il terminatore NULL
    if (!commands) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    int i = 0; // Indice per l'array principale
    while (to_pars)
	{
        char **command = parseCommand(&to_pars);
        if (command) {
            commands[i] = command;
            i++;
        }
    }
    // Aggiungi il terminatore null all'ultimo elemento dell'array principale
    commands[i] = NULL;
    return commands;
}

int     ft_execve(t_cmd *to_pars, t_envp *enviroment /* char *line */)
{
    char		*good_path_access;
    char		**new_enviroment;
    pid_t		pid[1024];
    int         status;
	int			fd[2];
	int			tmp_fd;
	int			n_pipe;
	int			i;

	i = -1;
	tmp_fd = 0;
	n_pipe = found_count_pipe(to_pars) + 1;
	new_enviroment = envp_list_to_new_env(enviroment);
	good_path_access = ft_good_path_access(to_pars, enviroment);
	if (!good_path_access)
		return (ft_error_commande_not_to_pars(to_pars), 0);
	 char ***avant_pipe = found_pipw_for_parse_commands(to_pars);
	 printTripleStringArray(avant_pipe);
	while(++i < n_pipe)
	{
		if (pipe(fd) == -1)
			perror("pipe error");
		pid[i] = fork();
		if (pid[i] == -1)
			perror("fork error");
		if (pid[i] == 0)
			child(to_pars, new_enviroment, i, good_path_access,tmp_fd,  fd);
		else
			parent(fd, i, tmp_fd);
	}
	i = 0;
	while(i < n_pipe)
			if (waitpid(pid[i++], &status, 0) == -1)
				perror("waitpid error");
    return (0);
}


void	redirection(int *fd, int tmp_fd, int i, int n_pipe)
{
	int	fd_1;

	fd_1 = 0;
	if (i == 0)
	{
		dup2(fd_1, 0);
		close(fd_1);
	}
	if (i == n_pipe)
	{
		dup2(fd_1, 1);
		close(fd_1);
	}
	if (i != 0)
	{
		dup2(tmp_fd, 0);
		close(tmp_fd);
	}
	if(i != n_pipe)
		dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);

}

void	child(t_cmd *to_pars, char **enviroment, int i, char *get_good_path, int tmp_fd, int *fd)
{
	char ***good_commande;
	int		n_pipe = found_count_pipe(to_pars);

	good_commande = NULL;
	good_commande = found_pipw_for_parse_commands(to_pars);
	redirection(fd, tmp_fd, i, n_pipe);
/* 	if (dup2(fd[1], 1) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1)
		perror("fdfdf error"); */
	execve(get_good_path, good_commande[i], enviroment);
	perror("execve error");
}


void		parent(int *fd,  int i, int tmp_fd)
{
/* 	if (dup2(fd[0], 0) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1)
		perror("error"); */
	close(fd[1]);
	if (i)
		close(tmp_fd);
	tmp_fd = fd[0];
}

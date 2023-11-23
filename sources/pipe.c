/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:36:18 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/04 00:36:26 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//(if (j != 0)) s'execute seulement si le processus actuel n'est pas le premier dans la 
	//sequence de pipes (c'est a dire, s'il a un processus precedent). 
	//dup2(fd[(j - 1) * 2], 0) redirige l'entree standard (stdin, descripteur de fichier 0) 
	//du processus actuel vers le descripteur de fichier de lecture du pipe du processus 
	//precedent (fd[(j - 1) * 2]).
	//Si dup2 echoue (retourne une valeur negative), le processus enfant quitte 
	//immediatement avec le code d'erreur 1.

//(if (temp->next)) s'execute seulement si le processus actuel n'est pas le dernier dans 
	//la sequence de pipes (c'est a dire, s'il y a un processus suivant).
	// dup2(fd[j * 2 + 1], 1) redirige la sortie standard (stdout, descripteur de fichier 1) 
	//du processus actuel vers le descripteur de fichier d'ecriture du pipe du processus 
	//suivant (fd[j * 2 + 1]).
	// Si dup2 echoue (retourne une valeur negative), le processus enfant quitte 
	// immediatement avec le code d'erreur 1.
// Ainsi, le premier processus va ecrire sa sortie dans le ficier d'ecriture (pipe[1]), ensuite
	// le second processus, va lire dans le fichier de lecture (pipe[0]) pour lire la commande
	// (on change son entree donc) et va donc se servir de sa lecture pour executer sa commande a elle
// on ferme ensuite tous les fd associes aux pipes
// on recupere le contenu de la commande qu'on decoupe avec des espaces en delimiteur
// ensuite, on recupere la path pour obtenir le chemin d'execution complet avec find_path
// enfin, execve pour justement executer le programme, a partir de la path complete ou on lui donne
	// le chemin d'acces vers le fichier, la commande et le tableau d'env sous forme variable=valeur

void	exec_pipe(int *fd, int j, t_list *temp, t_envp *s_envp)
{
	int		i;
	char	**cmd;
	char	*path;

	if (j != 0)
		if (dup2(fd[(j - 1) * 2], 0) < 0)
			exit(1);
	if (temp->next)
		if (dup2(fd[j * 2 + 1], 1) < 0)
			exit(1);
	i = -1;
	while (fd[++i])
		close(fd[i]);
	cmd = ft_split(temp->content, ' ');
	path = find_path(cmd[0]);
	if (execve(path, cmd, s_envp->env_array) != 0)
	{
		g_error = 127;
		ft_putstr_fd("Could not execute command", 1);
		exit(g_error);
	}
	free(path);
	ft_free_str(cmd);
	exit(g_error);
}

// om parcourt la liste chainee comportant les differentes partie de la commande
// pour chaque element de la liste, pendant qu'on est dans le parent, on implemente le gestionnaire
	// de signal pour ce processus
// puis pour chaque element de la liste, on cree un process enfant
// si on est dans le process enfant, on installe le gestionnaire de signal specifique pour les process
	// enfants, et on appelle exec_pipe(), qui va executer la partie specifique de la commande 
	// associee a ce process enfant, en lui envoyant le tableau de fd, un index "j" pour parcourir
	// le tableau de fd, mais surtout pour suivre le numero du processus dans la sequence de pipes,
	// la partie specifique de la commande et le tableau d'env
// le free(temp) n'est peut etre pas necessaire a la fin, car il pointe a la fin vers le dernier
	// element de la liste
static void	split_pipe(int *pipe_fd, t_list *pipe_commands, t_envp *s_envp)
{
	int		j;
	int		pid;
	t_list	*temp;

	j = 0;
	temp = pipe_commands;
	while (temp)
	{
		ft_signals(1);
		pid = fork();
		if (pid == 0)
		{
			ft_signals(2);
			exec_pipe(pipe_fd, j, temp, s_envp);
		}
		temp = temp->next;
		j++;
	}
	free(temp);
}

// on va allouer de la memoire pour stocker les descripteurs de fichier pour chaque pipe
// chaque pipe aura son descripteur de fichier d'ecriture, et de lecture
// avec pipe(), on cree des tubes qui vont permettre la communication entre deux processus
// par exemple, le premier processus va ecrire sa sortie de commande dans un pipe, puis le second
	// processus, avec son descripteur de lecture, va lire les donnees renvoyees par le precedent
	// processus a partir de ce pipe
// c'est comme ca que marche les pipes : les donnees ecrites dans un cote du du pipe peuvent etre
	// lues a partir de l'autre cote du pipe
// ainsi, pour un pipe par exemple, on a pipe[0] = fd de lecture et pipe[1] fd d'ecriture
// on appelle ensuite split_pipe, qui va executer les differentes parties de la commande en utilisant
	// les tubes, on lui envoie le tableau de descripteur, la liste contenant les commandes et le tableau
	// d'env
void	pipe_handler(t_list **pipe_list, int countpipe, t_envp *s_envp)
{
	int	i;
	int	*pipe_fd;

	i = -1;
	pipe_fd = (int *)malloc(sizeof(int) * countpipe * 2);
	while (++i < countpipe)
	{
		if (pipe(pipe_fd + i * 2) < 0)
			exit(1);
	}
	split_pipe(pipe_fd, (*pipe_list), s_envp);
	i = -1;
	while (++i < 2 * countpipe)
		close(pipe_fd[i]);
	countpipe++;
	while (countpipe--)
		waitpid(0, &g_error, WUNTRACED);
	if (WIFEXITED(g_error))
		g_error = WEXITSTATUS(g_error);
	else
		g_error = 0;
	if (pipe_fd[0] != '\0')
		free(pipe_fd);
}

// on declare une liste de pipe, qui va contenir nos futurs parties de la commande contenant les pipes
// apres avoir initalisee on decoupe la commande par |, qu'on stocke dans un tableau
// add_list va stocker les commandes du tableau dans une liste chainee, parce que pratiquer un peu
	// les listes chainees, c'est bien aussi !
// on appelle pipe_handler qui va gerer l'exec des commandes avec les pipes
// on free nos tableaux
void	run_pipe(char *str, int n_pipe, t_envp *s_envp)
{
	char	**pipe_array;
	t_list	**pipe_list;

	pipe_list = (t_list **)malloc(sizeof(char *) * 100);
	*pipe_list = NULL;
	pipe_array = ft_split(str, '|');
	add_list(pipe_array, pipe_list);
	pipe_handler(pipe_list, n_pipe, s_envp);
	ft_free_list(pipe_list);
	ft_free_str(pipe_array);
}

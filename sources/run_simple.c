/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simple.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:55:55 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/04 00:57:05 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// fonction qui va executer la commande dans l'enfant
// - on check d'abord la str devant le nom de la commande contient un $, si c'est le cas on
	// manipulera des variables d'environnement, on recup ainsi la valeur d'env avec getenv
	// + ft_strim pour enlever le dollar au debut, on libere l'ancienne valeur et on le remplace
	// dans le tableau par la valeur qu'on a trouve dans env
// - on met dans la variable path la valeur de retour de la fonction find_path, qui va nous
	// renvoyer la path exacte de la commande
// - c'est ensuite avec execve qu'on va executer le programme a partir de la variable path
	// on lui donne le chemin d'acces vers le fichier, parse qui est la commande en lui
	// meme et le tableau des variables d'env sous forme variable=valeur
// - un petit kill() qui va envoyer un signal de terminaison (SIGTERM) au processus qui execute
	// la commande (l'enfant) pour teminer le processus actuel, par securite, meme si nornalement
	// le processus sera automatiquement arrete apres l'appel d'execve(), qu'il reussise ou pas

void	run_child(char **parse, t_envp *s_envp)
{
	char	*env_value;
	char	*path;

	if (parse[1] && parse[1][0] == '$')
	{
		env_value = getenv(ft_strtrim(parse[1], "$"));
		free(parse[1]);
		parse[1] = ft_strdup(env_value);
	}
	path = find_path(parse[0]);
	if (execve(path, parse, s_envp->env_array) != 0)
	{
		g_error = 127;
		ft_putstr_fd("Command not found.\n", 1);
		exit(g_error);
	}
	kill(getpid(), SIGTERM);
}

// - fonction pour executer les commandes simples (sans pipes ou redirections)
// - on divise la commande en mots individuels qu'on stock dans le tableau commands avec split
// - on cree le processus enfant avec fork, car c'est comme ca que ca marche dans un shell,
	// c'est le processus enfant qui execute les commandes en general
// - si la creation echoue, message d'erreur + code de sortie 127 (commande non trouvee)
// - sinon, on est dans le process enfant, on execute la commande
// - apres ca on appelle waitpitd() avec le pid de l'enfant, pour attendre que le process enfant
	// se termine, le code de sortie de ce dernier est stockee dans g_error
// - on utilise la macro WIFEXITED pour verifier justement si un processus s'est termine
	// normalement, en analysant le statut de g_error renvoye par le process enfant
// - si ca s'est termine normalement, on assigne le code renvoye par le process enfant a
	// g_error, sinon on met g_error a 0, puis on free notre tableau qu'on a split

void	run_simple(char *str, t_envp *s_envp)
{
	pid_t	pid;
	char	**commands;

	commands = ft_split(str, ' ');
	pid = fork();
	if (pid < 0)
	{
		g_error = 127;
		ft_putstr_fd("Error : failed to create a child process.\n", 1);
	}
	else if (pid == 0)
		run_child(commands, s_envp);
	waitpid(pid, &g_error, 0);
	if (WIFEXITED(g_error))
		g_error = WEXITSTATUS(g_error);
	else
		g_error = 0;
	ft_free_str(commands);
}

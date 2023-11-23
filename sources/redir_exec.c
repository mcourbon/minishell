/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:38:32 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/04 00:38:50 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// on appelle ft_signals(2), 2 car on est dans l'enfant
// on appelle dup2() qui va permettre de dupliquer un descripteur de fichier existant vers un
	// autre descripteur de fichier existant
// ainsi, dup2 ici va nous permettre de rediriger sortie/entree standard vers un nouveau descripteur
	// de fichier, c'est a dire que new_fd (1 sortie standard, 0 entree standard) va pointer vers le
	// meme fichier que "fd", les deux fichiers vont pointer vers le meme fichier ouvert
// enfin, on analyse la commande en lancant les commandes dans la redirection, au cas ou ce serait
	// des commandes, builtins ou pipes.

void	exec_redir(char *str, int fd, int new_fd, t_envp *s_envp)
{
	int		n_pipe;

	ft_signals(2);
	n_pipe = count(str, '|');
	dup2(fd, new_fd);
	close(fd);
	if (n_pipe)
		run_pipe(str, n_pipe, s_envp);
	else if (is_builtin(str))
		run_builtin(str, s_envp);
	else
		run_simple(str, s_envp);
	exit(g_error);
}

// la fonction va creer un processus enfant pour executer la redirection, car c'est comme ca que 
	// cela marche, c'est pas le processus principal (shell lui meme) qui execute les commandes 
	// entrees par l'utilisateur, mais ce dernier va creer un processus enfant qui va l'executer
	// ca permet une meilleur gestion des taches et etvite de bloquer le shell pendant l'exec d'une
	// commande longue par exemple. apres bien sur, il est possible que certaines commandes soit
	// executees par le process parent directement, comme des "cd", car ils vont affecter direcement
	// les repertories du process parent
// - si la creation echoue, message d'erreur + code de sortie 127 (commande non trouvee)
// - sinon, on est dans le process enfant, on execute la exec_redir
// - apres ca on appelle waitpitd() avec le pid de l'enfant, pour attendre que le process enfant
	// se termine, le code de sortie de ce dernier est stockee dans g_error
// - on utilise la macro WIFEXITED pour verifier justement si un processus s'est termine
	// normalement, en analysant le statut de g_error renvoye par le process enfant
// - si ca s'est termine normalement, on assigne le code renvoye par le process enfant a
	// g_error, sinon on met g_error a 0
void	exec_dir(char *str, int fd, int new_fd, t_envp *s_envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		g_error = 127;
		ft_putstr_fd("Failed forking child", 1);
	}
	else if (pid == 0)
		exec_redir(str, fd, new_fd, s_envp);
	waitpid(0, &g_error, 0);
	if (WIFEXITED(g_error))
		g_error = WEXITSTATUS(g_error);
	else
		g_error = 0;
}

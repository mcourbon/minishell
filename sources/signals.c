/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shifterpro <shifterpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 01:19:32 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/23 14:14:15 by shifterpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// - fonction qui gere Ctr + C et Ctrl + backslash dans un process enfant
// - Ctrl + C = on renvoie 130 puis saut de ligne, classique
// - Ctrl + Backslash = on renvoie 131 (SIQUIT) + Quit Child, le msg pas obligatoire

static void	handler_child(int signum)
{
	if (signum == SIGINT)
	{
		g_error = 130;
		write(1, "\n", 1);
	}
	if (signum == SIGQUIT)
	{
		g_error = 131;
		write(1, "\n", 1);
		ft_putendl_fd("Quit Child\n", 1);
	}
}

// - fonction qui gere le signal Ctrl + C dans le process parent
// - on met a jour le code erreur a 130 qui indique l'arret d'un process avec SIGINT
// - on simule un Ctrl + C --> onsaute une ligne avec write, on replace le curseur de readline
	// au debut de la ligne actuelle avec rl_on_new_line(), puis avec rl_replace_line() on
	// remplace la ligne actuelle par "", donc rien, et rl_redisplay(), qu'on met en general
	// apres avoir aples rl_replace_line, qui permet l'affichage immmediat de la nouvelle ligne 

static void	handler_main(int signum)
{
	(void)signum;
	g_error = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// - foncion pour configurer la gestion de signaux selon le signum
// - si le signum est 1, on gere le SIG_INT (Ctr + C) dans le parent et on ignore SIGQUIT
	// (Ctr+\) car dans le parent, c'est a dire le shell lui meme, c'est cense rien faire
// - si le signum est 2, on gere les signaux SIGINT ET SIGQUIT dans les process enfants
void	ft_signals(int signum)
{
	if (signum == 1)
	{
		signal(SIGINT, handler_main);
		signal(SIGQUIT, SIG_IGN);
	}
	if (signum == 2)
	{
		signal(SIGINT, handler_child);
		signal(SIGQUIT, handler_child);
	}
}

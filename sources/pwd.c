/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:36:42 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/04 00:38:20 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// fonction pour gerer le builtin pwd
// getcwd() est utilse pour justement recuperer le repertoire courant
// de base, getcwd() prend en parametre un buffer qui va contenir le repertoire courant, et
	// la size du buffer, mais en faisant seulement (NULL, 0), ca va permettre a la fonction
	// de gerer automatiquement l'allocation de memoire pour le chemin du repertoire de travail
// si on a pu obtenir le repertoire courant (temp non NULL), on affiche le chemin absoulu et
	// on free temp, puisque getcwd a utilise malloc() pour gerer tout ca
// sinon erreur
void	run_pwd(char *temp)
{
	temp = getcwd(NULL, 0);
	if (temp)
	{
		ft_putendl_fd(temp, 1);
		free(temp);
		g_error = 0;
	}
	else
	{
		ft_putendl_fd("Error occured !", 1);
		g_error = 127;
	}
}

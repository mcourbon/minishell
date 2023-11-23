/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:35:30 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/04 00:36:09 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// - cette fonction recoit la str saisi par l'utilisateur, va l'analyser et va determiner quel
	// type de traitement appliquer en fonction des caracteres speciaux dans la commande
	// (pipe, redirection, builtin etc...)

void	parsing_command(char *str, t_envp *s_envp)
{
	int	n_pipe;
	int	n_squote;
	int	n_dquote;
	int	n_redir_out;
	int	n_redir_in;

	n_pipe = count(str, '|');
	n_squote = count(str, '\'');
	n_dquote = count(str, '\"');
	n_redir_out = count(str, '>');
	n_redir_in = count(str, '<');
	if ((n_redir_out > 0 || n_redir_in > 0) && (n_squote == 0 && n_dquote == 0))
		run_redir(str, s_envp);
	else if ((n_pipe > 0) && (n_redir_out == 0 && n_redir_in == 0))
		run_pipe(str, n_pipe, s_envp);
	else if (is_builtin(str) > 0)
		run_builtin(str, s_envp);
	else
		run_simple(str, s_envp);
}

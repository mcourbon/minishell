/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:15:37 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/03 23:16:08 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// fonction qui va analyser la commande envoyee et envoyer un id en fonction, avec ft_strncmp
	// sauf pour is_echo ou on a parsing specifique puisqu'il faut gerer les guillemets

int	is_builtin(char *temp)
{
	if (temp == NULL)
		return (0);
	if (is_echo(temp))
		return (1);
	else if (!ft_strncmp(temp, "cd", 2))
		return (2);
	else if (!ft_strncmp(temp, "pwd", 3))
		return (3);
	else if (!ft_strncmp(temp, "export", 6))
		return (4);
	else if (!ft_strncmp(temp, "unset", 5))
		return (5);
	else if (!ft_strncmp(temp, "env", 3))
	{
		g_error = 127;
		return (6);
	}
	else if (!ft_strncmp(temp, "exit", 4))
		return (7);
	return (0);
}

// - fonction qui va s'occuper de lancer les fonctions qui vont executer les builtins,
	// selon l'id renvoye par la fonction de parsing is_builtin
void	run_builtin(char *str, t_envp *s_envp)
{
	char	*temp;
	int		id;

	temp = ft_strtrim(str, " ");
	id = is_builtin(temp);
	if (id == 1)
		run_echo(str, s_envp);
	else if (id == 2)
		run_cd(temp);
	else if (id == 3)
		run_pwd(temp);
	else if (id == 4)
		run_export(str, s_envp);
	else if (id == 5)
		run_unset(str, s_envp);
	else if (id == 6)
		run_env(s_envp->env_array);
	else if (id == 7)
		exit(0);
	free(temp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:42:52 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/04 00:55:38 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// on recoit le tableau avec l'index dans laquelle se trouve la redirection, et on check le
	// cas ou le prochain argument n'est pas un fichier (donc NULL, ou si le fichier commence par
	// une redirection, c'est erreur)
// sinon, on appel les fonctions qui vont gerer les redirections selon si c'est un single ou
	// un double, avec notamment l'index ou on a trouvee la redirection
int	redir_out(char **str, int i, t_envp *s_envp)
{
	if (str[i + 1] == NULL || str[i + 1][0] == '<' || str[i + 1][0] == '>' ||
		str[i + 1][0] == '\0')
	{
		ft_putendl_fd("Syntax error", 2);
		g_error = 2;
		return (1);
	}
	if (!ft_strcmp(str[i], ">"))
	{
		redir_out_handle(str, i, s_envp);
		return (0);
	}
	else if (!ft_strcmp(str[i], ">>"))
	{
		redir2_out_handle(str, i, s_envp);
		return (0);
	}
	return (1);
}

// redir_in va appeler redir_in_handle ou redir2_in_handle en fonction du type de redirection
	// c'est a dire double ou single, on check aussi si la valeur d'apres n'est pas null
int	redir_in(char **str, int i, t_envp *s_envp)
{
	if (str[i + 1] == NULL || str[i + 1][0] == '<' || str[i + 1][0] == '>' ||
		str[i + 1][0] == '\0')
	{
		ft_putendl_fd("Syntax error", 2);
		g_error = 2;
		return(1);
	}
	if (!ft_strcmp(str[i], "<"))
	{
		redir_in_handle(str, i, s_envp);
		return (0);
	}
	else if (!ft_strcmp(str[i], "<<"))
	{
		redir2_in_handle(str, i, s_envp);
		return (0);
	}
	return (1);
}

// la fonction va diviser la commande de redirection avec comme delimiteur l'espace
// on parcourt le tableau, et on apppelle redir_out ou redir_in en fonction du type de redirection
// ft_strcmp qui renvoyera 0 si une chaine est egale a l'autre
void	run_redir(char *str, t_envp *s_envp)
{
	int		i;
	char	**commands;

	i = 0;
	commands = ft_split(str, ' ');
	while (commands[i])
	{
		if ((!ft_strcmp(commands[i], ">") || !ft_strcmp(commands[i], ">>")))
		{
			redir_out(commands, i, s_envp);
			break ;
		}
		else if ((!ft_strcmp(commands[i], "<") || \
		!ft_strcmp(commands[i], "<<")))
		{
			redir_in(commands, i, s_envp);
			break ;
		}	
		i++;
	}
	ft_free_str(commands);
}

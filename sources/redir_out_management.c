/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:40:57 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/04 00:42:28 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// la fonction qui va renvoyer l'index du dernier fichier de sortie
// on parcourt le tableau de commandes et on check a chaque fois si la valeur actuel et une redir
	// ">" qu'il y a un fichier apres, si c'est le cas on ouvre le fichier avec le nom specifie
	// par str[pos - 1] (qui est le precedent fichier), on le cree si il existe pas
// sachant qu'on parcourt 2 par 2 (car ca fait > file > file < file par exemple), on check si 
// la redirection en question est le dernier, en regardant 2 emplacements apres
// si c'est NULL, c'est que c'etait le dernier fichier et la derniere redir, on retoure l'index
	// ou on a trouve la derniere redir pour pouvoir choper le dernier fichier de sortie
int	check_another_redir(char **str, int i)
{
	int		pos;

	pos = i + 2;
	while (str[pos])
	{
		if (str[pos + 1] && (ft_strncmp(str[pos], ">", 1) == 0 || \
			ft_strncmp(str[pos], ">>", 2) == 0))
		{
			open(str[pos - 1], O_CREAT, 0777);
			if (str[pos + 2] == NULL)
			{
				i = pos;
				break ;
			}
		}
		pos = pos + 2;
	}
	return (i);
}

// exactement le meme que redir2_out_handle, sauf qu'on change cette fois le flag, en remplacant
	// le mode "O_APPEND" par "O_TRUNC", ce dernier qui va vider le fichier a 0 octet lors
	// de l'ouverture en ecriture
void	redir_out_handle(char **str, int i, t_envp *s_envp)
{
	char	*temp;
	int		fd;
	int		flags;
	char	*file;

	temp = sub_redir(str, i);
	flags = O_WRONLY | O_CREAT;
	if (str[i + 2])
		i = check_another_redir(str, i);
	file = ft_strdup(str[i + 1]);
	fd = open(file, flags | O_TRUNC, 0777);
	exec_dir(temp, fd, 1, s_envp);
	if (temp[0] != '\0')
		free(temp);
	if (file[0] != '\0')
		free(file);
}

// fonction qui va appeler les fonctions pour gerer les redirections
// on stocke les flags O_WRONLY | O_CREAT dans une variable "flags" pour l'ouverture du fichier selectionne
// on met dans temp ce que nous retourne sub_redir(), qui va nous renvoyer la commande sous un string
	// (qui de base est dans tableau separee par des espasces)
// on check si y'a d'autres redirections avec check_another_redir() qui va nous renvoyer
	// l'index du dernier fichier ou les sorties doivent etre redirigees
// on stocke dans "file" le fichier ou l'on souhaite effectuer des operations
// on ouvre le fichier avec tous les droits, on rajoute le flag O_APPEND pour activer le mode ajout
	// (place le curseur du fichier a la fin du fichier lors de chaque operation d'ecriture)
// on appelle ensuite exec_dir() avec la commande entiere, le fichier, la sortie standard pour dup2,
	// et le tableau d'env
void	redir2_out_handle(char **str, int i, t_envp *s_envp)
{
	char	*temp;
	int		fd;
	int		flags;
	char	*file;

	flags = O_WRONLY | O_CREAT;
	temp = sub_redir(str, i);
	if (str[i + 2])
		i = check_another_redir(str, i);
	file = ft_strdup(str[i + 1]);
	fd = open(file, flags | O_APPEND, 0777);
	exec_dir(temp, fd, 1, s_envp);
	if (temp[0] != '\0')
		free(temp);
	if (file[0] != '\0')
		free(file);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:39:01 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/04 01:45:23 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// on ouvre le fichier en mode lecture et ecriture
// on ouvre le fichier temporaire
// on met la ligne a vide pour le moment, qui contiendra la ligne entree par l'user avec readline
// on rentre la boucle du heredoc, dans la ligne ecrite n'est pas egal au EOF
// on free la line qui contient le malloc du strdup, on met dans line l'input de l'utilisateur
	// et on affiche cette derniere dans le fichier temporaire
// si justement la line == EOF, on sort de la boucle, on ferme le fd temporaire, on va le reouvrir plus tard
	// toute facon (dans redir2 handle)
// on free la line (readline)
void	here_doc(char *file, char *eof)
{
	char	*line;
	int		flags;
	int		fd_temp;

	flags = O_RDWR | O_CREAT | O_TRUNC;
	line = ft_strdup("");
	fd_temp = open(file, flags, 0777);
	while (ft_strcmp(line, eof))
	{
		free(line);
		line = readline("> ");
		if (line && ft_strcmp(line, eof))
			ft_putendl_fd(line, fd_temp);
		else
			break ;
	}
	close(fd_temp);
	free(line);
}

// gerer le cas ou il y a une redirection vers un fichier dans le heredoc 
// on duplique la sortie standard pour le sauvegarder et le restaurer plus tard
// on ouvre le dernier fichier de la commande
// on redirige la sortie standard vers le nouveau fichier
// on close le fichier, on a plus besoin car c'est bon on a redirige la sortie standard vers le fichier
// on exec ainsi la commande avec la temp contenant la commande, le fichier de sortie fianl, l'entree standard
	// et le tablea d'env
// enfin, on retablit la sortie standard d'origine en dupliquant le fd sauvegarde, avant de le fermer
void	mixed_redir(char *str, char *temp, int fd, t_envp *s_envp)
{
	int		fdd;
	int		stdout_copy;

	stdout_copy = dup(1);
	fdd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(fdd, 1);
	close(fdd);
	exec_dir(temp, fd, 0, s_envp);
	dup2(stdout_copy, 1);
	close(stdout_copy);
}

// rien ne change avec mixed_redir, sauf qu'on gere >>, donc le seul truc qui change c'est
	// dans les flags d'ouverture, O_APPEND	a la place de O_TRUNC
void	mixed_redir2(char *str, char *temp, int fd, t_envp *s_envp)
{
	int		fdd;
	int		stdout_copy;

	stdout_copy = dup(1);
	fdd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0777);
	dup2(fdd, 1);
	close(fdd);
	exec_dir(temp, fd, 0, s_envp);
	dup2(stdout_copy, 1);
	close(stdout_copy);
}

// La redirection in < est utilisee pour indiquer a un programme que son entree standard devrait
	// provenir d'un fichier specifie plutot que du clavier, par exemple "cat < file.txt", on lira
	// les donnees depuis un fichier au lieu de l'entree du clavier
// apres avoir mis dans temp la commande en question comportant la commande (sans la redirection) donc tout ce qui y'a avant
	// d'avoir stocke le fichier auquel lire les donnees, et d'avoir ouvert ce dernier en read_only
//on check si il y a plusieurs redirections, si il y a un redir_out deux places apres par exemple
	// si c'est le cas, on apppelle mixed_redir_2() ou sinon mixed_redir1, str[i + 3] = le dernier fichier normalement
// dans le cas d'une seule redirection, on exec exec_redir tranquillement avec la commande, le fichier
	// l'entree standard (0) et le tableau d'env, car on va redirigier l'entree standard cette fois
void	redir_in_handle(char **str, int i, t_envp *s_envp)
{
	char	*file;
	int		fd;
	char	*temp;

	temp = sub_redir(str, i);
	file = ft_strdup(str[i + 1]);
	fd = open(file, O_RDONLY, 0777);
	if (str[i + 2] && str[i + 2][0] == '>')
	{
		if (str[i + 2][1] || str[i + 2][1] == '>')
			mixed_redir2(str[i + 3], temp, fd, s_envp);
		else
			mixed_redir(str[i + 3], temp, fd, s_envp);
	}
	else
		exec_dir(temp, fd, 0, s_envp);
	free(file);
	free(temp);
}

// La redirection "<<" est utilisée dans les scripts de shell pour permettre à un utilisateur 
	// d'entrer plusieurs lignes de données qui seront ensuite transmises en tant qu'entrée 
	//à un programme ou utilisées dans un script, c' est le HEREDOC
// apres avoir mis la commande dans un temp, on check si y'a des redir vers un fichier out, 
	// donc i + 2
// si c'est le cas, on recupere dans EOF le delimiteur du here doc, on appelle notre here_doc
	// avec le delimiteur et le fichier temporaire qui contiendra le texte jusqu'a l'indicateur
	// de fin EOF
// si y'a pas de redirection de fichiers , on fait la meme, sauf qu;on appelle direct exec_dir
// on unlink bien le fichier temporaire  a la fin de l'exec, on en a plus besoin
void	redir2_in_handle(char **str, int i, t_envp *s_envp)
{
	int		fd;
	char	*eof;
	char	*temp;

	temp = sub_redir(str, i);
	if (str[i + 2] && str[i + 2][0] == '>')
	{
		eof = ft_strdup(str[i + 1]);
		here_doc("temp.txt", eof);
		fd = open("temp.txt", O_RDONLY, 0777);
		mixed_redir(str[i + 3], temp, fd, s_envp);
		unlink("temp.txt");
	}	
	else
	{
		eof = ft_strdup(str[i + 1]);
		here_doc("temp2.txt", eof);
		fd = open("temp2.txt", O_RDONLY, 0777);
		exec_dir(temp, fd, 0, s_envp);
		unlink("temp2.txt");
	}
	if (eof[0] != '\0')
		free(eof);
	if (temp[0] != '\0')
		free(temp);
}

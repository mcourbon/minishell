/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:32:47 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/04 00:35:17 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_error; // la variable globalde g_error est la variable indispensable d'un projet comme
				//qui est un code erreur qu'on mettra a jour au fil du projet, qui sera le
				//code de sortie des commandes executees et ainsi indiquer l'etat de sortie
				//d'un programme. ce code de sortie sera envoyee generalement du processus enfant
				//(qui execute les commandes) au processus parent (le shell principal) pour 
				//justement traiter ce code de sortie et agir en consequence.
				// on va s'en servir par exemple pour echo "$?" qui va afficher le code de retour
				// ou encore 
				
// fonction qui permet de parcourir le tableau d'environnement, et retourner 1 si la
	//variable PATH existe
int	path_exists(t_envp *s_envp)
{
	int	i;

	i = 0;
	while (s_envp->env_array[i])
	{
		if (ft_strncmp(s_envp->env_array[i], "PATH=", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}

// - fonction pour lire l'entree utilisateur avec readline et stock l'input dans buffer
	// - si readline a retourne NULL, c'est qu'il atteint l'EOF et du coup cela indique la 
		//fin de l'entree, on gere ainsi Ctrl + D car ce dernier retourne aussi EOF quand il
		//est appele puis on exit avec le code de sortie 130, qui est un code lorsque le 
		//programme a ete interrompu 
	//- elle check si la variable d'env PATH existe, si c'est le cas, elle copie la commande 
		//entree par l'user dans str, on ajoute l'entree dans l'historique avec add_history, et
		//on libere le buffer occupee par le tampon de lecture readline, on retourne str
	//- si pour quelconque raison y'a pas PATH, on affiche Command not found dans l'entree
		//standard, free le tampon de lecture, on retroune la chaine str vide, et on met le
		//code error a 127, qui est le code pour signaler qu'une commande n'a pas ete trouvee
//*/
char	*take_input(t_envp *s_envp)
{
	char	*str;
	char	*buffer;

	str = "";
	buffer = readline(">>>minishell ");
	if (buffer == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		exit(130);
	}
	else if (path_exists(s_envp))
	{
		str = ft_strdup(buffer);
		add_history(buffer);
		free(buffer);
		return (str);
	}
	ft_putendl_fd("Command not found", 1);
	if (buffer[0] != '\0')
		free(buffer);
	g_error = 127;
	return (str);
}


// - on init l'environnement
// - on entre dans la boucle infini ou on lit l'input utilisateur
// - on verifie si la commande n'est pas vide avant de lancer parsing_command
// - on free str (strdup) et le tableau d'env qui est dans un split
// - biensur, on implemente le ft_signals pour pouvoir arreter la boucle a tout moment
int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_envp	*s_envp;

	(void)argc;
	(void)argv;
	s_envp = init(envp);
	while (1)
	{
		ft_signals(1);
		str = take_input(s_envp);
		if (ft_strlen(str) != 0)
			parsing_command(str, s_envp);
		free(str);
	}
	ft_free_env(s_envp);
	return (0);
}

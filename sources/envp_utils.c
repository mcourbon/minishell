/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:04:55 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/21 23:19:53 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// calculer la longueur du tableau de variables d'env

int	env_len(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

// la fonction qui va comparer la variable saisie avec la variable d'env dans le tableau 
	// caracteres par caracteres
int	ft_var_is_in_env(char *env_var, char *my_var)
{
	int	i;

	i = 0;
	if (my_var == NULL)
	{
		ft_putendl_fd("Error Occured !", 1);
		g_error = 127;
	}
	while (my_var[i])
	{
		if (my_var[i] && env_var[i] != my_var[i]) // ma variable n' est pas dans l'index de env en question
			return (0);
		i++;
	}
	return (1); // la variable est dans l'index d'env en question
}

// get_index va parcourir le tableau de variables d'emv, et essayer de verifier (avec la
	// fonction ft_var_is_env)), si la variable actuel correspond a une variable du tableau
// si c'est le cas, on renvoie l'id dans laquelle on a trouve, dans le cas d'export, ca veut
	// dire qu'on va modifier une variable existante, et dans le cas d'unset c'est qu'on va
	// supprimer une variable existante
// si on a pas trouve, on renvoie le dernier element du tableau, c'est la ou on ecrira la 
	// nouvelle variable avec export, ou dans le cas d'unset ou on supprimera rien
int	get_index(char *var_name, t_envp *s_envp)
{
	int		i;

	i = 0;
	while (s_envp->env_array[i])
	{
		if (ft_var_is_in_env(s_envp->env_array[i], var_name))
			return (i);
		i++;
	}
	return (i);
}

// fonction qui va reallouer notre tableau d'env avec la nouvelle taille
void	realloc_env_array(t_envp *s_envp)
{
	char	**new_env_array;
	int		i;

	new_env_array = malloc(sizeof(char *) * (s_envp->env_len + 1));
	if (new_env_array == NULL)
	{
		ft_putendl_fd("malloc() failed", 1);
		g_error = 127;
	}
	i = 0;
	while (s_envp->env_array[i])
	{
		new_env_array[i] = ft_strdup(s_envp->env_array[i]);
		free(s_envp->env_array[i]);
		i++;
	}
	new_env_array[i + 1] = NULL;
	free(s_envp->env_array);
	s_envp->env_array = new_env_array;
}

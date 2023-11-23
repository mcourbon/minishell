/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:07:06 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/21 22:58:26 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// ainsi, cette fonction va ainsi supprimer (free + NULL) la variable a remplacer, dans l'index
	// en question
// si la variable a une valeur, alors on a un premier temp qui va etre egal a "=valeur", qu'on
	// va join avec la nom de la variable dans temp2, qu'on place dans le tableau
// si le nom de la variable n'a pas de valeur, alors on met juste un espace "nom=", ce qui
	// est possible si on veut que notre variable soit vide
void	export_exec_exist(char *var_name, char *var_val, t_envp *s_envp, int i)
{
	char	*temp;
	char	*temp2;

	if (s_envp->env_array[i][0] != '\0')
		free(s_envp->env_array[i]);
	s_envp->env_array[i] = NULL;
	if (var_val)
	{
		temp = ft_strjoin("=", var_val);
		temp2 = ft_strjoin(var_name, temp);
		s_envp->env_array[i] = temp2;
		free(temp);
		free(temp2);
	}
	else
	{
		temp2 = ft_strjoin(var_name, " ");
		s_envp->env_array[i] = temp2;
		free(temp2);
	}
}

// dans cette fonction, apres avoir augmenter de 1 la taille du tableau pour accueillir la nouvelle
	// variable, puis avoir realloc le tableau avec la nouvelle valeur
// on verifie si la valeur n'est pas null, si c'est le cas, on check si y'a un dollar devant
	// la valeur (si c'est une variable existante a substituer a notre variable), et pareil si
	// c'est le cas, on enleve le dollar de la valeur en question, pour pouvoir ensuite extraire
	// la valeur de la variable d'env avec getenv, que l'on place dans dollar, puis on va
	// copier cette nouvelle valeur dans var_val, cette derniere aura la valeur qu'on a extrait
	// de la variable d'env
// sinon, tranquillement on ajoute = a la valeur avec join, qu'on rejoin dans le tableau avec le
	// nom de la variable
// comme d'hab, si la valeur de la variable est NULL, on join juste le nom de la variable avec rien
	// a l'interieur (espace quoi)
void	export_exec_non_existent(char *var_name, char *var_val,
	t_envp *s_envp, int i)
{
	char	*dollar;
	char	*temp;
	char	*temp2;

	//printf("len %d\n", s_envp->env_len);
	s_envp->env_len++;
	realloc_env_array(s_envp);
	if (var_val)
	{
		if (count(var_val, '$'))
		{
			temp2 = ft_strtrim(var_val, "$");
			dollar = ft_strdup(getenv(temp2));
			free(temp2);
			ft_strcpy(var_val, dollar);
			free(dollar);
		}
		temp = ft_strjoin("=", var_val);
		s_envp->env_array[i] = ft_strjoin(var_name, temp);
		free(temp);
	}
	else if (var_val == NULL)
		s_envp->env_array[i] = ft_strjoin(var_name, " ");
}

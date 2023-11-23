/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 01:20:01 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/21 18:25:50 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// vu qu'on va supprimer une variable d'env, on reduit la taille d'1 du tableau
// on free et on met egal a NULL la variable en question, puis on parcourt le tableau pour
	// faire en sorte de remplacer la valeur supprime (egal a NULL) par l'element suivant du
	// tableau, on decale les elements l'un a l'autre jusqu'au dernier element du tableau
// puis on realloc le tableau avec la nouvelle taille du tableau
static void	ft_unset(int var_pos, t_envp *s_envp) 
{
	int	i;

	s_envp->env_len--;
	if (s_envp->env_array[var_pos][0] != '\0')
		free(s_envp->env_array[var_pos]);
	s_envp->env_array[var_pos] = NULL;
	i = var_pos;
	while (s_envp->env_array[i + 1])
	{
		s_envp->env_array[i] = s_envp->env_array[i + 1];
		s_envp->env_array[i + 1] = NULL;
		i++;
	}
	realloc_env_array(s_envp);
}

// la fonction qui va lancer unset, qui permet de supprimer une variable d'env
// apres avoir extrait uniquement la variable d'env selectionne dans la commande, qu'on stocke
	// dans un tableau (split)
// on lance ensuite ft_unset qui va gerer l'exec, en lui envoyant l'index de la variable a
 // supprimer, avec le tableau en question
void	run_unset(char *str, t_envp *s_envp)
{
	int		i;
	int		j;
	int		len;
	char	**array;
	char	*sub;

	len = ft_strlen(str);
	sub = ft_substr(str, 6, len - 6);
	//if (sub[0] == '\0')
	//{
	//	ft_putendl_fd("unset : not enough arguments", 2);
	//	g_error = 1;
	//}
	array = ft_split(sub, ' ');
	i = -1;
	while (array[++i])
	{
		j = get_index(array[i], s_envp);
		if (s_envp->env_array[j])
			ft_unset(j, s_envp);
	}
	if (sub[0] != '\0')
		free(sub);
	if (array[0][0] != '\0')
		ft_free_str(array);
}

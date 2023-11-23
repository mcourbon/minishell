/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:09:09 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/21 23:40:10 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// ft_export va s'occuper de d'abord choper l'index du tableau d'env, si c'est un index different de NULL
	// c'est que la var d'env existe deja, on appelera donc export_exec_exist pour modifier une 
	// variable existante
// si get_index renvoie NULL, c'est qu'on est arrive a la fin du tableau, alors on va la creer
void	ft_export(char *var_name, char *var_val, t_envp *s_envp)
{
	int	i;

	i = get_index(var_name, s_envp);
	if (s_envp->env_array[i])
		export_exec_exist(var_name, var_val, s_envp, i);
	else if (s_envp->env_array[i] == NULL)
		export_exec_non_existent(var_name, var_val, s_envp, i);
}

// cette fonction a comme objectif de creer deux variables temporaires, qui va stocker, pour
	// chaque valeur du tableau, le nom de la variable d'env a exporter d'un cote, et la valeur
	// de la variable de l'autre cote
// puis on envoie le tout a ft_export
void	export_with_equal(char **str, t_envp *s_envp, int i)
{
	char	*temp;
	char	*temp2;
	int		j;
	int		k;

	j = 0;
	k = 0;
	temp = malloc(sizeof(char) * (ft_strlen_equal(str[i]) + 1));
	//if (temp == NULL)
		// caca;
	temp2 = malloc(sizeof(char) * 
		((ft_strlen(str[i]) - ft_strlen_equal(str[i])) + 1));
	//if (temp2 == NULL)
		// caca;
	while (str[i][j] != '=')
		temp[k++] = str[i][j++];
	temp[k] = '\0';
	k = 0;
	if (str[i][j] == '=')
	{
		while (str[i][j] != '\0')
			temp2[k++] = str[i][++j];
		temp2[k] = '\0';
	}
	ft_export(temp, temp2, s_envp);
	free(temp);
	free(temp2);
}

// la fonction va s'occuper de mettre toutes les variables exportees dans un tableau
// on free sub2 (strtrim) on a plus besoin
// on parcourt nos variables d'env a exporter dans le tableau, on compte le nombre d'egal pour
	// chaque valeur, appeler export_with_equal() si y'a on export une variable avec
void	run_export2(char *sub2, t_envp *s_envp)
{
	int		i;
	int		equal;
	char	**str;

	str = ft_split(sub2, ' ');
	i = -1;
	free(sub2);
	while (str[++i])
	{
		equal = count(str[i], '=');
		if (equal > 0)
			export_with_equal(str, s_envp, i);
		else if (equal == 0)
			ft_export(str[i], NULL, s_envp);
	}
}

// la fonction va extraire la variable a exporter et le mettre dans sub, puis enlever les espaces
	// au debut et a la fin
// si export n'a pas d'argument, on appelle print_export(), car export va en fait afficher env
	// mais avec "declare -x" au debut, et par ordre alphabetique
// sinon, on appelle run_export2 avec le tableau et la valeur a exporter
void	run_export(char *str, t_envp *s_envp)
{
	char	*sub;
	char	*sub2;
	int		len;

	len = ft_strlen(str);
	sub = ft_substr(str, 7, len - 7);
	sub2 = ft_strtrim(sub, " ");
	if (sub2[0] == '\0')
	{
		print_export(s_envp);
		free(sub2);
	}
	else
		run_export2(sub2, s_envp);
	free(sub);
}

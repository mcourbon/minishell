/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:06:04 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/03 23:06:37 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// trier par ordre alphabetique notre tableau de variables d'env

char	**sort_envp(char **envp)
{
	int			i;
	char		*temp;

	i = 0;
	while (envp[i] && envp[i + 1])
	{
		if (ft_strcmp(envp[i], envp[i + 1]) > 0)
		{
			temp = envp[i];
			envp[i] = envp[i + 1];
			envp[i + 1] = temp;
			i = -1;
		}
		i++;
	}
	return (envp);
}

// afficher ce tableau triee, mais avec "declare -x" a la fin
void	print_export(t_envp *s_envp)
{
	int		i;
	char	**env_sort;
	char	*temp;

	i = 0;
	env_sort = sort_envp(s_envp->env_array);
	while (env_sort[i])
	{
		temp = ft_strjoin("declare -x ", env_sort[i]);
		ft_putendl_fd(temp, 1);
		free(temp);
		i++;
	}
}

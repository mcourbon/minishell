/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:12:28 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/03 23:14:15 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// free les tableaux de char, particulierement les split
void	ft_free_str(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

// free des listes
void	ft_lstdelete(t_list *lst)
{
	free(lst->content);
	free(lst);
	lst = NULL;
}

void	ft_free_list(t_list **list)
{
	t_list	*tmp;

	if (list)
	{
		while (*list)
		{
			tmp = (*list)->next;
			ft_lstdelete(*list);
			*list = tmp;
		}
		free(list);
	}
}

// free le tableau d'env
void	ft_free_env(t_envp *s_envp)
{
	int	i;

	i = 0;
	while (s_envp->env_array[i])
	{
		free(s_envp->env_array[i]);
		i++;
	}
	free(s_envp);
	s_envp = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:14:25 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/21 23:10:19 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// - fonction qui remplit notre tableau avec les variables d'environnement, grace a envp qui
	// permet justement d'y avoir acces 

t_envp	*init_envp(char **envp)
{
	int		i;
	t_envp	*s_env;

	i = 0;
	s_env = malloc(sizeof(t_envp));
	if (!s_env)
		return (NULL);
	s_env->env_len = env_len(envp);
	s_env->env_array = malloc(sizeof(char *) * (s_env->env_len + 1));
	if (!s_env->env_array)
	{
		ft_putstr_fd("Error : malloc() failed.\n", 1);
		g_error = 127;
	}
	while (envp[i])
	{
		s_env->env_array[i] = ft_strdup(envp[i]);
		i++;
	}
	s_env->env_array[i] = NULL;
	return (s_env);
}

t_envp	*init(char **envp)
{
	t_envp	*s_envp;

	g_error = 0;
	s_envp = init_envp(envp);
	return (s_envp);
}

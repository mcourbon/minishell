/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:02:52 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/22 00:44:05 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// enfin, cette fonction parcourera le tableau d'env a partir de l'index ou on a trouve la variable d'env
	// et afficher tout ce qu'il y a apres le = (donc la valeur)
static void	print_echo_envp(t_envp *s_envp, int i, int j)
{
	while (s_envp->env_array[i][++j])
	{
		if (s_envp->env_array[i][j] == '=')
		{
			while (s_envp->env_array[i][++j])
				ft_putchar_fd(s_envp->env_array[i][j], 1);
		}
	}
}

// on divise la chaine en morceaux distincts en utilisant $ comme delimiteur
// on parcourt le tableau de variables d'env
// pour chaque nom de variable d'env, on lui rajoute un = avec \0
// ensuite pour chaque variable elle est dans le tableau d'env 
// si c'est le cas, on envoie a print_echo_envp l'index ou on a trouve i avec le tableau d'env
static void	multiple_dollar(char *str, t_envp *s_envp)
{
	char	**dollars;
	int		i;
	char	*temp;
	int		j;
	int		k;

	k = -1;
	dollars = ft_split(str, '$');
	while (dollars[++k])
	{
		i = -1;
		j = -1;
		while (s_envp->env_array[++i])
		{
			temp = ft_strjoin(dollars[k], "=\0");
			if (ft_var_is_in_env(s_envp->env_array[i], temp))
				print_echo_envp(s_envp, i, j);
			free(temp);
		}
	}
	ft_free_str(dollars);
}

// cette fonction va compter le nombre de $, au cas ou il y a aurait plusiseurs variables d'env a
	// afficher
// puis on parcourt le tableau d'env
// si y'avait qu'un dollar (une variable a afficher), on met un egal a la fin de chaque nom
	// de variable, le temp va juste servir a comparer notre variable avec celle du tableau d'env
	// puis ensuite ben pareil on check si la variable est dans le tableau d'ennv, si c'est le
	// cas ou on affiche avec print_echo_envp
// si y'en a plusieurs, c' est multiple_dollar() qui gere tout
static void	get_my_env(char *var_name, t_envp *s_envp)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	if (count(var_name, '$'))
		multiple_dollar(var_name, s_envp);
	while (s_envp->env_array[i])
	{
		temp = ft_strjoin(var_name, "=\0");
		if (ft_var_is_in_env(s_envp->env_array[i], temp))
			print_echo_envp(s_envp, i, j);
		free(temp);
		i++;
	}
}

// dans le cas ou on veut echo une variable d'env avec $
// cette fonction va d'abord mettre dans une temp le nom de la variable, genre "PATH"
// on envoie en suite la variable a get_my_envv
int	echo_dollar_env(char *str, int *i, t_envp *s_envp)
{
	char	*temp;
	int		j;

	temp = malloc(sizeof(char) * ft_strlen(str));
	if (temp == NULL)
		return (-1);
	j = 0;
	(*i)++;
	while (*(str + *i) != ' ' && *(str + *i))
	{
		temp[j] = *(str + *i);
		(*i)++;
		j++;
	}
	temp[j] = '\0';
	get_my_env(temp, s_envp);
	free(temp);
	return (0);
}

// on affiche, dans le cas ou y'aurait un double quote, tout ce qui est entre les quotes
void	print_echo_double_quote(char *str, int *i)
{
	(*i)++;
	while (*(str + *i) != '\"' && *(str + *i))
	{
		ft_putchar_fd(*(str + *i), 1);
		(*i)++;
	}
}

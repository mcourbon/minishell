/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:57:27 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/03 22:57:41 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// pareil mais pour double
static int	check_double_quote(char *str, int *i)
{
	(*i)++;
	while (*(str + *i) != '\"' && *(str + *i))
		(*i)++;
	if (*(str + *i) != '\"')
		return (-1);
	return (1);
}

// check single, on se casse pas la tete on gere le i en mode pointeur
static int	check_single_quote(char *str, int *i)
{
	(*i)++;
	while (*(str + *i) != '\'' && *(str + *i))
		(*i)++;
	if (*(str + *i) != '\'')
		return (-1);
	return (1);
}

// fonction global qui va checker si la string comporte des " ou des ','
// mais particulierement checker si il y en a 2 de chaque, c'est a dire si la str est bien entoure
	// de single ou double quotes
// si c'est le cas, utils_quote_flag sera egal a 1 et on le retourne, si c'est -1, on le retourne
	// aussi a echo_management, qui va traiter l'erreur
int	check_quotes(char *str, t_utils utils)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			utils.quote_flag = check_double_quote(str, &i);
		else if (str[i] == '\'')
			utils.quote_flag = check_single_quote(str, &i);
		if (utils.quote_flag == -1)
			break ;
		i++;
	}
	return (utils.quote_flag);
}

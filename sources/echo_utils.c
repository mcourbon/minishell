/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:58:01 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/03 23:02:41 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// on affiche, dans le cas ou y'aurait un single quote, tout ce qui est entre les quotes
void	print_echo_single_quote(char *str, int *i)
{
	(*i)++;
	while (*(str + *i) != '\'' && *(str + *i))
	{
		ft_putchar_fd(*(str + *i), 1);
		(*i)++;
	}
}

// pareil sauf qu'on affiche pas le saut de ligne a la fin (car flag -n)
// plus opti de renvoyer un pointeur sur i, pour que i reste "global" et qu'on puisse continuer
	// a taffer avec, au lieu de faire une static
void	exec_echo_with_n(char *str, t_envp *s_envp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			print_echo_double_quote(str, &i);
		else if (str[i] == '\'')
			print_echo_single_quote(str, &i);
		else if (str[i] == '$' && str[i + 1] == '?' && ++i)
			ft_putnbr_fd(g_error, 1);
		else if (str[i] == '$')
			echo_dollar_env(str, &i, s_envp);
		else
			ft_putchar_fd(str[i], 1);
		i++;
	}
}

// fonction qui va analyser la commande (sans le flag -n) et va executer la fonction adequate
	// en consequence
// $? = afficher le code de retour
// on ajoute a la fin le saut de ligne
void	exec_echo_without_n(char *str, t_envp *s_envp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			print_echo_double_quote(str, &i);
		else if (str[i] == '\'')
			print_echo_single_quote(str, &i);
		else if (str[i] == '$' && str[i + 1] == '?' && ++i)
			ft_putnbr_fd(g_error, 1);
		else if (str[i] == '$')
			echo_dollar_env(str, &i, s_envp);
		else
			ft_putchar_fd(str[i], 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}

// la fonction qui check si la commande echo contient litteralement " -n "
int	check_flag_n(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '-')
		i++;
	if (str[i - 1] == ' ' && (str[i] == '-' && str[i + 1] == 'n')
		&& str[i + 2] == ' ')
		return (1);
	return (-1);
}

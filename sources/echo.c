/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:04:02 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/03 23:04:15 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// la fonction qui va lancer les exec pour echo, avec ou sans -n 
// on met de base utils.quote_flag a 1, donc si y'a des quotes ou non, ce sera toujours vrai
// puis on lance echo with n ou echo without n selon le flag -n mis a jour dans check flag

void	echo_management(char *str, t_utils utils, t_envp *s_envp)
{
	utils.quote_flag = 1;
	if (check_quotes(str, utils) == -1)
	{
		g_error = 127;
		ft_putendl_fd("Syntax Error Occured !", 1);
	}
	else
	{
		if (utils.n_flag == 1)
			exec_echo_with_n(str, s_envp);
		else if (utils.n_flag == -1)
			exec_echo_without_n(str, s_envp);
	}
}

// pareil que find_start(), mais avec l'option -n
static char	*find_start_n(char *str, int last, int start)
{
	int		i;
	char	*temp;

	i = 0;
	while (str[i])
	{
		if (str[i - 1] == ' ' && (str[i] == '-' && str[i + 1] == 'n')
			&& str[i + 2] == ' ')
		{
			i = i + 2;
			while (str[i] < 33)
				i++;
			start = i;
			break ;
		}
		i++;
	}
	temp = ft_substr(str, start, last + 1);
	if (temp[0] != '\0')
		return (temp);
	return (NULL);
}

// cette fonction sert a extraire la valeur d'echo a afficher, en essayant de trouver par ou
	// elle commence, pour pouvoir envoyer le tout a substr qui va mettre tout ca dans
	// une nouvelle string
static char	*find_start(char *str, int last, int start)
{
	int		i;
	char	*temp;

	i = 0;
	while (str[i])
	{
		if (str[i + 1] > 32)
			;
		else
		{
			i++;
			while (str[i] < 33)
				i++;
			start = i;
			break ;
		}
		i++;
	}
	temp = ft_substr(str, start, last + 1);
	return (temp);
}

// cette fonction va essayer de trouver le dernier caractere de la commande qui a ete envoyee
	// pour pouvoir l'envoyer a find_start_n ou find_start (en fonction de la presence de -n)
// l'objectif final etant d'extraire la valeur a afficher d'echo
static char	*get_echo_str(char *str, t_utils utils)
{
	int		last;
	int		start;
	int		len;
	char	*temp;

	last = 0;
	start = 0;
	len = ft_strlen(str) - 1;
	while (len)
	{
		if (str[len] > 32 && str[len] < 127)
		{
			last = len;
			str[last + 1] = '\0';
			break ;
		}
		len--;
	}
	if (utils.n_flag == 1)
		temp = find_start_n(str, last, start);
	else
		temp = find_start(str, last, start);
	return (temp);
}

// la fonction globale qui va appeler les fonctions pour gerer le builtin echo
// on recoit la commande, on enleve les espaces au debut + a la fin
// on met dans utils.n_flag ce que renvoie check_flag_n, renvoie 1 si y'a un -n, sinon -1
// on met ensuite dans temp ce que renvoie get_echo_str, la valeur a afficher
void	run_echo(char *str, t_envp *s_envp)
{
	t_utils	utils;
	char	*temp;
	char	*temp2;

	temp2 = ft_strtrim(str, " ");
	utils.n_flag = check_flag_n(str);
	temp = get_echo_str(temp2, utils);
	echo_management(temp, utils, s_envp);
	if (temp[0] != '\0')
		free(temp);
	if (temp2[0] != '\0')
		free(temp2);
}

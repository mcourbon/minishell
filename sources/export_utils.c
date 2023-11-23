#include "../headers/minishell.h"

// calcule la len jusqu'à = pour stocker juste le nom de la variable d'env à export

int	ft_strlen_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}
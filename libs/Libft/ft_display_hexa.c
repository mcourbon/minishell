/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_hexa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:47:30 by momaiouf          #+#    #+#             */
/*   Updated: 2023/01/20 16:47:30 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_len_hexa(unsigned int nb)
{
	unsigned int	count;

	count = 0;
	if (nb == 0)
		count++;
	while (nb != 0)
	{
		nb = nb / 16;
		count++;
	}
	return (count);
}

unsigned int	ft_display_hexa(long nb, char caps)
{
	long				temp;
	char				*hexa_lower;
	char				*hexa_upper;

	temp = nb;
	hexa_lower = "0123456789abcdef";
	hexa_upper = "0123456789ABCDEF";
	if (nb == 16)
	{
		ft_putstr_int("10");
		return (ft_len_hexa(temp));
	}
	if (nb > 16)
		ft_display_hexa(nb / 16, caps);
	if (caps == 'X')
		ft_putchar_int(hexa_upper[nb % 16]);
	else if (caps == 'x')
		ft_putchar_int(hexa_lower[nb % 16]);
	return (ft_len_hexa(temp));
}

unsigned long long	ft_len_hexa_pointer(unsigned long long nb)
{
	unsigned long long	count;

	count = 0;
	if (nb == 0)
		count++;
	while (nb != 0)
	{
		nb = nb / 16;
		count++;
	}
	return (count);
}

unsigned long long	ft_display_hexa_pointer(unsigned long long nb)
{
	unsigned long long	temp;
	char				*hexa_array;

	temp = nb;
	hexa_array = "0123456789abcdef";
	if (nb == 16)
	{
		ft_putstr_int("10");
		return (ft_len_hexa_pointer(temp) + 2);
	}
	if (nb > 16)
		ft_display_hexa_pointer(temp / 16);
	ft_putchar_int(hexa_array[temp % 16]);
	return (ft_len_hexa_pointer(temp) + 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_number.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:47:38 by momaiouf          #+#    #+#             */
/*   Updated: 2023/01/20 16:47:38 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len_int(int nb)
{
	int		count;

	count = 0;
	if (nb == 0)
		count++;
	if (nb < 0)
	{
		nb = -nb;
		count++;
	}
	while (nb != 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

int	ft_putnbr_int(int nb)
{
	int	temp;

	if (nb == -2147483648)
		return (ft_putstr_int("-2147483648"));
	if (nb < 0)
	{
		ft_putchar_int('-');
		temp = -nb;
	}
	else
		temp = nb;
	if (temp > 9)
		ft_putnbr_int(temp / 10);
	ft_putchar_int('0' + (temp % 10));
	return (ft_len_int(nb));
}

int	ft_len_u_int(unsigned int nb)
{
	int		count;

	count = 0;
	if (nb == 0)
		count++;
	while (nb != 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

int	ft_putnbr_u_int(unsigned int nb)
{
	unsigned int	temp;

	temp = nb;
	if (temp > 9)
		ft_putnbr_u_int(temp / 10);
	ft_putchar_int('0' + (temp % 10));
	return (ft_len_u_int(nb));
}

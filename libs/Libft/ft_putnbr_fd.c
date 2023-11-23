/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:47:22 by momaiouf          #+#    #+#             */
/*   Updated: 2022/11/18 20:23:30 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int		temp;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		temp = -n;
	}
	else
		temp = n;
	if (temp > 9)
		ft_putnbr_fd(temp / 10, fd);
	ft_putchar_fd('0' + (temp % 10), fd);
}

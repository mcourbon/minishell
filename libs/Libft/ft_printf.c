/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:52:54 by momaiouf          #+#    #+#             */
/*   Updated: 2023/01/20 16:52:54 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_arg_len(const char *str, int i, va_list ap)
{
	if (str[i] == 'c')
		return (ft_putchar_int(va_arg(ap, int)));
	else if (str[i] == 's')
		return (ft_putstr_int(va_arg(ap, char *)));
	else if (str[i] == 'p')
	{
		write(1, "0x", 2);
		return (ft_display_hexa_pointer(va_arg(ap, unsigned long long)));
	}
	else if (str[i] == 'd' || str[i] == 'i')
		return (ft_putnbr_int(va_arg(ap, int)));
	else if (str[i] == 'u')
		return (ft_putnbr_u_int(va_arg(ap, unsigned int)));
	else if (str[i] == 'x' || str[i] == 'X')
		return (ft_display_hexa(va_arg(ap, unsigned int), str[i]));
	else if (str[i] == '%')
		return (ft_putchar_int('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	ap;

	i = 0;
	len = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len = len + get_arg_len(str, ++i, ap);
		}
		else
		{
			write(1, &str[i], 1);
			len++;
		}
		i++;
	}
	va_end(ap);
	return (len);
}

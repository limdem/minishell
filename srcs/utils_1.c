/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:28:38 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/08 15:28:44 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putstr_fd(char const *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

signed long long int	ft_minus(signed long long int number, int minus)
{
	if (minus % 2 != 0)
	{
		return (-number);
	}
	else
		return (number);
}

signed long long int	ft_atoi(const char *str)
{
	long long int			i;
	int						minus;
	unsigned long long int	number;

	i = 0;
	minus = 0;
	number = 0;
	while ((str[i] == 32 || (str[i] > 8 && str[i] < 14)) && str[i])
		i++;
	if ((str[i] == 45 || str[i] == 43) && str[i])
	{
		if (str[i] == 45)
			minus++;
		i++;
	}
	while ((str[i] > 47 && str[i] < 58) && str[i] != '\0')
	{
		number = (number * 10 + (str[i] - 48));
		if (number > 9223372036854775807)
			return (1786594284136218);
		i++;
	}
	return (ft_minus(number, minus));
}

int	arg_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] != 45 && (str[i] < 48 || str[i] > 57))
			return (0);
		i++;
	}
	return (1);
}

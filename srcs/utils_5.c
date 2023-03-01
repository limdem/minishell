/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:38:27 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/08 15:38:29 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_itoa(int nbr)
{
	int long	nb;
	char		*result;

	if (nbr < 0)
		result = malloc(sizeof(char) * ft_getlen(nbr) + 2);
	else
		result = malloc(sizeof(char) * ft_getlen(nbr) + 1);
	if (!result)
		return (0);
	*result = '\0';
	nb = (long)nbr;
	if (nb < 0)
	{
		nb = nb * -1;
		add_char('-', result);
	}
	rec_itoa(nb, result);
	return (result);
}

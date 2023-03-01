/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:33:53 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/08 13:33:56 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	unsigned int		lenstr;
	char				*t;
	int					i;

	i = 0;
	if (!s)
		return (0);
	lenstr = ft_strlen(s);
	if (start >= lenstr)
	{
		t = malloc(sizeof(char) * 1);
		t[0] = '\0';
		return (t);
	}
	if (len > (ft_strlen(s) - start))
		t = malloc(sizeof(char) * ((ft_strlen(s) - start)) + 1);
	else
		t = malloc(sizeof(char) * (len) + 1);
	if (!(t))
		return (0);
	while (len-- && s[start])
		t[i++] = s[start++];
	t[i] = '\0';
	return (t);
}

char	*ft_strdup(const char *s)
{
	char	*new_s;
	int		i;

	new_s = malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!new_s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

void	add_char(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	str[i] = c;
	str[i + 1] = '\0';
}

void	rec_itoa(long nb, char *result)
{
	if (nb >= 10)
	{
		rec_itoa(nb / 10, result);
	}
	add_char((nb % 10 + 48), result);
}

int	ft_getlen(int nbr)
{
	int	nbrmalloc;

	nbrmalloc = 1;
	while (nbr >= 10 || nbr <= -10)
	{
		nbr = nbr / 10;
		nbrmalloc++;
	}
	return (nbrmalloc);
}

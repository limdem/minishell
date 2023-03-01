/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:47:35 by dgauvin           #+#    #+#             */
/*   Updated: 2022/06/09 23:49:14 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize_tmp_array(t_tmp *tmp, char **tmp_arr, int args_nbr)
{
	tmp->no_match = 1;
	tmp->folder = opendir(".");
	tmp->read = 1;
	tmp_arr[args_nbr] = NULL;
}

int	determine_distance(char char1, char char2)
{
	int	dist1;
	int	dist2;
	int	res;

	res = 1;
	if (char1 >= 'A' && char1 <= 'Z')
		dist1 = char1 - 65;
	if (char1 >= 'a' && char1 <= 'z')
		dist1 = char1 - 97;
	if (char2 >= 'A' && char2 <= 'Z')
		dist2 = char2 - 65;
	if (char2 >= 'a' && char2 <= 'z')
		dist2 = char2 - 97;
	if (dist1 < dist2)
		return (-res);
	if (dist1 > dist2)
		return (res);
	return (char1 - char2);
}

int	alpha_sort(char *str1, char *str2)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
		{
			if (((str1[i] >= 'A' && str1[i] <= 'Z')
					|| (str1[i] >= 'a' && str1[i] <= 'z'))
				&& ((str2[i] >= 'A' && str2[i] <= 'Z')
					|| (str2[i] >= 'a' && str2[i] <= 'z')))
				return (determine_distance(str1[i], str2[i]));
			if (str1[i] == '.' || str2[i] == '.')
				res = -1;
			return (res * (str1[i] - str2[i]));
		}
		i++;
	}
	return (0);
}

char	*custom_strjoin(char *s1, char *s2, int delete)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!str || !s1 || !s2)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	deletestr (delete, s1, s2);
	return (str);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n-- > 0)
	{
		*ptr = c;
		ptr++;
	}
	return (s);
}

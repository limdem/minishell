/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_extended.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:23:56 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/10 11:23:58 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_args(char **args, int args_nbr)
{
	while (args_nbr >= 0)
	{
		free(args[args_nbr]);
		args_nbr--;
	}
	free(args);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*pt_dest;
	const unsigned char	*pt_src;

	pt_dest = (unsigned char *)dest;
	pt_src = (const unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	while (n > 0)
	{
		pt_dest[n - 1] = pt_src[n - 1];
		n--;
	}
	return (dest);
}

int	is_a_directory(char *str)
{
	DIR	*folder;

	folder = opendir(str);
	if (folder != NULL)
	{
		closedir(folder);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_match.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:28:56 by dgauvin           #+#    #+#             */
/*   Updated: 2022/06/08 21:31:55 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_match_type_0(char **file_name, char *chunk)
{
	*file_name += ft_strlen(*file_name) - ft_strlen(chunk);
	if (!ft_strncmp(*file_name, chunk, ft_strlen(chunk)))
	{
		*file_name += ft_strlen(chunk);
		return (0);
	}
	else
		return (1);
}

int	check_match_type_1(char **file_name, char *chunk)
{
	if (!ft_strncmp(*file_name, chunk, ft_strlen(chunk)))
	{
		*file_name += ft_strlen(chunk);
		return (0);
	}
	else
		return (1);
}

int	check_match_type_2(char **file_name, char *chunk)
{
	int	i;

	i = 0;
	while ((*file_name)[i])
	{
		if (!ft_strncmp(*file_name + i, chunk, ft_strlen(chunk)))
		{
			i += ft_strlen(chunk);
			*file_name += i;
			return (0);
		}
		i++;
	}
	return (1);
}

int	match_pattern(char **file_name, char *chunk, int chunk_type)
{
	int	match;

	if (chunk_type == 0)
		match = check_match_type_0(file_name, chunk);
	if (chunk_type == 1)
		match = check_match_type_1(file_name, chunk);
	if (chunk_type == 2)
		match = check_match_type_2(file_name, chunk);
	free(chunk);
	if (match)
		return (1);
	return (0);
}

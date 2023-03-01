/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_match2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:24:11 by dgauvin           #+#    #+#             */
/*   Updated: 2022/06/08 21:27:40 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	determine_chunk(char *wildcard, int *index2)
{
	if (wildcard[*index2] == '*')
		(*index2)++;
	while (wildcard[*index2])
	{
		if (wildcard[*index2] == '*')
		{
			(*index2)++;
			break ;
		}
		(*index2)++;
	}
}

int	extract_pattern(char **chunk, int chunk_type)
{
	char	*new_chunk;
	int		size;

	size = ft_strlen(*chunk) - chunk_type;
	if (!chunk_type)
		size--;
	new_chunk = malloc(sizeof(char) * (size + 1));
	if (!new_chunk)
		return (1);
	if (*chunk[0] == '*')
		ft_memcpy(new_chunk, *chunk + 1, size);
	else
		ft_memcpy(new_chunk, *chunk, size);
	new_chunk[size] = 0;
	free(*chunk);
	*chunk = new_chunk;
	return (0);
}

void	determine_chunk_type(char *chunk, int *chunk_type)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (chunk[i])
	{
		if (chunk[i] == '*')
		count++;
		i++;
	}
	if (count == 1)
	{
		if (chunk[0] == '*')
			*chunk_type = 0;
		else
			*chunk_type = 1;
	}
	else
		*chunk_type = 2;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:34:53 by dgauvin           #+#    #+#             */
/*   Updated: 2022/06/08 20:19:15 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize_wild_handler(t_wild_handler *wild_handler)
{
	wild_handler->file_match = 1;
	wild_handler->ind1 = 0;
	wild_handler->ind2 = 0;
}

int	wildcard_match(char *file_name, char *wd)
{
	t_wild_handler	w_h;

	initialize_wild_handler(&w_h);
	if (is_a_directory(file_name) && (file_name[0] == '.'))
		return (1);
	while (wd[w_h.ind1])
	{
		determine_chunk(wd, &w_h.ind2);
		w_h.chunk = malloc(sizeof(char) * (w_h.ind2 - w_h.ind1 + 1));
		if (!w_h.chunk)
			return (2);
		ft_memcpy(w_h.chunk, wd + w_h.ind1, w_h.ind2 - w_h.ind1 + 1);
		w_h.chunk[w_h.ind2 - w_h.ind1] = 0;
		determine_chunk_type(w_h.chunk, &w_h.chunk_type);
		if (extract_pattern(&w_h.chunk, w_h.chunk_type))
			return (2);
		if (match_pattern(&file_name, w_h.chunk, w_h.chunk_type))
			return (1);
		if (!wd[w_h.ind2] || (wd[w_h.ind2] == '*' && wd[w_h.ind2 + 1] == 0))
			break ;
		w_h.ind1 = w_h.ind2 - 1;
	}
	if (w_h.file_match)
		return (0);
	return (1);
}

int	count_wild_args(char *wildcard, int *args_nbr, t_wild_args wd_args)
{
	wd_args.no_match = 1;
	wd_args.folder = opendir(".");
	if (wd_args.folder == NULL)
		return (1);
	while (1)
	{
		wd_args.entry = readdir(wd_args.folder);
		if (!wd_args.entry)
			break ;
		else
		{
			wd_args.res_match = wildcard_match(wd_args.entry->d_name, wildcard);
			if (!wd_args.res_match)
			{
				wd_args.no_match = 0;
				(*args_nbr)++;
			}
			if (wd_args.res_match == 2)
				return (1);
		}
	}
	closedir(wd_args.folder);
	if (wd_args.no_match)
		(*args_nbr)++;
	return (0);
}

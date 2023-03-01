/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:37:32 by dgauvin           #+#    #+#             */
/*   Updated: 2022/06/10 00:00:35 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_arr(char **arr, int nbr, void *pointer)
{
	if (pointer)
		return (0);
	while (nbr >= 0)
	{
		free(arr[nbr]);
		nbr--;
	}
	free(arr);
	return (1);
}

int	fill_tmp_array(t_tmp	tmp, char **tmp_arr, char *wildcard, int args_nbr)
{
	initialize_tmp_array(&tmp, tmp_arr, args_nbr);
	while (tmp.read)
	{
		tmp.entry = readdir(tmp.folder);
		if (!tmp.entry)
			tmp.read = 0;
		else
		{	
			if (!wildcard_match(tmp.entry->d_name, wildcard))
			{
				tmp.no_match = 0;
				tmp_arr[args_nbr - 1] = ft_strdup(tmp.entry->d_name);
				if (free_arr(tmp_arr, args_nbr - 1, tmp_arr[args_nbr - 1]))
					return (1);
				args_nbr--;
			}
		}
	}
	closedir(tmp.folder);
	if (tmp.no_match)
		tmp_arr[0] = ft_strdup(wildcard);
	if (free_arr(tmp_arr, args_nbr - 1, tmp_arr[0]))
		return (1);
	return (0);
}

void	sort_array(char **tmp_arr, int args_nbr)
{
	int		i;
	int		j;
	char	*tmp_swap;

	i = 0;
	while (i < args_nbr - 1)
	{
		j = i + 1;
		while (j < args_nbr)
		{
			if (alpha_sort(tmp_arr[i], tmp_arr[j]) > 0)
			{
				tmp_swap = tmp_arr[i];
				tmp_arr[i] = tmp_arr[j];
				tmp_arr[j] = tmp_swap;
			}
		j++;
		}
		i++;
	}
}

int	prepare_wild_args_arr(char **args, char **tmp_arr, int args_nbr, int index)
{
	int	i;

	i = 0;
	while (i < args_nbr)
	{
		args[index] = ft_strdup(tmp_arr[i]);
		if (free_arr(tmp_arr, args_nbr, args[index]))
			return (1);
		index++;
		i++;
	}
	return (0);
}

int	handle_wild_args(char *wildcard, char **args, int *index)
{
	t_wild_args	wd_args;
	t_tmp		tmp;
	char		**tmp_arr;
	int			args_nbr;

	args_nbr = 0;
	count_wild_args(wildcard, &args_nbr, wd_args);
	tmp_arr = malloc((args_nbr + 1) * sizeof(char *));
	if (!tmp_arr)
		return (1);
	if (fill_tmp_array(tmp, tmp_arr, wildcard, args_nbr))
		return (1);
	sort_array(tmp_arr, args_nbr);
	if (prepare_wild_args_arr(args, tmp_arr, args_nbr, *index))
		return (1);
	*index += args_nbr;
	free_args(tmp_arr, args_nbr);
	return (0);
}

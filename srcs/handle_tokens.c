/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:16:08 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/07 20:16:10 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	simple_pipe(t_minishell *minishell, int *i, char *result)
{
	result[0] = minishell->line[*i];
	result[1] = '\0';
	(*i)++;
	minishell->token = push_list(minishell->info, result, 5);
	while (minishell->line[*i] && minishell->line[*i] == ' ')
		(*i)++;
	parse_line (minishell, (*i));
	return (1);
}

int	eperluette(t_minishell *minishell, int *i, char *result)
{
	result[0] = minishell->line[*i];
	result[1] = '\0';
	(*i)++;
	minishell->token = push_list(minishell->info, result, 45);
	while (minishell->line[*i] && minishell->line[*i] == ' ')
		(*i)++;
	parse_line (minishell, (*i));
	return (1);
}

int	parenthese(t_minishell *minishell, int *i, char *result)
{
	int	utils;

	utils = 11;
	if (minishell->line[*i] == ')')
		utils = 12;
	result[0] = minishell->line[*i];
	result[1] = '\0';
	(*i)++;
	minishell->token = push_list(minishell->info, result, utils);
	while (minishell->line[*i] && minishell->line[*i] == ' ')
		(*i)++;
	parse_line (minishell, (*i));
	return (1);
}

int	double_operator(t_minishell *minishell, int *i, int type, char *result)
{
	result[0] = minishell->line[*i];
	result[1] = minishell->line[*i];
	result[2] = '\0';
	(*i) = (*i) + 2;
	minishell->token = push_list(minishell->info, result, type);
	while (minishell->line[*i] && minishell->line[*i] == ' ')
		(*i)++;
	parse_line (minishell, (*i));
	return (1);
}

int	is_infile_or_outfile(t_minishell *minishell, int *i, char *result)
{
	int	utils;

	utils = 7;
	if (minishell->line[(*i)] == '>')
		utils = 8;
	result[0] = '\0';
	(*i)++;
	while (minishell->line[(*i)] && minishell->line[(*i)] == ' ')
		(*i)++;
	while (minishell->line[(*i)] && not_token(minishell->line[(*i)]))
	{
		if (minishell->line[*i] == 39)
			result = custom_strjoin(result, ft_39(minishell, i), 1);
		if (minishell->line[*i] == 34)
			result = custom_strjoin(result, ft_34(minishell, i), 1);
		result = custom_strjoin(result, ft_substr(minishell->line, (*i), 1), 1);
		(*i)++;
	}
	minishell->token = push_list(minishell->info, result, utils);
	while (minishell->line[(*i)] && minishell->line[(*i)] == ' ')
		(*i)++;
	parse_line (minishell, (*i));
	return (1);
}

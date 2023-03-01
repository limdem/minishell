/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PL1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:54:06 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/07 19:54:15 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	inside_regular(t_minishell *minishell, int *i, char **result)
{
	if (minishell->line[(*i)] == 34)
	{
		*result = custom_strjoin(*result, ft_34(minishell, i), 1);
		regularstr(minishell, i, *result);
		return (0);
	}
	if (minishell->line[(*i)] == 39)
	{
		*result = custom_strjoin(*result, ft_39(minishell, i), 1);
		regularstr(minishell, i, *result);
		return (0);
	}
	if (minishell->line[(*i)] == '$')
	{
		*result = custom_strjoin(*result, dollars_sign(minishell, i, 0), 1);
		regularstr(minishell, i, *result);
		return (0);
	}
	if ((minishell->line[(*i)] && !not_token(minishell->line[(*i)]))
		|| (!minishell->line[(*i)]))
		return (2);
	return (1);
}

int	is_13(char *result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		if (result[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	regularstr(t_minishell *minishell, int *i, char *result)
{
	int	utils;

	utils = 0;
	while (minishell->line[(*i)] && minishell->line[(*i)] != ' ')
	{
		if (minishell->line[(*i)] != 92)
		{
			if (!(inside_regular(minishell, i, &result)))
				return (1);
			if (inside_regular(minishell, i, &result) == 2)
				break ;
			result = custom_strjoin(result, ft_substr
					(minishell->line, (*i), 1), 1);
		}
		(*i)++;
	}
	utils = is_13(result);
	if (utils == 0)
		minishell->token = push_list(minishell->info, result,
				is_wildcard(result, *i, minishell));
	if (utils > 0)
		minishell->token = push_list(minishell->info, result, 13);
	parse_line (minishell, (*i));
	return (1);
}

int	inside_parse_line(t_minishell *minishell, int *i, char *result)
{
	if (minishell->line[*i] == '|' && minishell->line[*i + 1] != '|')
		if (simple_pipe(minishell, i, result))
			return (0);
	if (minishell->line[*i] == '&' && minishell->line[*i + 1] != '&')
		if (eperluette(minishell, i, result))
			return (0);
	if ((minishell->line[*i] == '<' && minishell->line[*i + 1] != '<')
		|| (minishell->line[*i] == '>' && minishell->line[*i + 1] != '>'))
		if (is_infile_or_outfile (minishell, i, result))
			return (0);
	if (minishell->line[*i] == '(' || minishell->line[*i] == ')')
		if (parenthese(minishell, i, result))
			return (0);
	if (minishell->line[*i] == '&' && minishell->line[*i + 1] == '&')
		if (double_operator (minishell, i, 9, result))
			return (0);
	if (minishell->line[*i] == '|' && minishell->line[*i + 1] == '|')
		if (double_operator (minishell, i, 10, result))
			return (0);
	if (minishell->line[*i] == '<' && minishell->line[*i + 1] == '<')
		if (redirection (minishell, i, 14, result))
			return (0);
	return (1);
}

int	parse_line(t_minishell *minishell, int i)
{
	char	*result;

	result = malloc(sizeof(char) * (3));
	if (!result)
		ft_putstr_fd("MALLOC PARSE LINE\n", 2);
	result[0] = '\0';
	while (minishell->line[(i)] && minishell->line[(i)] == ' ')
		(i)++;
	while (minishell->line[i])
	{
		if (minishell->quote == 0)
		{
			if (!inside_parse_line(minishell, &i, result))
				return (1);
			if (minishell->line[i] == '>' && minishell->line[i + 1] == '>')
				if (redirection (minishell, &i, 15, result))
					return (1);
		}
		if (minishell->line[i])
			if (regularstr(minishell, &i, result))
				return (1);
	}
	free(result);
	return (1);
}

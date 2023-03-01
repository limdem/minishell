/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_spe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:15:55 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/10 11:27:42 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_34(t_minishell *minishell, int *i)
{
	char	*result;

	result = malloc(sizeof(char) * 1);
	if (!result)
		ft_putstr_fd("MALLOC 34\n", 2);
	result[0] = '\0';
	(*i)++;
	while (minishell->line[(*i)] && minishell->line[(*i)] != 34)
	{
		if (minishell->line[(*i)] == '$')
		{
			result = custom_strjoin(result, dollars_sign(minishell, i, 1), 1);
		}
		else
			result = custom_strjoin(result,
					ft_substr(minishell->line, (*i), 1), 1);
		(*i)++;
	}
	(*i)++;
	return (result);
}

char	*ft_39(t_minishell *minishell, int *i)
{
	char	*result;

	result = malloc(sizeof(char *) * (1));
	if (!result)
		ft_putstr_fd("MALLOC 39\n", 2);
	result[0] = '\0';
	(*i)++;
	while (minishell->line[(*i)] && minishell->line[(*i)] != 39)
	{
		result = custom_strjoin(result, ft_substr(minishell->line, (*i), 1), 1);
		if (minishell->line[(*i)] == 39)
			break ;
		(*i)++;
	}
	(*i)++;
	return (result);
}

int	verification(char **result, t_minishell *minishell, int *i)
{
	if (minishell->line[((*i) + 1)] == 34)
		return (0);
	if (!ft_isalpha(*result[0]) && *result[0] != '?' && !ft_isdigit(*result[0]))
	{
		minishell->check = 0;
		*result = custom_strjoin(ft_strdup("$"), *result, 1);
		(*i)++;
		return (0);
	}
	if (ft_isdigit(*result[0]))
	{
		(*i)++;
		return (0);
	}
	if (*result[0] == '?')
	{
		(*i)++;
		return (0);
	}
	return (1);
}

char	*dollars_sign(t_minishell *minishell, int *i, int quote)
{
	char	*result;

	result = create_result();
	minishell->check = 1;
	(*i)++;
	while (minishell->line[(*i)] && not_token(minishell->line[(*i)]) == 2)
	{
		result = custom_strjoin(result, ft_substr(minishell->line, (*i), 1), 1);
		if (!verification(&result, minishell, i))
			break ;
		(*i)++;
	}
	if (not_token(minishell->line[(*i)]) == 1 && !quote)
		return (result);
	if (!ft_strlen(result))
		result = custom_strjoin(ft_strdup("$"), result, 1);
	if (quote && not_token(minishell->line[(*i)]) < 2)
			(*i)--;
	if (minishell->check)
		return (check_extension(result, minishell));
	if (!minishell->check)
		return (result);
	return (0);
}

int	not_token(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '('
		|| c == ')' || c == '&' || c == '>' || c == '$' )
		return (0);
	if (c == 34 || c == 39)
		return (1);
	return (2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:38:48 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/08 15:47:04 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	type(int type)
{
	if (type == 5 || type == 6 || type == 10 || type == 9)
	{
		return (1);
	}
	return (0);
}

int	inside_grammar(t_token *token)
{
	if ((token)->type == 14 || (token)->type == 15
		|| token->type == 7 || token->type == 8)
	{
		if (token->str[0] == '\0')
		{
			ft_putstr_fd("bash: syntax error near unexpected token\n", 2);
			return (0);
		}
	}
	if ((token)->type == 5 && ((!(token)->previous) || (!(token)->next)))
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	if ((token)->type == 10 && ((!(token)->previous) || (!(token)->next)))
	{
		ft_putstr_fd("bash: syntax error near unexpected token\n", 2);
		return (0);
	}
	if ((token)->type == 13 && ((!(token)->previous)))
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
		return (0);
	}
	return (1);
}

int	ft_grammar(t_token *token)
{
	if (token)
	{
		if ((token)->type == 45)
		{
			ft_putstr_fd("bash: syntax error unexpected token\n", 2);
			return (0);
		}
		if (!inside_grammar(token))
			return (0);
		if (type(token->type) && ((!(token)->previous) || (!(token)->next)))
		{
			ft_putstr_fd("bash: syntax error near unexpected token\n", 2);
			return (0);
		}
		if (token->type == 12 && ((!(token)->next && token->previous
					&& token->previous->type != 1) || !(token)->previous))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `)'\n", 2);
			return (0);
		}
	}
	return (1);
}

int	verif_quote(char *str)
{
	int	i;
	int	insides;
	int	insided;

	insided = -1;
	insides = -1;
	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
			if (insides == -1)
				insided = insided * (-1);
		if (str[i] == 39)
			if (insided == -1)
				insides = insides * (-1);
		i++;
	}
	if (insided == 1 || insides == 1)
	{
		ft_putstr_fd("bash: odd number of quotes\n", 2);
		return (0);
	}
	return (1);
}

void	free_me_from_minishell_end(t_minishell *minishell)
{
	t_token	*temp;

	if (minishell->grammar && minishell->ishd)
		free_here_doc(minishell);
	minishell->token = minishell->info->last;
	while (minishell->token)
	{
		temp = minishell->token;
		free(minishell->token->str);
		minishell->token = minishell->token->previous;
		free(temp);
	}
	minishell->grammar = 1;
	free(minishell->info);
	free(minishell->line);
}

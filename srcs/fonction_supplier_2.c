/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_supplier_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:37:15 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/16 12:37:17 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_arg_echo(char *str)
{
	int	i;

	i = 2;
	if (str && !ft_strncmp(str, "-n", 2))
	{
		while (str[i])
		{
			if (str[i] == 110)
				i++;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}

void	free_here_doc(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (minishell->token)
	{
		while (minishell->here[i])
			free (minishell->here[i++]);
		free(minishell->here);
	}
}

int	is_wildcard(char *str, int a, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			if (!not_34(minishell->line, a))
				return (16);
		i++;
	}
	return (1);
}

int	not_34(char *str, int i)
{
	i--;
	while (str[i] && str[i] != '*')
		i--;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

void	determine_size(t_token *token, int *size)
{
	*size = 0;
	while (token)
	{
		if (token->type == 14)
			(*size)++;
		token = token->next;
	}
}

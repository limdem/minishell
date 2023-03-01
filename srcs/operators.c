/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:29:43 by dgauvin           #+#    #+#             */
/*   Updated: 2022/06/08 15:31:37 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_operator(t_token **token)
{
	while (*token)
	{
		if ((*token)->type == 9)
		{
			*token = (*token)->next;
			return (1);
		}
		if ((*token)->type == 10)
		{
			*token = (*token)->next;
			return (2);
		}
		if (!(*token)->next)
			return (-1);
		*token = (*token)->next;
	}
	return (-1);
}

int	handle_continue(int status, int operator)
{
	if (operator == 1 && !status)
		return (0);
	if (operator == 2 && status)
		return (0);
	return (1);
}

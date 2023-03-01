/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:57:05 by dgauvin           #+#    #+#             */
/*   Updated: 2022/06/08 15:18:11 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	move_next_cmds_pipe(t_token **token)
{
	while (*token)
	{
		if ((*token)->type == 5)
		{
			*token = (*token)->next;
			return (1);
		}
		if (!(*token)->next)
			break ;
		*token = (*token)->next;
	}
	return (-1);
}

void	determine_pipe_num(t_token *token, t_p_exec *p_exec)
{
	t_token	*tmp;

	tmp = token;
	p_exec->cmds_nbr = 1;
	while (tmp && !(tmp->type == 9 || tmp->type == 10))
	{
		if (tmp->type == 5)
			p_exec->cmds_nbr++;
		tmp = tmp->next;
	}
	p_exec->save_cmds_nbr = p_exec->cmds_nbr;
}

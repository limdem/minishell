/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:34:49 by dgauvin           #+#    #+#             */
/*   Updated: 2022/06/09 23:36:23 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_execution3(t_p_exec *p_exec)
{
	while (wait(NULL) != -1)
		;
	p_exec->exit_code = 2;
	close(p_exec->pipe_fd[0]);
	close(p_exec->s_in);
	close(p_exec->s_out);
	free_me_from_minishell(p_exec, p_exec->exit_code, NULL, 0);
}

void	exit_execution2(t_p_exec *p_exec)
{	
	while (wait(NULL) != -1)
		;
	p_exec->exit_code = 0;
	close(p_exec->pipe_fd[0]);
	close(p_exec->s_in);
	close(p_exec->s_out);
	free_me_from_minishell(p_exec, p_exec->exit_code, NULL, 0);
}

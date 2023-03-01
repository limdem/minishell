/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:01:25 by dgauvin           #+#    #+#             */
/*   Updated: 2022/06/08 21:21:43 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	go_next_cmd(t_token **token)
{
	if ((*token)->type == 11)
	{
		while ((*token)->type != 12)
			*token = (*token)->next;
	}
	else
	{
		while (*token && ((*token)->type != 9 && (*token)->type != 10))
		{
			if ((*token)->next)
				*token = (*token)->next;
			else
				return (-1);
		}
	}
	return (1);
}

int	move_next_cmds(t_token **token, int status)
{
	int	operator;
	int	continue_exec;

	continue_exec = 1;
	while (continue_exec)
	{
		operator = find_operator(token);
		if (operator == -1)
			return (-1);
		continue_exec = handle_continue(status, operator);
		if (!continue_exec)
			return (0);
		if (go_next_cmd(token) == -1)
			return (-1);
	}
	return (0);
}

int	execute_commands(t_token *token, t_p_exec *p_exec)
{
	int	pid;

	p_exec->first_cmd = 1;
	p_exec->exit_code = -1;
	p_exec->s_in = dup(STDIN_FILENO);
	p_exec->s_out = dup(STDOUT_FILENO);
	determine_pipe_num(token, p_exec);
	while (p_exec->cmds_nbr > 0)
	{
		if (handle_execution(&token, p_exec, &pid))
			return (1);
		p_exec->cmds_nbr--;
		if (p_exec->cmds_nbr > 0)
			move_next_cmds_pipe(&token);
		p_exec->first_cmd = 0;
	}
	close(p_exec->pipe_fd[0]);
	restore_fd(p_exec->s_in, p_exec->s_out);
	waitpid (pid, (int *)&g_code, 0);
	g_code = WEXITSTATUS(g_code);
	if (p_exec->exit_code >= 0)
		g_code = p_exec->exit_code;
	while (wait(NULL) != -1)
		;
	return (0);
}

int	execute_line(t_minishell *minishell)
{
	t_p_exec	p_exec;
	int			continue_exec;

	minishell->token = minishell->info->first;
	minishell->suppressor = &p_exec;
	p_exec.env = minishell->env;
	p_exec.gate = minishell;
	p_exec.here = minishell->here;
	p_exec.here_index = 0;
	p_exec.envi = &(minishell->envi);
	continue_exec = 0;
	while (continue_exec != -1)
	{
		if (execute_commands(minishell->token, &p_exec))
			return (1);
		continue_exec = move_next_cmds(&minishell->token, g_code);
	}
	return (0);
}

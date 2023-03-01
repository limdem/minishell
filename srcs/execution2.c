/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:37:14 by dgauvin           #+#    #+#             */
/*   Updated: 2022/06/09 23:44:38 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_cmd(t_token **token, t_p_exec *p_exec)
{
	p_exec->cmd = NULL;
	if ((*token)->type == 16)
	{
		p_exec->cmd = (*token)->str;
		return ;
	}
	while (*token && !((*token)->type == 9 || (*token)->type == 10))
	{
		if ((*token)->type == 1)
			p_exec->cmd = (*token)->str;
		if (!(*token)->next || p_exec->cmd)
			break ;
		*token = (*token)->next;
	}
	p_exec->cmd = (*token)->str;
}

int	args_handler(t_token **token, t_p_exec *p_exec, int index)
{
	p_exec->args[++index] = cmd_to_args(*token, p_exec->cmd, p_exec);
	if (!p_exec->args[index])
		return (0);
	if (*token)
		(*token) = (*token)->next;
	index++;
	while (*token && ((*token)->type == 1 || (*token)->type == 16))
	{
		if ((*token)->type == 16)
		{
			if (handle_wild_args((*token)->str, p_exec->args, &index))
				return (1);
		}
		else
		{	
			if (index < p_exec->args_nbr + 1)
			{
				p_exec->args[index++] = ft_strdup((*token)->str);
				free_me_from_minishell(p_exec, 0, p_exec->args[index - 1], 0);
			}
		}
		*token = (*token)->next;
	}
	p_exec->args[index] = NULL;
	return (0);
}

int	handle_args(t_token **token, int *args_nbr, t_p_exec *p_exec)
{
	if (count_args(*token, args_nbr))
		return (1);
	initialize_args_handler(p_exec);
	if (args_handler(token, p_exec, -1))
		return (1);
	if (! strcmp (p_exec->cmd, "./minishell"))
		p_exec->gate->erasemn = 1;
	else
		p_exec->gate->erasemn = 0;
	return (0);
}

int	handle_execution(t_token **token, t_p_exec *p_exec, int *pid)
{
	*pid = 1;
	if (pipe_redirections(p_exec->pipe_fd, &p_exec->input,
			&p_exec->output, p_exec->first_cmd))
		return (1);
	if (inf_outf_redirections(*token, p_exec))
		return (1);
	handle_cmd(token, p_exec);
	if (handle_args(token, &p_exec->args_nbr, p_exec))
		return (1);
	p_exec->is_built_in = built_in(p_exec);
	if (!p_exec->is_built_in)
		*pid = fork();
	if (!(*pid))
		handle_execve(p_exec);
	if (*pid && p_exec->is_built_in != 0)
	{
		if (!p_exec->denied)
			dispatcher(token, p_exec);
		return (0);
	}
	if (p_exec->here_inf)
		write_here_doc(p_exec->here_pipe_fd[1], p_exec->here);
	free_args(p_exec->args, p_exec->args_nbr);
	return (0);
}

void	restore_fd(int save_input, int save_output)
{
	dup2(save_input, STDIN_FILENO);
	close(save_input);
	dup2(save_output, STDOUT_FILENO);
	close(save_output);
}

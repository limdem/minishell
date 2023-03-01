/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:46:31 by dgauvin           #+#    #+#             */
/*   Updated: 2022/06/08 15:53:18 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	determine_inf_outf(t_token *token, t_p_exec *p_exec)
{
	t_token	*tmp;

	tmp = token;
	p_exec->infile = NULL;
	p_exec->outfile = NULL;
	p_exec->here_inf = 0;
	p_exec->app_outfile = NULL;
	p_exec->denied = 0;
	while (tmp && !(tmp->type == 5 || tmp->type == 9 || tmp->type == 10))
	{
		if (tmp->type == 7)
			p_exec->infile = tmp->str;
		if (tmp->type == 8)
			p_exec->outfile = tmp->str;
		if (tmp->type == 14)
			p_exec->here_inf = 1;
		if (tmp->type == 15)
			p_exec->app_outfile = tmp->str;
		tmp = tmp->next;
	}
}

int	infile_redirection(t_p_exec *p_exec)
{
	int	tmp_input;

	if (p_exec->infile)
	{
		tmp_input = p_exec->input;
		if (!p_exec->first_cmd)
			close(p_exec->prev_pipe_in);
		p_exec->input = open(p_exec->infile, O_RDONLY);
		if (inf_error(&p_exec->exit_code, &p_exec->input, tmp_input))
			return (1);
	}
	if (p_exec->here_inf)
	{
		if (pipe(p_exec->here_pipe_fd) == -1)
			return (1);
		if (!p_exec->first_cmd)
			close(p_exec->prev_pipe_in);
		p_exec->input = p_exec->here_pipe_fd[0];
	}
	if (!(p_exec->infile || p_exec->here_inf) && p_exec->first_cmd)
		p_exec->input = dup(p_exec->s_in);
	return (0);
}

int	outfile_redirection(t_p_exec *p_exec)
{
	int	tmp_output;

	tmp_output = p_exec->output;
	if (p_exec->outfile)
	{
		close(p_exec->output);
		p_exec->output = open(p_exec->outfile,
				O_CREAT | O_WRONLY | O_TRUNC, 0664);
	}
	if (p_exec->app_outfile)
	{
		close(p_exec->output);
		p_exec->output = open(p_exec->app_outfile,
				O_CREAT | O_APPEND | O_WRONLY, 0664);
	}
	if (out_error(p_exec, tmp_output))
		return (1);
	p_exec->output = tmp_output;
	if (!(p_exec->outfile || p_exec->app_outfile)
		&& p_exec->cmds_nbr == 1)
	{
		close(p_exec->output);
		p_exec->output = dup(p_exec->s_out);
	}
	return (0);
}

int	pipe_redirections(int pipe_fd[2], int *input, int *output, int first_cmd)
{
	if (first_cmd)
	{
		if (pipe(pipe_fd) == -1)
			return (1);
		*input = pipe_fd[0];
		*output = pipe_fd[1];
	}
	else
	{
		*input = pipe_fd[0];
		if (pipe(pipe_fd) == -1)
			return (1);
		*output = pipe_fd[1];
	}
	return (0);
}

int	inf_outf_redirections(t_token *token, t_p_exec *p_exec)
{
	determine_inf_outf(token, p_exec);
	if (infile_redirection(p_exec) || outfile_redirection(p_exec))
		return (1);
	p_exec->prev_pipe_in = p_exec->pipe_fd[0];
	dup2(p_exec->input, STDIN_FILENO);
	close(p_exec->input);
	dup2(p_exec->output, STDOUT_FILENO);
	close(p_exec->output);
	return (0);
}

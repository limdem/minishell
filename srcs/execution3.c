/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:44:14 by dgauvin           #+#    #+#             */
/*   Updated: 2022/06/09 23:46:32 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_here_doc(int here_pipe_fd_out, char **here)
{
	int	i;

	i = 0;
	while (here[i])
	{
		write(here_pipe_fd_out, here[i], ft_strlen(here[i]));
		i++;
	}
	close(here_pipe_fd_out);
}

int	count_args(t_token *token, int *args_nbr)
{
	t_token		*tmp;
	t_wild_args	wd_args;

	tmp = token;
	*args_nbr = -1;
	if (tmp->type == 8 || tmp->type == 15 || tmp->type == 16)
	{
		*args_nbr = 1;
		tmp = tmp->next;
	}
	while (tmp && (tmp->type == 1 || tmp->type == 14 || tmp->type == 16))
	{
		if (tmp->type == 16)
		{
			if (count_wild_args(tmp->str, args_nbr, wd_args))
				return (1);
		}
		else
			(*args_nbr)++;
		tmp = tmp->next;
	}
	return (0);
}

int	initialize_cmd_to_args(t_cmd_args *cmd_args, t_token *token)
{
	cmd_args->index = 0;
	cmd_args->args_nbr = 0;
	if (token->type == 14 || ((token->type == 7 || token->type == 8
				|| token->type == 15) && !token->next))
		return (1);
	return (0);
}

char	*cmd_to_args(t_token *token, char *cmd, t_p_exec *p_exec)
{
	t_cmd_args	cmd_args;
	t_wild_args	wd_args;

	if (initialize_cmd_to_args(&cmd_args, token))
		return (NULL);
	if (token->type == 16 && cmd[0] == '*')
	{
		if (count_wild_args(token->str, &cmd_args.args_nbr, wd_args))
			free_me_from_minishell(p_exec, 1, NULL, 1);
		cmd_args.cmd_wild = malloc((cmd_args.args_nbr + 1) * sizeof(char *));
		free_me_from_minishell(p_exec, p_exec->exit_code, cmd_args.cmd_wild, 0);
		cmd_args.cmd_wild[cmd_args.args_nbr] = 0;
		if (handle_wild_args(token->str, cmd_args.cmd_wild, & cmd_args.index))
			free_me_from_minishell(p_exec, 1, NULL, 1);
		cmd_args.cur_exec = ft_strdup(cmd_args.cmd_wild[0]);
		free_me_from_minishell(p_exec, p_exec->exit_code, cmd_args.cur_exec, 0);
		free_args(cmd_args.cmd_wild, cmd_args.args_nbr);
	}
	else
	{
		cmd_args.cur_exec = ft_strdup(cmd);
		free_me_from_minishell(p_exec, p_exec->exit_code, cmd_args.cur_exec, 0);
	}
	return (cmd_args.cur_exec);
}

int	handle_execve(t_p_exec *p_exec)
{
	close(p_exec->pipe_fd[0]);
	close(p_exec->s_in);
	close(p_exec->s_out);
	if (!p_exec->args[0])
	{
		if (p_exec->here_inf)
			close(p_exec->here_pipe_fd[1]);
		exit(0);
	}
	determine_path(p_exec->cmd, &p_exec->path, *p_exec->env);
	if (!p_exec->path)
		determine_cmd_no_path(p_exec);
	else
		determine_cmd_path(p_exec);
	handle_error(p_exec->args[0], p_exec->args, p_exec->args_nbr);
	return (0);
}

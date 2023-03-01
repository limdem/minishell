/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_supplier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:23:30 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/16 12:23:32 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirection(t_minishell *minishell, int *i, int type, char *result)
{
	result[0] = '\0';
	(*i) = (*i) + 2;
	while (minishell->line[*i] && minishell->line[*i] == ' ')
		(*i)++;
	while (minishell->line[(*i)] && not_token(minishell->line[(*i)]))
	{
		if (minishell->line[*i] == 34)
			result = custom_strjoin(result,
					ft_34(minishell, i), 1);
		if (minishell->line[*i] == 39)
			result = custom_strjoin(result, ft_39(minishell, i), 1);
		result = custom_strjoin(result, ft_substr(minishell->line, (*i), 1), 1);
		(*i)++;
	}
	minishell->token = push_list(minishell->info, result, type);
	parse_line (minishell, (*i));
	return (1);
}

void	exit_execution1(t_p_exec *p_exec)
{
	while (wait(NULL) != -1)
		;
	p_exec->exit_code = g_code;
	close(p_exec->pipe_fd[0]);
	close(p_exec->s_in);
	close(p_exec->s_out);
	free_me_from_minishell(p_exec, p_exec->exit_code, NULL, 0);
}

void	exit_execution0(int *exit_code, char **args, int args_nbr)
{
	*exit_code = 1;
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	free_args(args, args_nbr);
}

void	inside_exit_execution(t_p_exec *p_exec)
{
	p_exec->exit_code = 2;
	ft_putstr_fd("bash: exit: numeric argument required\n", 2);
	if (p_exec->first_cmd == 1 && p_exec->cmds_nbr == 1)
		exit_execution3(p_exec);
}

void	exit_execution(t_p_exec *p_exec)
{
	if (p_exec->args_nbr > 1)
	{
		p_exec->exit_code = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		free_args(p_exec->args, p_exec->args_nbr);
		return ;
	}
	if (p_exec->args[1] && arg_is_numeric(p_exec->args[1])
		&& ft_atoi(p_exec->args[1]) != 1786594284136218)
	{
		g_code = (ft_atoi(p_exec->args[1]) % 256);
		p_exec->exit_code = g_code;
		if (p_exec->first_cmd == 1 && p_exec->cmds_nbr == 1)
			exit_execution1(p_exec);
	}
	if (!p_exec->args[1])
	{
		p_exec->exit_code = 0;
		if (p_exec->first_cmd == 1 && p_exec->cmds_nbr == 1)
			exit_execution2(p_exec);
	}
	else
		inside_exit_execution(p_exec);
	free_args(p_exec->args, p_exec->args_nbr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:33:38 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/09 23:24:00 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dispatcher(t_token **token, t_p_exec *p_exec)
{
	if (!ft_strcmp(p_exec->cmd, "cd"))
		cd_execution(p_exec);
	else if (!ft_strcmp(p_exec->cmd, "export"))
		export_execution(token, p_exec);
	else if (!ft_strcmp(p_exec->cmd, "unset"))
		unset_execution(p_exec);
	else if (!ft_strcmp(p_exec->cmd, "env"))
		env_execution(p_exec);
	else if (!ft_strcmp(p_exec->cmd, "pwd"))
		pwd_execution(p_exec);
	else if (!ft_strcmp(p_exec->cmd, "echo"))
		echo_execution(p_exec);
	else if (!ft_strcmp(p_exec->cmd, "exit"))
		exit_execution(p_exec);
}

void	echo_execution(t_p_exec *p_exec)
{
	echo(p_exec->args);
	g_code = 0;
	free_args(p_exec->args, p_exec->args_nbr);
}

int	cd_execution0(int *exit_code, char **args, int args_nbr)
{
	g_code = 1;
	*exit_code = g_code;
	ft_putstr_fd("minishell: cd: too many argumets\n", 2);
	free_args(args, args_nbr);
	return (1);
}

void	cd_execution1(t_p_exec *p_exec)
{
	int	i;

	i = 0;
	while (p_exec->env[0][i])
	{
		if (!ft_strncmp(p_exec->env[0][i], "HOME", 4))
			break ;
		i++;
	}
	if (chdir((const char *)p_exec->env[0][i] + 5) == -1)
		free_me_from_minishell(p_exec, 1, NULL, 1);
}

void	cd_execution(t_p_exec *p_exec)
{
	if (p_exec->args_nbr > 1)
		if (cd_execution0(&p_exec->exit_code, p_exec->args, p_exec->args_nbr))
			return ;
	if (!p_exec->args_nbr || !ft_strcmp(p_exec->args[1], "~"))
	{
		cd_execution1(p_exec);
		return ;
	}
	if (chdir((const char *)p_exec->args[1]) == -1)
	{
		if (errno == 116 || errno == 14)
		{
			g_code = 1;
			p_exec->exit_code = g_code;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(p_exec->args[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return ;
		}
	}
	g_code = 0;
	free_args(p_exec->args, p_exec->args_nbr);
}

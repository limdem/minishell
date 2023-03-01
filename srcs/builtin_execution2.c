/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:44:19 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/09 23:33:34 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_execution(t_token **token, t_p_exec *p_exec)
{
	export(token, p_exec);
	g_code = 0;
	free_args(p_exec->args, p_exec->args_nbr);
}

void	unset_execution(t_p_exec *p_exec)
{
	int	p;

	p = 1;
	if (!(p_exec)->args[1])
		ft_putstr_fd("unset: not enough arguments\n", 2);
	while ((p_exec)->args[p])
	{
		*(p_exec)->env = unset_env((p_exec)->args[p],
				*(p_exec)->env, p_exec->envi);
		p++;
	}
	g_code = 0;
	free_args(p_exec->args, p_exec->args_nbr);
}

void	env_execution(t_p_exec *p_exec)
{
	int	i;

	i = 0;
	while (p_exec->env[0][i])
		printf("%s\n", p_exec->env[0][i++]);
	g_code = 0;
	free_args(p_exec->args, p_exec->args_nbr);
}

void	pwd_execution(t_p_exec *p_exec)
{
	print_pwd(p_exec);
	g_code = 0;
	free_args(p_exec->args, p_exec->args_nbr);
}

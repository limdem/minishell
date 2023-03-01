/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:36:11 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/10 11:26:59 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*push_empty_list(t_db_list *info, char *str, int type)
{
	t_token	*new_env;

	new_env = malloc(sizeof(t_token));
	if (!new_env)
		ft_putstr_fd("MALLOC EMPTY LIST\n", 2);
	new_env->next = NULL;
	new_env->previous = NULL;
	new_env->str = str;
	new_env->type = type;
	info->first = new_env;
	info->last = new_env;
	info->lenght = 1;
	return (new_env);
}

t_token	*push_full_list(t_db_list *info, char *str, int type)
{
	t_token	*new_env;

	new_env = malloc(sizeof(t_token));
	if (!new_env)
		ft_putstr_fd("MALLOC FULL LIST\n", 2);
	new_env->str = str;
	new_env->type = type;
	new_env->next = NULL;
	info->last->next = new_env;
	new_env->previous = info->last;
	info->last = new_env;
	info->lenght = info->lenght + 1;
	return (new_env);
}

t_token	*push_list(t_db_list *info, char *str, int type)
{
	if (info->lenght == 0)
		return (push_empty_list (info, str, type));
	if (info->lenght > 0)
		return (push_full_list(info, str, type));
	return (0);
}

t_db_list	*init_list(t_db_list *info)
{
	info = malloc(sizeof(t_db_list));
	if (!info)
		ft_putstr_fd("MALLOC INIT LIST\n", 2);
	info->first = NULL;
	info->last = NULL;
	info->lenght = 0;
	return (info);
}

void	free_me_from_minishell(t_p_exec *p_exec, int sortie,
		void *pointer, int force)
{
	t_token	*temp;

	if (pointer && !force)
		return ;
	if (p_exec->gate->grammar && p_exec->gate->ishd)
		free_here_doc(p_exec->gate);
	p_exec->gate->token = p_exec->gate->info->last;
	while (p_exec->gate->token)
	{
		temp = p_exec->gate->token;
		free(p_exec->gate->token->str);
		p_exec->gate->token = p_exec->gate->token->previous;
		free(temp);
	}
	free_envi(&p_exec->gate->envi, *p_exec->gate->env);
	p_exec->gate->grammar = 1;
	free(p_exec->gate->info);
	free(p_exec->gate->line);
	free_args(p_exec->args, p_exec->args_nbr);
	exit(sortie);
}

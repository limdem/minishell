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

void	initialize_args_handler(t_p_exec *p_exec)
{
	p_exec->args = malloc((p_exec->args_nbr + 2) * sizeof(char *));
	free_me_from_minishell(p_exec, 0, p_exec->args, 0);
}

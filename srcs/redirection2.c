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

int	inf_error(int *exit_code, int *input, int tmp_input)
{
	if (*input == -1 && errno != 2 && errno != 13)
		return (1);
	if (*input == -1 && (errno == 2 || errno == 13))
	{
		*exit_code = 1;
		ft_putstr_fd("Permission denied\n", 2);
		*input = tmp_input;
	}
	return (0);
}

int	out_error(t_p_exec *p_exec, int tmp_output)
{
	if (errno == 13)
	{
		p_exec->exit_code = 1;
		ft_putstr_fd("Permission denied\n", 2);
		p_exec->output = tmp_output;
		p_exec->denied = 1;
		return (0);
	}		
	if (p_exec->output == -1)
		return (1);
	return (0);
}

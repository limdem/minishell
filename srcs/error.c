/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:54:13 by dgauvin           #+#    #+#             */
/*   Updated: 2022/06/08 15:59:35 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_errno_13(char *cmd, char **args, int args_nbr)
{
	if (is_a_directory(cmd) || (cmd[0] == '~' && cmd[1] == 0))
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		free_args(args, args_nbr);
		write(2, " : is a directory\n", 18);
	}
	else
	{
		free_args(args, args_nbr);
		write(2, ": Permission denied\n", 20);
	}
	exit(126);
}

void	handle_not_found(char *cmd, char **args, int args_nbr)
{
	write(2, cmd, ft_strlen(cmd));
	free_args(args, args_nbr);
	write(2, " : command not found\n", 21);
	exit(127);
}

void	handle_exception(char *cmd, char **args, int args_nbr)
{
	if ((cmd[0] == '!' && cmd [1] == 0))
	{
		free_args(args, args_nbr);
		exit(1);
	}
	if (cmd[0] == ':' && cmd [1] == 0)
	{
		free_args(args, args_nbr);
		exit(1);
	}
}

void	handle_error(char *cmd, char **args, int args_nbr)
{
	if (errno == 13 || (cmd[0] == '~' && cmd[1] == 0))
		handle_errno_13(cmd, args, args_nbr);
	handle_exception(cmd, args, args_nbr);
	handle_not_found(cmd, args, args_nbr);
}

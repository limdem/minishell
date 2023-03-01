/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:47:06 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/16 10:47:08 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	launch_infinite(struct sigaction *sig)
{
	sig->sa_handler = &handler_infinite_command;
	sigaction(SIGINT, sig, 0);
	sigaction(SIGQUIT, sig, 0);
}

void	launch_classic(struct sigaction *sig)
{
	sig->sa_handler = &handler;
	sigaction(SIGINT, sig, 0);
	sigaction(SIGQUIT, sig, 0);
}

void	launch_default(struct sigaction *sig)
{
	sig->sa_handler = SIG_DFL;
	sigaction(SIGQUIT, sig, 0);
	sigaction(SIGINT, sig, 0);
}

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		g_code = 130;
		ft_putendl("");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signal == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
}

void	handler_infinite_command(int signal)
{
	if (signal == SIGINT)
	{
		g_code = 130;
		ft_putendl("");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

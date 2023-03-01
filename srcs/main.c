/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:23:50 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/10 11:23:52 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

long long int	g_code = 0;

int	main(int argc, char *argv[], char *env[])
{
	t_minishell			minishell;
	struct sigaction	sig;

	prepare_readline(argc, argv, &minishell, &sig);
	minishell.info = init_minishell(&minishell, &env, &sig);
	minishell.line = readline("minishell$ ");
	while (minishell.line)
	{
		prepare_handler(&minishell, &sig);
		launch_infinite (&sig);
		if (minishell.grammar > 0 && ft_strlen(minishell.line))
			if (minishell.token)
				if (execute_line(&minishell))
					return (1);
		free_me_from_minishell_end(&minishell);
		launch_classic (&sig);
		if (minishell.erasemn)
			ft_putendl("");
		ft_putstr_fd("\b\b\b\b\b\b\b\b\b\b\b", 1);
		minishell.line = readline("minishell$ ");
	}
	free_envi(&minishell.envi, *minishell.env);
	return (1);
}

int	prepare_readline(int argc, char **argv, t_minishell *minishell,
	struct sigaction *sig)
{
	(void)argv;
	minishell->envi = 0;
	minishell->erasemn = 0;
	minishell->ishd = 0;
	argc++;
	minishell->grammar = 1;
	ft_memset(sig, 0, sizeof (struct sigaction));
	return (1);
}

int	prepare_handler(t_minishell *minishell, struct sigaction *sig)
{
	minishell->info = init_list(minishell->info);
	if (!verif_quote(minishell->line))
		minishell->grammar = 0;
	if (minishell->grammar)
		parse_line(minishell, 0);
	minishell->token = minishell->info->first;
	add_history(minishell->line);
	while (minishell->token)
	{
		if (!ft_grammar(minishell->token))
		{
			g_code = 2;
			minishell->grammar = 0;
			break ;
		}
		minishell->token = minishell->token->next;
	}
	minishell->token = minishell->info->first;
	if (minishell->grammar > 0 && minishell->token)
	{
		minishell->here = here_doc(minishell->token,
				minishell->info->first, sig, minishell);
		ft_putstr_fd("\b\b  \b\b", 1);
	}
	return (1);
}

t_db_list	*init_minishell(t_minishell *minishell, char **env[],
struct sigaction *sig)
{
	launch_classic (sig);
	minishell->env = env;
	minishell->token = NULL;
	minishell->extension = NULL;
	minishell->grammar = 1;
	minishell->here_doc = -1;
	minishell->quote = 0;
	return (minishell->info);
}

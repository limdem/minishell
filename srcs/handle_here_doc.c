/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:15:36 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/07 20:15:38 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**read_here(t_token *token, int **pipe_fd, char **result)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == 14)
		{
			result[i] = read_pipe_fd(pipe_fd[i], NULL, 0);
			i++;
		}
		token = token->next;
	}
	free(pipe_fd);
	result[i] = NULL;
	return (result);
}

void	initialise_res_pipe(char ***result, int ***pipe_fd, int size)
{
	*result = malloc (sizeof(char *) * (size + 1));
	if (!*result)
		ft_putstr_fd("MALLOC INITIALISE RES PIPE\n", 2);
	*pipe_fd = malloc (sizeof(int *) * size);
	if (!*pipe_fd)
		ft_putstr_fd("MALLOC INITIALISE RES PIPE\n", 2);
}

void	inside_here_doc(t_token *token, t_token *start, t_minishell *minishell,
		t_here_handler	*here_handler)
{
	token = start;
	here_handler->i = -1;
	determine_size(token, &here_handler->size);
	minishell->ishd = here_handler->size;
}

char	**here_doc(t_token *token, t_token *start,
	struct sigaction *sig, t_minishell *minishell)
{
	t_here_handler	here_handler;

	inside_here_doc(token, start, minishell, &here_handler);
	if (!here_handler.size)
		return (0);
	initialise_res_pipe(&here_handler.result,
		&here_handler.pipe_fd, here_handler.size);
	if (!here_handler.result || !here_handler.pipe_fd)
		return (NULL);
	while (++here_handler.i < here_handler.size)
	{
		here_handler.pipe_fd[here_handler.i] = generate_pipe_here();
		if (pipe(here_handler.pipe_fd[here_handler.i]) == -1)
			return (NULL);
	}
	here_handler.pid = fork();
	if (!here_handler.pid)
		create_here_doc(token, start, here_handler, sig);
	wait(NULL);
	here_handler.i = 0;
	here_handler.result = read_here(token,
			here_handler.pipe_fd, here_handler.result);
	return (here_handler.result);
}

char	*put_here_doc(t_token *token)
{
	char	*str;
	char	*result;

	result = malloc(sizeof(char) * (1));
	if (!result)
		ft_putstr_fd("MALLOC HERE DOC\n", 2);
	result[0] = '\0';
	str = readline("> ");
	while (ft_strcmp(str, token->str) && str)
	{
		result = custom_strjoin(result, str, 1);
		result = custom_strjoin(result, ft_strdup("\n"), 1);
		str = readline("> ");
	}
	free(str);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:17:54 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/16 12:17:56 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*read_pipe_fd(int *fds, char *str, int time)
{
	char	*save_str;
	char	*buf;

	close(fds[1]);
	buf = ft_strdup(" ");
	if (read(fds[0], buf, 1) > 0)
	{
		buf[1] = 0;
		if (!time)
			str = ft_strdup(buf);
		else
		{
			save_str = custom_strjoin(str, buf, 0);
			free(str);
			str = save_str;
		}
		free(buf);
		return (read_pipe_fd(fds, str, 1));
	}
	close(fds[0]);
	close(fds[1]);
	free(fds);
	free(buf);
	return (str);
}

void	create_here_doc(t_token *token, t_token *start,
		t_here_handler here_handler, struct sigaction *sig)
{
	char	*result;
	int		i;

	i = 0;
	token = start;
	launch_default (sig);
	free(here_handler.result);
	while (token)
	{
		if (token->type == 14)
		{
			close(here_handler.pipe_fd[i][0]);
			result = put_here_doc(token);
			ft_putstr_fd(result, here_handler.pipe_fd[i][1]);
			free(result);
			close(here_handler.pipe_fd[i][1]);
			free(here_handler.pipe_fd[i]);
			i++;
		}
		token = token->next;
	}
	free(here_handler.pipe_fd);
	exit(0);
}

int	*generate_pipe_here(void)
{
	int	*fds;

	fds = malloc(sizeof(int) * 2);
	if (!fds)
		return (NULL);
	return (fds);
}

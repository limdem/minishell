/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:07:58 by dgauvin           #+#    #+#             */
/*   Updated: 2022/06/09 23:38:12 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	determine_path(char *cmd, char **path, char **env)
{
	int	i;

	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		*path = NULL;
		return ;
	}
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			break ;
	}
	*path = env[i];
}

char	*prepare_cur_exec(t_p_exec *p_exec)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	p_exec->cmd = custom_strjoin(buf, p_exec->cmd + 1, 0);
	free_me_from_minishell(p_exec, 1, (void *)p_exec->cmd, 0);
	free(buf);
	return (p_exec->cmd);
}

void	determine_cmd_no_path(t_p_exec *p_exec)
{
	if (p_exec->cmd[0] == '.' && p_exec->cmd[1] == '/')
		p_exec->cmd = prepare_cur_exec(p_exec);
	if (p_exec->here_inf)
		close(p_exec->here_pipe_fd[1]);
	execve(p_exec->args[0], p_exec->args, *p_exec->env);
}

int	prepare_cmd_path(char *path, char **cmd, int *index)
{
	char	*cur_exec;
	char	*tmp;

	*index = 0;
	while (path[*index] && path[*index] != ':')
		(*index)++;
	path[*index] = 0;
	tmp = custom_strjoin(path, "/", 0);
	if (!tmp)
		return (1);
	cur_exec = custom_strjoin(tmp, *cmd, 0);
	free(tmp);
	free(*cmd);
	if (!cur_exec)
		return (1);
	*cmd = cur_exec;
	return (0);
}

void	determine_cmd_path(t_p_exec *p_exec)
{
	t_cmd_path	cmd_path;

	initialize_cmd_path(&cmd_path, p_exec->path);
	cmd_path.save_cmd = ft_strdup(p_exec->args[0]);
	free_me_from_minishell(p_exec, 1, cmd_path.save_cmd, 0);
	cmd_path.path_len = ft_strlen(p_exec->path);
	while (cmd_path.index1 < cmd_path.path_len)
	{
		prepare_cmd_path(p_exec->path,
			&p_exec->args[0], &cmd_path.index1);
		free_me_from_minishell(p_exec, 1, p_exec->cmd, 0);
		if (p_exec->here_inf)
			close(p_exec->here_pipe_fd[1]);
		execve(p_exec->args[0], p_exec->args, *p_exec->env);
		free(p_exec->args[0]);
		cmd_path.index1++;
		cmd_path.index2 += cmd_path.index1;
		p_exec->path += cmd_path.index1;
		p_exec->args[0] = ft_strdup(cmd_path.save_cmd);
		free_me_from_minishell(p_exec, 1, p_exec->args[0], 0);
		if (cmd_path.index2 >= cmd_path.path_len)
			break ;
	}
	free(cmd_path.save_cmd);
}

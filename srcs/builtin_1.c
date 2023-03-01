/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:48:48 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/08 16:03:31 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	built_in(t_p_exec *pipe_exec)
{
	if (!ft_strcmp(pipe_exec->cmd, "exit"))
		return (1);
	if (!ft_strcmp(pipe_exec->cmd, "env"))
		return (1);
	if (!ft_strcmp(pipe_exec->cmd, "export"))
		return (1);
	if (!ft_strcmp(pipe_exec->cmd, "unset"))
		return (1);
	if (!ft_strcmp(pipe_exec->cmd, "pwd"))
		return (1);
	if (!ft_strcmp(pipe_exec->cmd, "echo"))
		return (1);
	if (!ft_strcmp(pipe_exec->cmd, "cd"))
		return (1);
	return (0);
}

int	*free_envi(int *envi, char **env)
{
	int	i;

	i = 0;
	if (*envi)
	{
		while (env[i])
			free(env[i++]);
		free(env);
	}
	(*envi)++;
	return (envi);
}

char	**inside_export_env(int i, char *same, char **new_env, char *str)
{
	if (same[0] != '\0')
		new_env[i] = '\0';
	if (same[0] == '\0')
	{
		new_env[i] = ft_strdup(str);
		new_env[i + 1] = '\0';
		free(same);
	}
	return (new_env);
}

char	**export_env(char *str, char **env, int *envi)
{
	int		i;
	char	**new_env;
	char	*same;

	i = 0;
	same = already_in_env(str, env);
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		ft_putstr_fd("MALLOC EXPORT\n", 2);
	i = 0;
	while (env[i])
	{
		if (ft_strcmpe(env[i], same))
			new_env[i] = ft_strdup(env[i]);
		if (!ft_strcmpe(env[i], same))
			new_env[i] = ft_strdup(str);
		i++;
	}
	new_env = inside_export_env(i, same, new_env, str);
	envi = free_envi(envi, env);
	return (new_env);
}

char	*check_extension(char *str, t_minishell *minishell)
{
	char	*same;
	char	*result;

	if (!ft_strncmp("?", str, 1))
	{
		free(str);
		return (ft_itoa(g_code));
	}
	if (!ft_strncmp("$", str, 1))
		return (str);
	same = already_in_env(str, *minishell->env);
	if (same[0] != '\0')
	{
		result = ft_substr(same, ft_strlen(str) + 1, ft_strlen(same));
		free(str);
		return (result);
	}
	free(str);
	free (same);
	return (ft_strdup(""));
}

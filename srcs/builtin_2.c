/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:59:26 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/08 16:03:53 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	test_export(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	export(t_token **token, t_p_exec *pipe_exec)
{
	if (!pipe_exec->args[1] && ((!*token)
			|| ((*token) && (*token)->type != 13)))
		sort_env(*(pipe_exec)->env);
	if ((*token) && (*token)->type == 13)
	{
		if (!test_export((*token)->str))
		{
			pipe_exec->exit_code = 1;
			ft_putstr_fd("export: not a valid identifier\n", 2);
			return (0);
		}
		while ((*token) && (*token)->type == 13)
		{
			*(pipe_exec)->env = export_env((*token)->str,
					*(pipe_exec)->env, pipe_exec->envi);
			*token = (*token)->next;
		}
		return (1);
	}
	return (1);
}

char	**inside_unset_env(char **new_env, int l, char *same)
{
	new_env[l] = '\0';
	if (same[0] == '\0')
		free(same);
	return (new_env);
}

char	**unset_env(char *str, char **env, int *envi)
{
	int		i;
	int		l;
	char	**new_env;
	char	*same;

	i = 0;
	l = 0;
	same = already_in_env(str, env);
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		ft_putstr_fd("MALLOC UNSET\n", 2);
	i = 0;
	while (env[++i])
	{
		if (ft_strcmpe(env[i], same))
			new_env[l] = ft_strdup(env[i]);
		if (!ft_strcmpe(env[i], same))
			l--;
		l++;
	}
	new_env = inside_unset_env(new_env, l, same);
	envi = free_envi(envi, env);
	return (new_env);
}

int	print_pwd(t_p_exec *p_exec)
{
	char	*pwd;
	char	*buf;
	int		i;

	buf = NULL;
	pwd = getcwd(buf, 0);
	if (errno != 2 && errno != 10)
		free_me_from_minishell(p_exec, 1, pwd, 0);
	if (errno == 0)
	{
		printf("%s\n", pwd);
		free(pwd);
		return (1);
	}
	if (errno == 2 || errno == 10)
	{
		i = 0;
		while (p_exec->env[0][i++])
			if (!ft_strncmp(p_exec->env[0][i], "PWD", 3))
				break ;
		printf("%s\n", p_exec->env[0][i] + 4);
	}
	return (1);
}

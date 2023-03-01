/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:11:21 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/08 16:33:41 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_echo(int *n, int *i, char **str)
{
	while (check_arg_echo(str[*i]))
	{
		(*n)++;
		(*i)++;
	}
	return (1);
}

void	echo(char **str)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (str[i])
	{
		count_echo(&n, &i, str);
		while (str[i])
		{
			if (!str[i + 1])
			{
				printf("%s", str[i]);
				break ;
			}
			printf("%s ", str[i]);
			i++;
		}
		if (!n)
			printf("\n");
	}
	else
		printf("\n");
}

char	**inside_sort_env(char **env, int j, int len_env, char **result)
{
	int	rank;
	int	i;

	rank = 0;
	i = 0;
	while (j < len_env)
	{
		while (env[i])
		{
			if (ft_strcmpe(env[j], env[i]) > 0)
				rank++;
			i++;
		}
		result[rank] = custom_strjoin("declare -x ", env[j], 0);
		rank = 0;
		i = 0;
		j++;
	}
	return (result);
}

void	sort_env(char **env)
{
	int		i;
	int		j;
	int		len_env;
	char	**result;

	i = 0;
	j = 0;
	len_env = 0;
	while (env[len_env])
		len_env++;
	result = malloc(sizeof(char **) * len_env + 1);
	if (!result)
		ft_putstr_fd("MALLOC SORT ENV\n", 2);
	result[len_env] = '\0';
	result = inside_sort_env(env, j, len_env, result);
	while (i < len_env)
	{
		printf("%s\n", result[i]);
		free(result[i]);
		i++;
	}
	free(result);
}

char	*already_in_env(char *str, char **env)
{
	int		i;
	int		j;
	int		k;
	char	*result;

	i = 0;
	j = 0;
	k = 0;
	while (str[k] && str[k] != '=')
		k++;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, k))
		{
			while (env[i][j] && env[i][j] != '=')
				j++;
			if (j == k)
				return (env[i]);
		}
		j = 0;
		i++;
	}
	result = ft_strdup("");
	return (result);
}

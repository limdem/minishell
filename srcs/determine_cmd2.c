/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_cmd2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgauvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:36:55 by dgauvin           #+#    #+#             */
/*   Updated: 2022/06/09 23:36:58 by dgauvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize_cmd_path(t_cmd_path	*cmd_path, char *path)
{
	cmd_path->index1 = 5;
	cmd_path->index2 = cmd_path->index1;
	path += 5;
}

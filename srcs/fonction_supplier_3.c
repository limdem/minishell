/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_supplier_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlanani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:51:52 by rlanani           #+#    #+#             */
/*   Updated: 2022/06/16 17:51:55 by rlanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*create_result(void)
{
	char	*result;

	result = malloc(sizeof(char) * 1);
	if (!result)
		ft_putstr_fd("MALLOC $\n", 2);
	result[0] = '\0';
	return (result);
}

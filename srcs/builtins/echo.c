/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:31:54 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/12 16:35:30 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *str, bool n, int fd_out)
{
	if (!str)
		return ;
	ft_dprintf(fd_out, "%s", str);
	if (!n)
		ft_dprintf(fd_out, "\n");
}

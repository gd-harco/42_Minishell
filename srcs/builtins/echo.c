/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:31:54 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/16 12:27:22 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief echo builtin
 *
 * @param str the string to print
 * @param n if true, don't print a newline
 * @param fd_out the file descriptor to print to. if 0, print to STDOUT
 */
void	echo(char **str, bool n, int fd_out)
{
	int	i;

	i = 0;
	if (fd_out == 0)
		fd_out = STDOUT_FILENO;
	while (str[i])
	{
		ft_dprintf(fd_out, "%s", str[i++]);
		if (str[i])
			ft_dprintf(fd_out, " ");
	}
	if (!n)
		ft_dprintf(fd_out, "\n");
}

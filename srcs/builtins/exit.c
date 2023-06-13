/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:07:05 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/24 15:32:15 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: determine what will be needed to free
void	exit_shell(int status, void **things_to_free)
{
	(void)things_to_free;
	rl_clear_history();
	ft_dprintf(STDOUT_FILENO,
		"La Team Rocket s'envole vers d'autres cieux!\n");
	ft_dprintf(STDERR_FILENO, "exit\n");
	exit(status);
}

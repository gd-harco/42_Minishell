/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sigaction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:43:33 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/03 19:43:35 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_malloc(t_sig *sig);

void	init_sigaction(t_sig *sig)
{
	sig->int_prompt = ft_calloc(1, sizeof(struct sigaction));
	sig->int_exec = ft_calloc(1, sizeof(struct sigaction));
	sig->quit_prompt = ft_calloc(1, sizeof(struct sigaction));
	sig->quit_exec = ft_calloc(1, sizeof(struct sigaction));
	check_malloc(sig);
}

static void	check_malloc(t_sig *sig)
{
	if (!sig->int_prompt || !sig->int_exec
    ||
		!sig->quit_prompt || !sig->quit_exec)
	{
		ft_dprintf(STDERR_FILENO, "minishell: malloc error in init_sigaction\n");
		if (sig->int_prompt)
			free(sig->int_prompt);
		if (sig->int_exec)
			free(sig->int_exec);
		if (sig->quit_prompt)
			free(sig->quit_prompt);
		if (sig->quit_exec)
			free(sig->quit_exec);
		exit(EXIT_FAILURE);
	}
}

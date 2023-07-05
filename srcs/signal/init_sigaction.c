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
static void	init_int_prompt(t_sig *sig);
static void	init_quit_prompt(t_sig *sig);

void	init_sigaction(t_sig *sig)
{
	sig->int_prompt = ft_calloc(1, sizeof(struct sigaction));
	sig->int_exec = ft_calloc(1, sizeof(struct sigaction));
	sig->quit_prompt = ft_calloc(1, sizeof(struct sigaction));
	sig->quit_exec = ft_calloc(1, sizeof(struct sigaction));
	check_malloc(sig);
	init_int_prompt(sig);
	init_quit_prompt(sig);
}

static void	init_int_prompt(t_sig *sig)
{
	sig->int_prompt->sa_handler = sigint_prompt;
	sig->int_prompt->sa_flags = SA_RESTART;
	sigemptyset(&sig->int_prompt->sa_mask);
}

static void	init_quit_prompt(t_sig *sig)
{
	sig->quit_prompt->sa_handler = SIG_IGN;
	sig->quit_prompt->sa_flags = SA_RESTART;
	sigemptyset(&sig->quit_prompt->sa_mask);
}

static void	check_malloc(t_sig *sig)
{
	if (!sig->int_prompt || !sig->int_exec
		|| !sig->quit_prompt || !sig->quit_exec)
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

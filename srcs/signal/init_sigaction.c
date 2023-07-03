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

static void	init_sig_int_prompt(struct sigaction *to_init);
static void	init_siq_int_exec(struct sigaction *to_init);
static void	init_sig_quit(struct sigaction *to_init);

void	init_sigaction(t_sig *sig)
{
	sig->int_prompt = malloc(sizeof(struct sigaction));
	sig->int_exec = malloc(sizeof(struct sigaction));
	sig->quit_prompt = malloc(sizeof(struct sigaction));
	sig->quit_exec = malloc(sizeof(struct sigaction));
	init_siq_int_exec(sig->int_exec);
	init_sig_int_prompt(sig->int_prompt);
	init_sig_quit_prompt(sig->quit_prompt);
	init_siq_quit_exec(sig->quit_exec);
}

//ctrl+\ dans le prompt
static void	init_sig_quit(struct sigaction *to_init)
{
	to_init->sa_handler = SIG_IGN;
	sigemptyset(&to_init->sa_mask);
	to_init->sa_flags = 0;
}

static void	init_siq_int_exec(struct sigaction *to_init)
{
	to_init->sa_handler = SIG_IGN;
	sigemptyset(&to_init->sa_mask);
	to_init->sa_flags = 0;
}

static void	init_sig_int_prompt(struct sigaction *to_init)
{
	to_init->sa_handler = sig_c_prompt;
	sigemptyset(&to_init->sa_mask);
	to_init->sa_flags = 0;
}

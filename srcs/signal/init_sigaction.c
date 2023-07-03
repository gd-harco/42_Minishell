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

static void	init_sigint_parent(struct sigaction *to_init);
static void	init_siqint_child(struct sigaction *to_init);
static void	init_sigquit_parent(struct sigaction *to_init);
static void	init_sigquit_child(struct sigaction *to_init);

void	init_sigaction(t_sig *sig)
{
	sig->int_prompt = malloc(sizeof(struct sigaction));
	sig->int_exec = malloc(sizeof(struct sigaction));
	sig->quit_prompt = malloc(sizeof(struct sigaction));
	sig->quit_exec = malloc(sizeof(struct sigaction));
	init_siqint_child(sig->int_exec);
	init_sigint_parent(sig->int_prompt);
	init_sigquit_parent(sig->quit_prompt);
	init_siqquit_child(sig->quit_exec);
}

//ctrl + c dans un process enfant kill le process
static void	init_siqint_child(struct sigaction *to_init)
{
	to_init->sa_handler = SIG_IGN;
	sigemptyset(&to_init->sa_mask);
	to_init->sa_flags = 0;
}

//ctrl + c dams un process parent affiche le prompt sur une nouvelle ligne
static void	init_siqint_parent(struct sigaction *to_init)
{
	to_init->sa_handler = SIG_IGN;
	sigemptyset(&to_init->sa_mask);
	to_init->sa_flags = 0;
}

//ctrl+\ dans le prompt ne fais rien
static void	init_sigquit_parent(struct sigaction *to_init)
{
	to_init->sa_handler = SIG_IGN;
	sigemptyset(&to_init->sa_mask);
	to_init->sa_flags = 0;
}


// ctrl + \ dans un ori
static void	init_sigint_parent(struct sigaction *to_init)
{
	to_init->sa_handler = sig_c_prompt;
	sigemptyset(&to_init->sa_mask);
	to_init->sa_flags = 0;
}

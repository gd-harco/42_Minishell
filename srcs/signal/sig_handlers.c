/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:43:36 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/03 19:43:38 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_c_prompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	printf("sig_c_prompt\n");
}

void	sig_c_exec(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	printf("sig_c_exec\n");
}

void	sig_d_int(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	printf("sig_d_int\n");
}

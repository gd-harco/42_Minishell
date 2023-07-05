/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:13:26 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/12 14:47:03 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_user_input(t_minishell *data)
{
	char		*user_input;
	static char	*prompt[11];
	static int	i = -1;

	sigaction(SIGINT, data->sig->int_prompt, data->sig->int_exec);
	sigaction(SIGQUIT, data->sig->quit_prompt, data->sig->quit_exec);
	if (!prompt[0])
	{
		prompt[0] = "Nous sommes de retour! > ";
		prompt[1] = "Pour vous jouer un mauvais tour! > ";
		prompt[2] = "Afin de préserver le monde de la dévastation! > ";
		prompt[3] = "Afin de rallier tous les peuples à notre nation! > ";
		prompt[4] = "Afin d'écraser l'amour et la vérité! > ";
		prompt[5] = "Afin d'étendre notre pouvoir"
			"jusqu'à la voie lactée! > ";
		prompt[6] = "Jessie! > ";
		prompt[7] = "James! > ";
		prompt[8] = "La Team Rocket plus rapide que la lumière! > ";
		prompt[9] = "Rendez-vous tous ou ce sera la guerre! > ";
		prompt[10] = "Miaouss, oui la guerre! > ";
	}
	if (i == 11)
		i = -1;
	i++;
	user_input = readline(prompt[i]);
	return (user_input);
}

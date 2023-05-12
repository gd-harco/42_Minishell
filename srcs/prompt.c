/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:13:26 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/12 14:07:44 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_user_input(void)
{
	char	*user_input;
	char	*prompt;

	prompt = ft_strdup("Nous sommes de retour! > ");
	user_input = readline(prompt);
	add_history(user_input);
	free(prompt);
	return (user_input);
}

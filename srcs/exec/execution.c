/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:56:35 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/17 18:40:22 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nb_cmd(const t_minishell *data);

void	master_exec(t_minishell *data)
{
	int	cmd_nb;

	cmd_nb = get_nb_cmd(data);
	ft_printf("cmd_nb = %d\n", cmd_nb);
}

static int	get_nb_cmd(const t_minishell *data)
{
	int		nb;
	t_token	*tmp;

	nb = 1;
	tmp = data->token_list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			nb++;
		tmp = tmp->next;
	}
	return (nb);
}

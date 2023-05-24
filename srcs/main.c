/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:09:31 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/24 12:05:14 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*data;
	t_var		*var;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_minishell));
	var = malloc(sizeof(t_var));
	data->envp = envp;
	var->envp = envp;
	printf(ROCKET_LOGO);
	var->str = get_user_input();
	while (42)
	{
		add_history(var->str);
		data->token_list = get_token(var);
		master_exec(data);
		free(data->token_list);
		var->str = get_user_input();
	}
	return (0);
}

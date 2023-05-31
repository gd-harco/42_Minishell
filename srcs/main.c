/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:09:31 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/31 11:23:14 by gd-harco         ###   ########lyon.fr   */
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
	if (!data)
		exit(EXIT_FAILURE);
	var = malloc(sizeof(t_var));
	if (!var)
		exit(EXIT_FAILURE);//TODO: Call exit function
	data->envp = envp;
	var->envp = envp;
	printf(ROCKET_LOGO);
	var->str = get_user_input();
	while (42)
	{
		if (var->str && *(var->str))
			add_history(var->str);
		data->token_list = get_token(var);
		master_exec(data);
		free(data->token_list);
		var->str = get_user_input();
	}
	return (0);
}

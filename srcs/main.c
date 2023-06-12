/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:09:31 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/03 13:10:00 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;
	t_var		var;

	(void)argc;
	(void)argv;
	malloc(10);
	data.envp = envp;
	var.env_cpy = envp;
	printf(ROCKET_LOGO);
	var.str_in = get_user_input();
	var.str = ft_space_str(&var);
	while (42)
	{
		if (!var.str_in)
		{
			free(var.str_in);
			free(var.str);
			rl_clear_history();
			ft_printf("exit\n");
			exit(EXIT_EOF);
		}
		if (var.str_in && *(var.str_in))
			add_history(var.str_in);
		data.token_list = get_token_list(&var);
		if (data.token_list)
			master_exec(&data);
		free(var.str_in);
		var.str_in = get_user_input();
		var.str = ft_space_str(&var);
	}
	return (0);
}

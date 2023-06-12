/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:09:31 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/12 16:15:57 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;
	t_var		var;

	(void)argc;
	(void)argv;
	// data = ft_calloc(1, sizeof(t_minishell));
	// if (!data)
	// 	exit(EXIT_FAILURE);
	// var = ft_calloc(1, sizeof(t_var));
	// if (!var)
	// 	exit(EXIT_FAILURE);//TODO: Call exit function
	data.envp = envp;
	var.envp = lst_env(envp);
	printf(ROCKET_LOGO);
	var.str_in = get_user_input();
	var.str = ft_space_str(&var);
	while (42)
	{
		if (!var.str_in)
		{
			free_data(&data);
			free_var(&var);
			ft_printf("exit\n");
			exit(EXIT_EOF);
		}
		if (var.str_in && *(var.str_in))
			add_history(var.str_in);
		data.token_list = get_token_list(&var);
		if (data.token_list)
			master_exec(&data);
		free(var.str);
		// free_var(&var);
		exit (0);
		var.str_in = get_user_input();
		var.str = ft_space_str(&var);
	}
	return (0);
}

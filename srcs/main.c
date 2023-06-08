/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:09:31 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/03 13:10:00 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*data;
	t_var		*var;

	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_minishell));
	if (!data)
		exit(EXIT_FAILURE);
	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		exit(EXIT_FAILURE);//TODO: Call exit function
	data->envp = envp;
	var->envp = envp;
	printf(ROCKET_LOGO);
	var->str = get_user_input();
	while (42)
	{
		if (!var->str)
		{
			free(var->str);
			free(data);
			free(var);
			ft_printf("exit\n");
			exit(EXIT_EOF);
		}
		if (var->str && *(var->str))
			add_history(var->str);
		data->token_list = get_token(var);
		if (data->token_list)
			master_exec(data);
		free(var->str);
		var->str = get_user_input();
	}
	return (0);
}

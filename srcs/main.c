/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:09:31 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/13 22:30:07 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO man stat = recuperer la valeur de retour
int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;
	t_var		var;

//TODO bien verifier que la commande envoye est bien un path et pas juste un binaire
	(void)argc;
	(void)argv;
	data.envp = (char **)ft_array_dup((void **)envp, false);
	var.env_cpy = data.envp;
	printf(ROCKET_LOGO);
	var.str_in = get_user_input();
	var.str = ft_space_str(&var);
	while (42)
	{
		if (!var.str_in)
		{
			free(var.str_in);
			free(var.str);
			free(var.env_cpy);
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
}

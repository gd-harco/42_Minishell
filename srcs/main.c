/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:09:31 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/17 12:21:06 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*data;
	char		*str;
	t_token		*tmp;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_minishell));
	data->envp = envp;
	printf("\033[0;31m");
	printf("Bienvenue dans le Minishell de la Team Rocket!\n\n");
	printf(ROCKET_LOGO);
	printf("\033[0m");
	str = get_user_input();
	while (42)
	{
		add_history(str);
		data->token_list = get_token(str, envp);
		tmp = data->token_list;
		while (tmp)
		{
			ft_printf("\n\nTOKEN\n");
			ft_printf("content[0] : %s\n", tmp->content[0]);
			ft_printf("content[1] : %s\n", tmp->content[1]);
			ft_printf("type : %i\n", tmp->type);
			ft_printf("next : %p\n", tmp->next);
			tmp = tmp->next;
		}
		str = get_user_input();
	}
	return (0);
}

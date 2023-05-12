/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:09:31 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/12 14:02:08 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	(void)argc;
	(void)argv;
	(void)envp;
	str = get_user_input();
	while (42)
	{
		printf("User input = \"%s\"\n", str);
		if (ft_strncmp(str, "quit", 4) == 0)
		{
			free(str);
			printf("La Team Rocket s'envole vers d'autres cieux!!!!\n");
			exit (0);
		}
		free(str);
		str = get_user_input();
	}
	return (0);
}

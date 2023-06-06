/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:33:44 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/05 16:50:01 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	struct_clear(t_var *var);

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*data;
	t_var		*var;
	t_token		*tmp;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_minishell));
	var = malloc(sizeof(t_var));
	data->envp = envp;
	var->envp = envp;
	printf("\033[0;31m");
	printf("Bienvenue dans le Minishell de la Team Rocket!\n\n");
	printf(ROCKET_LOGO);
	printf("\033[0m");
	var->str_in = get_user_input();
	var->str = ft_space_str(var);
	ft_printf("%s\n", var->str);
		add_history(var->str_in);
		free(var->str_in);
		data->token_list = get_token_list(var);
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
	token_clear(data->token_list);
	// free(var->s_p);
	free_var(var);
	free(var->str);
	free(data);
	free(var);
	return (0);
}

void	struct_clear(t_var *var)
{
	int	i;

	i = 0;
	free(var->s_p);
	free(var->arg);
	while (var->s[i])
	{
		free(var->spipe[i]);
		free(var->s[i]);
		i++;
	}
	free(var->s);
	free(var->spipe);
	free(var->path);
}

void	free_var(t_var *var)
{
	if (var->s)
		ft_free_array((void *)var->s);
	if (var->spipe)
		ft_free_array((void *)var->spipe);
	// if (var->envp)
	// 	ft_free_array((void *)var->envp);
	// if (var->path)
	// 	ft_free_array((void *)var->path);
	if (var->s_p)
		free(var->s_p);
	if (var->arg)
		free(var->arg);
	// if (var->env)
	// 	free(var->env);
	// if (var->new_tkn)
	// 	token_clear(&var->new_tkn, free);
}
// cat Makefile | rev | wc -l >> out

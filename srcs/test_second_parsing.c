/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:50:12 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/11 14:45:05 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_add_back(t_token	**token_list, t_token *new)
{
	t_token	*tmp;

	if (!token_list)
		return ;
	tmp = *token_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*new_node(char **content, enum e_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = content;
	new->type = type;
	new->next = NULL;
	return (new);
}

int	main(void)
{
	t_token	*token_list;
	char **cmd_1;
	char **cmd_2;
	char **cmd_3;

	cmd_1 = malloc(sizeof(char *) * 2);
	cmd_1[0] = "echo";
	cmd_1[1] = "test";
	cmd_2 = malloc(sizeof(char *) * 2);
	cmd_2[0] = ">";
	cmd_2[1] = NULL;
	cmd_3 = malloc(sizeof(char *) * 2);
	cmd_3[0] = "test.txt";
	cmd_3[1] = NULL;
	token_list = new_node(cmd_1, STRING);
	token_add_back(&token_list, new_node(cmd_2, CHEVRON_OUT));
	token_add_back(&token_list, new_node(cmd_3, STRING));
	second_parsing(token_list);
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:23:51 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/02 10:18:44 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_space_str(t_var *var)
{
	int		i;
	char	*new;
	char	to_join[2];

	var->str = ft_strdup(var->str_in);
	i = 0;
	to_join[1] = 0;
	new = NULL;
	while (var->str[i])
	{
		to_join[0] = var->str[i];
		if (var->str[i] == '|')
		{	
			new = ft_strjoin(new, " |");
			var->nb_pipe++;
		}
		else
			new = ft_strjoin(new, to_join);
		i++;
	}
	return (new);
}

bool	already_pipe(t_token t_new)
{
	if (token_last(&t_new)->type == PIPE)
		return (true);
	else
		return (false);
}

int	ft_nb_pipe(char *str)
{
	int	i;
	int	c;

	if (!str)
		return (0);
	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '|')
			c++;
		i++;
	}
	return (c);
}

// void	token_add_front(t_token **token, t_token *new)
// {
// 	if (new && token)
// 	{
// 		new->next = *token;
// 		*token = new;
// 	}
// }

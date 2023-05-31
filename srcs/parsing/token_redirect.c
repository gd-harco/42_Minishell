/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:06:00 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/31 10:27:49 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_redirect_in(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			return (true);
		i++;
	}
	return (false);
}

void	get_token_backup(t_var var, t_var *tmp);
char	**ft_str2dup(char **s1);

t_token	*get_recutoken(t_var *var)
{
	t_var	*tmp;

	tmp = malloc(sizeof(t_var));
	if (!tmp)
		exit(EXIT_FAILURE);//TODO: call function pointer exit
	var->recu = true;
	get_token_backup(*var, tmp);
	var->str = ft_split_redirect(var->s);
	var->new_tkn = get_token(var);
	if (tmp->spipe[1])
	{
		tmp->new_tkn = token_pipe();
		token_add_back(&var->new_tkn, tmp->new_tkn);
	}
	get_token_backup(*tmp, var);
	// var->i++;
	var->recu = false;
	return (var->new_tkn);
}

void	get_token_backup(t_var var, t_var *tmp)
{
	tmp->str = ft_strdup(var.str);
	tmp->spipe = ft_str2dup(var.spipe);
	tmp->s = ft_str2dup(var.s);
	tmp->i = var.i;
}

char	**ft_str2dup(char **s1)
{
	char	**s2;
	int		x;

	x = 0;
	while (s1[x] != NULL)
		x++;
	s2 = malloc(sizeof(char *) * x + 1);
	if (!s2 || !s1)
		return (NULL);
	x = 0;
	while (s1[x])
	{
		s2[x] = ft_strdup(s1[x]);
		x++;
	}
	s2[x] = NULL;
	return (s2);
}

char	*ft_split_redirect(char **str)
{
	int		i;
	int		j;
	char	*new;
	char	to_join[2];
	char	to_join1[2];

	to_join[1] = 0;
	to_join1[1] = 0;
	i = 0;
	j = 0;
	new = NULL;
	while (str[i])
	{
		while (str[i] && str[i][j] && str[i][j] != '|')
		{
			to_join[0] = str[i][j];
			to_join1[0] = str[i][j + 1];
			if ((str[i][j] == '<' && str[i][j + 1] != '<')
				|| (str[i][j] == '>' && str[i][j + 1] != '>')
				|| str[i][j] == ' ')
				new = ft_strjoinsp(new, to_join);
			else if ((str[i][j] == '<' && str[i][j + 1] == '<')
				|| (str[i][j] == '>' && str[i][j + 1] == '>'))
			{
				new = ft_strjoinsp(new, ft_strjoin(to_join, to_join1));
				j++;
			}
			else
				new = ft_strjoin(new, to_join);
			j++;
		}
		if (str[i] && str[i][j] == '|')
			break ;
		new = ft_strjoinsp(new, "");
		j = 0;
		i++;
	}
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:06:00 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/01 15:57:26 by tdutel           ###   ########.fr       */
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
	get_token_backup(*tmp, var);
	if (var->nb_pipe-- > 0) //tmp->spipe[tmp->index + 1])
	{
		tmp->new_tkn = token_pipe();
		token_add_back(&var->new_tkn, tmp->new_tkn);
		var->i--;
	}
	var->index++;	//	si | alors on passe au spipe[index++]
	var->recu = false;
	// var->tkn_past = malloc(sizeof(t_token));
	// var->tkn_past = var->new_tkn;
	return (var->new_tkn);
}

void	get_token_backup(t_var var, t_var *tmp)
{
	tmp->str = ft_strdup(var.str);
	tmp->spipe = ft_str2dup(var.spipe);
	tmp->s = ft_str2dup(var.s);
	tmp->nb_pipe = var.nb_pipe;
	tmp->i = var.i;
	tmp->index = var.index;
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


//<in>out cat makefile| cat<in2 || ls|

// TODO : enlever les arg de trop de la lst_tkn (cat <in>ot makefile 	sup makefile)

//gerer  dans infile : cat < in>out makefile
//	gerer quand n'ecrit pas tout : cat <in >out<in2 Makefile	n'ecrit pas le >out<in2
//ok

//	<in>out cat -e Makefile et
//	gerer cat <in0<in>out makefile	ecrit 2 fois la cmd

//		cat in>out makefile|cat<in>out > out		segfault
//mettre la condition dans infile outfile argument et autres...


//	<in>out >out cat|echo lo	

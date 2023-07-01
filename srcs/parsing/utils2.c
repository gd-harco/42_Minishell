/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:23:51 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/01 17:16:20 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	fill_str_quote(char *str, int *start, t_var_quote *v_q, t_var *var)
{
	if (str[*start] == '|')
	{
		v_q->tmp[v_q->j] = '`';
		var->is_pquote = true;
	}
	else if (str[*start] == ' ')
	{
		v_q->tmp[v_q->j] = '~';
		var->is_squote = true;
	}
	else
		v_q->tmp[v_q->j] = str[*start];
	v_q->j++;
	*start = *start + 1;
}

static char	*ft_quote_str(char *str, int *start, char c, t_var *var)
{
	t_var_quote	v_q;

	v_q.i = 1;
	v_q.j = 0;
	while (str[*start + v_q.i] != c && str[*start + v_q.i])
	{
		v_q.i++;
	}
	v_q.i++;
	v_q.tmp = malloc(sizeof(char) * (v_q.i + 3));
	if (!v_q.tmp)
		exit(EXIT_FAILURE); //TODO: call function pointer exit
	v_q.tmp[v_q.j++] = ';';
	while (v_q.j < v_q.i + 1)
	{
		fill_str_quote(str, start, &v_q, var);
	}
	*start = *start - 1;
	v_q.tmp[v_q.j] = ';';
	v_q.tmp[v_q.j + 1] = '\0';
	return (v_q.tmp);
}

static void	fill_str(t_var *var, t_var_quote *v_q, char **new)
{
	char	*tmp;

	v_q->t[0] = v_q->tmp[v_q->i];
	if (v_q->tmp[v_q->i] == '\'')
	{
		tmp = ft_quote_str(v_q->tmp, &v_q->i, '\'', var);
		*new = ft_strjoinsp(*new, tmp, 0);
		if (tmp)
			free(tmp);
	}
	else if (v_q->tmp[v_q->i] == '"')
	{
		tmp = ft_quote_str(v_q->tmp, &v_q->i, '"', var);
		*new = ft_strjoinsp(*new, tmp, 0);
		if (tmp)
			free(tmp);
	}
	else if (v_q->tmp[v_q->i] == '|')
	{
		*new = ft_strjoinsp(*new, " | ", 0);
		var->nb_pipe++;
	}
	else if (v_q->tmp[v_q->i] == '<' && v_q->i > 0 && v_q->tmp[v_q->i - 1] != '<')
		*new = ft_strjoinsp(*new, " <", 0);
	else if (v_q->tmp[v_q->i] == '>' && v_q->tmp[v_q->i - 1] != '>')
		*new = ft_strjoinsp(*new, " >", 0);
	else
		*new = ft_strjoinsp(*new, v_q->t, 0);
}

char	*ft_space_str(t_var *var)
{
	t_var_quote	v_q;
	char		*new;

	if (check_syntax_error(var, 0) == true)
		return (NULL);
	var->is_pquote = false;
	var->is_squote = false;
	v_q.tmp = ft_strdup(var->str_in);
	if (!v_q.tmp)
		return (NULL);
	v_q.i = 0;
	v_q.t[1] = 0;
	new = NULL;
	while (v_q.tmp && v_q.tmp[v_q.i])
	{
		fill_str(var, &v_q, &new);
		v_q.i++;
	}
	free(v_q.tmp);
	return (new);
}

/*bool	already_pipe(t_token t_new)		//plus besoin
{
	if (token_last(&t_new)->type == PIPE)
		return (true);
	else
		return (false);
}*/

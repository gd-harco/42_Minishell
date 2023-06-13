/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:39:54 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/12 10:16:44 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_quote(t_var_quote *v_q)
{
	if (v_q->tmp)
		free(v_q->tmp);
	if (v_q->split_tmp)
		ft_free_split(v_q->split_tmp);
}

char	*ft_reload_dup(char *str, t_var *var)
{
	t_var_quote	v_q;

	v_q.i = 0;
	v_q.tmp = NULL;
	v_q.t[1] = '\0';
	while (str[v_q.i])
	{
		if (str[v_q.i] == '`' && var->is_pquote == true)
		{
			v_q.t[0] = '|';
			var->is_pquote = false;
		}
		else if (str[v_q.i] == '~' && var->is_squote == true)
		{
			v_q.t[0] = ' ';
			var->is_squote = false;
		}
		if (str[v_q.i] == '"')
			v_q.t[0] = '\0';
		else
			v_q.t[0] = str[v_q.i];
		v_q.tmp = ft_strjoinsp(v_q.tmp, v_q.t, 0);
		v_q.i++;
	}
	return (v_q.tmp);
}

static size_t	get_length(char const *s, unsigned int start, size_t len)
{
	size_t	x;
	size_t	y;

	if (start > ft_strlen(s))
		return (0);
	x = start;
	y = 0;
	if (len == 0)
		return (0);
	if (len == start)
		return (len);
	while (s[x] && x < (len + start))
	{
		x++;
		y++;
	}
	return (y);
}

char	*ft_substrvar(char const *s, unsigned int start, size_t len, t_var var)
{
	char	*result;
	size_t	result_length;
	size_t	x;

	if (s == NULL)
		return (NULL);
	result_length = get_length(s, start, len);
	result = malloc(sizeof(char) * (result_length + 1));
	if (result == NULL)
		return (NULL);
	x = 0;
	while (x < result_length)
	{
		if (s[start] == '`' && var.is_pquote == true)
			result[x] = '|';
		else if (s[start] == '~' && var.is_squote == true)
			result[x] = ' ';
		else
			result[x] = s[start];
		x++;
		start++;
	}
	result[x] = '\0';
	return (result);
}

// char	**ft_str2dup(char **s1)
// {
// 	char	**s2;
// 	int		x;

// 	x = 0;
// 	while (s1[x] != NULL)
// 		x++;
// 	s2 = malloc(sizeof(char *) * (x + 1));
// 	if (!s2)
// 		exit(EXIT_FAILURE); //TODO: call function pointer exit
// 	if (!s1)
// 		return (NULL);
// 	x = 0;
// 	while (s1[x])
// 	{
// 		s2[x] = ft_strdup(s1[x]);
// 		x++;
// 	}
// 	s2[x] = NULL;
// 	return (s2);
// }
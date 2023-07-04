/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:58:50 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/04 11:48:23 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//############################   JOIN_FCT   #################################//

static char	*joningsp(char *result, char *s2, char *s1)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (s1[x])
	{
		result[x] = s1[x];
		x++;
	}
	result[x] = ' ';
	x++;
	while (s2[y])
	{
		result[x] = s2[y];
		x++;
		y++;
	}
	result[x] = '\0';
	return (result);
}

static char	*joning(char *result, char *s2, char *s1)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (s1[x])
	{
		result[x] = s1[x];
		x++;
	}
	while (s2[y])
	{
		result[x] = s2[y];
		x++;
		y++;
	}
	result[x] = '\0';
	return (result);
}

/*
ft_strjoinsp fonction comme un strjoin normal mais le int n permet de
savoir si on espace les 2 str d'un space durant le join : 0 non, 1 oui.
*/

char	*ft_strjoinsp(char *s1, char *s2, int n)
{
	size_t		joined_size;
	char		*result;

	joined_size = (ft_strlen (s1) + ft_strlen (s2));
	if (!s2 && !s1)
		return (NULL);
	if (!s2 && s1)
		return ((ft_strdup(s1)));
	if (!s1 && s2)
		return ((ft_strdup(s2)));
	// result = ft_calloc(joined_size + 1 +n, sizeof(char));
	result = malloc(sizeof(char) * joined_size + 1 + n);
	if (!result)
	{
		ft_free_secure(&s1);
		exit(EXIT_FAILURE); //TODO: call function pointer exit
	}
	if (n == 1)
	{
		joningsp(result, (char *)s2, (char *)s1);
		ft_free_secure(&s1);
		return (result);
	}
	// else if (n == -1)
	// 	return (joningsp(result, (char *)s2, (char *)s1));
	joning(result, (char *)s2, (char *)s1);
	ft_free_secure(&s1);
	return (result);
}

/*
//############################   TRUNC_FCT   #################################//
*/

static char	*fill_dup(char *str, int start, t_var var, int k)
{
	char	*tmp;
	int		j;

	tmp = malloc(sizeof(char) * (k + 1));
	if (!tmp)
		exit(EXIT_FAILURE); //TODO: call function pointer exit
	j = 0;
	while (j < k)
	{
		if (str[start + j] == '`' && var.is_pquote == true)
			tmp[j] = '|';
		else if (str[start + j] == '~' && var.is_squote == true)
			tmp[j] = ' ';
		else
			tmp[j] = str[start + j];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*ft_trunc(char *str, int start, char *c, t_var var)
{
	t_var_quote	v_q;

	v_q.i = start;
	v_q.j = 0;
	v_q.k = 0;
	while (c[v_q.k])
	{
		if (!str || str[v_q.i] == c[v_q.k])
			return (ft_calloc(1, 1));
		v_q.k++;
	}
	v_q.k = 0;
	while (str[v_q.i] && str[v_q.i] != c[v_q.j])
	{
		while (c[v_q.j] && str[v_q.i] != c[v_q.j])
			v_q.j++;
		if (c[v_q.j])
			break ;
		v_q.i++;
		v_q.k++;
		v_q.j = 0;
	}
	v_q.tmp = fill_dup(str, start, var, v_q.k);
	return (v_q.tmp);
}


char	*ft_trunc_start(char *str, char *c, t_var var)
{
	t_var_quote	v_q;

	v_q.i = 0;
	v_q.j = 0;

	while (str[v_q.i])
	{
		while (c[v_q.j])
		{
			if (str[v_q.i] == c[v_q.j])
				break ;
			v_q.j++;
		}
		if (str[v_q.i] != c[v_q.j])
			break ;
		v_q.i++;
		v_q.j = 0;
	}
	// v_q.tmp = ft_substrvar(str, v_q.i, ft_strlen(str - v_q.i), var);
	return (ft_substrvar(str, v_q.i, ft_strlen(str) - v_q.i, var));
}
// char	*ft_trunc_char(char *str, int start, char c, t_var var)
// {
// 	char	*s;
// 	int		i;
// 	int		j;
// 	int		k;

// 	i = start;
// 	j = 0;
// 	k = 0;
// 	if (!str || str[i] == c)
// 		return ("");
// 	while (str[i] && str[i] != c)
// 	{
// 		i++;
// 		k++;
// 	}
// 	s = fill_dup(str, start, var, k);
// 	return (s);
// }

// char	*ft_trunc_var(t_var var, t_varenv v_e, int start, char *c)
// {
// 	char	*s;
// 	int		i;
// 	int		j;
// 	int		k;

// 	i = start;
// 	j = 0;
// 	k = 0;
// 	while (c[k])
// 	{
// 		if (!var.s[v_e.j] || var.s[v_e.j][i] == c[k])
// 			return ("");
// 		k++;
// 	}
// 	k = 0;
// 	while (var.s[v_e.j][i] && var.s[v_e.j][i] != c[j])
// 	{
// 		while (c[j] && var.s[v_e.j][i] != c[j])
// 			j++;
// 		if (c[j])
// 			break ;
// 		i++;
// 		k++;
// 		j = 0;
// 	}
// 	s = fill_dup(var.s[v_e.j], start, var, k);
// 	return (s);
// }

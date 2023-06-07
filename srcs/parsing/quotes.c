/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:25:29 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/07 13:25:07 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// bool	is_env_in_str(char *str, int nb)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && nb == 0)
// 			return (true);
// 		else if (str[i] == '$' && nb > 0)
// 			nb--;
// 		i++;
// 	}
// 	return (false);
// }

char	*ft_reload_dup(char *str, t_var *var)
{
	char	*tmp;
	char	t[2];
	int		i;

	i = 0;
	tmp = NULL;
	t[1] = '\0';
	while (str[i])
	{
		if (str[i] == '`' && var->is_pquote == true)
		{
			t[0] = '|';
			var->is_pquote = false;
		}
		else if (str[i] == '*' && var->is_squote == true)
		{
			t[0] = ' ';
			var->is_squote = false;
		}
		else
			t[0] = str[i];
		tmp = ft_freestrjoin(tmp, t);
		i++;
	}
	return (tmp);
}

void	dub_quote(t_var *var, t_varenv *v_e, char **tmp, int *i)
{
	char	t[2];

	t[1] = '\0';
	++*i;
	var->env = NULL;
	if (is_env_in(*var, v_e->j) == true)
	{
		*tmp = ft_strjoinsp(*tmp, ft_truncstr(*var, *v_e, 1, "$"));
		env_arg(var, v_e);
		var->env = ft_reload_dup(var->env, var);
		*tmp = ft_freestrjoin(*tmp, var->env);
		while (var->s[v_e->j][*i] != '"' && var->s[v_e->j][*i])
			++*i;
	}
	else
	{
		while (var->s[v_e->j][*i] != '"' && var->s[v_e->j][*i])
		{
			if (var->s[v_e->j][*i] == '`' && var->is_pquote == true)
				t[0] = '|';
			else if (var->s[v_e->j][*i] == '*' && var->is_squote == true)
				t[0] = ' ';
			else
				t[0] = var->s[v_e->j][*i];
			*tmp = ft_freestrjoin(*tmp, t);
			++*i;
		}
	}
}


void	single_quote(t_var *var, t_varenv *v_e, char **tmp, int *i)
{
	char	t[2];

	t[1] = '\0';
	++*i;
	while (var->s[v_e->j][*i] != '\'' && var->s[v_e->j][*i])
	{
		if (var->s[v_e->j][*i] == '`' && var->is_pquote == true)
			t[0] = '|';
		else if (var->s[v_e->j][*i] == '*' && var->is_squote == true)
			t[0] = ' ';
		else
			t[0] = var->s[v_e->j][*i];
		*tmp = ft_freestrjoin(*tmp, t);
		++*i;
	}
}

void	quote_manager(t_var *var, t_varenv *v_e)
{
	char	*tmp;
	int		i;
	char	t[2];

	t[1] = '\0';
	tmp = NULL;
	var->quote = NULL;
	// var->quote = ft_reload_dup(var);
	i = 0;
	while (var->s[v_e->j][i] != '\'' && var->s[v_e->j][i] != '"')
		i++;
	while (var->s[v_e->j][i])
	{
		if (var->s[v_e->j][i] == '"')
		{
			dub_quote(var, v_e, &tmp, &i);
		}
		else if (var->s[v_e->j][i] == '\'')
		{
			single_quote(var, v_e, &tmp, &i);
		}
		else
		{
			if (var->s[v_e->j][i] == '`' && var->is_pquote == true)
				t[0] = '|';
			else if (var->s[v_e->j][i] == '*' && var->is_squote == true)
				t[0] = ' ';
			else
				t[0] = var->s[v_e->j][i];
			tmp = ft_freestrjoin(tmp, t);
		}
		i++;
	}
	var->quote = ft_strdup(tmp);
	free(tmp);
}

char	*ft_truncstr(t_var var, t_varenv v_e, int start, char *c)
{
	char	*s;
	int		i;
	int		j;
	int		k;

	i = start;
	j = 0;
	k = 0;
	while (c[k])
	{
		if (!var.s[v_e.j] || var.s[v_e.j][i] == c[k])
			return ("");
		k++;
	}
	k = 0;
	while (var.s[v_e.j][i] && var.s[v_e.j][i] != c[j])
	{
		while (c[j] && var.s[v_e.j][i] != c[j])
			j++;
		if (c[j])
			break ;
		i++;
		k++;
		j = 0;
	}
	s = malloc(sizeof(char) * (k + 1));
	j = 0;
	while (j < k)
	{
		if (var.s[v_e.j][start + j] == '`' && var.is_pquote == true)
			s[j] = '|';
		else if (var.s[v_e.j][start + j] == '*' && var.is_squote == true)
			s[j] = ' ';
		else
			s[j] = var.s[v_e.j][start + j];
		j++;
	}
	s[j] = '\0';
	return (s);
}

	// tmp = malloc(sizeof(char) * (j));	//j et non j + 1 car j - 1 + 1



/*

echo "$(echo "upg")"	=	echo $(echo "upg")
		upg

echo '$(echo"upg")'
	$(echo"upg")

*/

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

char	*ft_substrv(char const *s, unsigned int start, size_t len, t_var var)
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
		else if (s[start] == '*' && var.is_squote == true)
			result[x] = ' ';
		else
			result[x] = s[start];
		x++;
		start++;
	}
	result[x] = '\0';
	return (result);
}

//		cat "$$" doit etre pareil que cat $$

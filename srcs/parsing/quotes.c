/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:25:29 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/07 11:15:20 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_env_in_str(char *str, int nb)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && nb == 0)
			return (true);
		else if (str[i] == '$' && nb > 0)
			nb--;
		i++;
	}
	return (false);
}

void	dub_quote(t_var *var, t_varenv *v_e, char **tmp, int *j)
{
	int		nb;
	char	t[2];

	t[1] = '\0';
	nb = 0;
	++*j;
	while (var->quote[*j] != '"' && var->quote[*j])
	{
		if (is_env_in_str(var->quote, nb) == true)
		{
			nb++;
			*tmp = ft_strjoinsp(*tmp, ft_truncstr(*var, *v_e, 1, "$"));
			env_arg(var, v_e);
			*tmp = ft_freestrjoin(*tmp, var->env);
			break ;
		}
		else
		{
			if (var->s[var->i + 1][*j] == '`' && var->is_pquote == true)
				t[0] = '|';
			else if (var->s[var->i + 1][*j] == '*' && var->is_squote == true)
				t[0] = ' ';
			else
				t[0] = var->s[var->i + 1][*j];
			*tmp = ft_freestrjoin(*tmp, t);
			++*j;
		}
	}
	++*j;
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

char	*ft_reload_dup(t_var *var)
{
	char	*tmp;
	char	t[2];
	int		i;

	i = 0;
	tmp = NULL;
	t[1] = '\0';
	while (var->s[var->i + 1][i])
	{
		if (var->s[var->i + 1][i] == '`' && var->is_pquote == true)
			t[0] = '|';
		else if (var->s[var->i + 1][i] == '*' && var->is_squote == true)
			t[0] = ' ';
		else
			t[0] = var->s[var->i + 1][i];
		tmp = ft_freestrjoin(tmp, t);
		i++;
	}
	return (tmp);
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
	var->env = NULL;
	i = 0;
	while (var->s[v_e->j][i] != '\'' && var->s[v_e->j][i] != '"')
		i++;
	while (var->s[v_e->j][i])
	{
		if (var->s[v_e->j][i] == '"')
		{
			dub_quote(var, v_e, &tmp, &i);
			var->i++;
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

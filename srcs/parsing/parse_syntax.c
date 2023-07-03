/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:18:35 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/03 15:17:59 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	check_parse(t_var var);
static bool	check_parse_bis(t_var var, int i);;
static bool	in_out_in(t_var var, int i);
static char	last_char(char *str);
static bool	pipe_parse(char *str);

static bool	pipe_check(char *str)
{
	int	i;

	if (str[0] == '|' && str[1] != '|')
		return (ft_putendl_fd(PIPE_SYNTAX_ERR, STDERR_FILENO), true);
	else if (str[0] == '|' && str[1] == '|')
		return (ft_putendl_fd(PIPE2_SYNTAX_ERR, STDERR_FILENO), true);
	i = 0;
	while (str[i])
	{
		if ((str[i] == '|' && str[i + 1] == '|' && str[i + 2] != '|' && is_quote_between(str, i) == 0)
			|| (str[i] == '|' && str[i + 1] == '\0'))
			return (ft_putendl_fd(PIPE_SYNTAX_ERR, STDERR_FILENO), true);
		if (str[i] == '|' && str[i + 1] == '|' && str[i + 2] == '|' && is_quote_between(str, i) == 0)
			return (ft_putendl_fd(PIPE2_SYNTAX_ERR, STDERR_FILENO), true);
		i++;
	}
	if (pipe_parse(str) == true)
		return (true);
	return (false);
}

static bool	is_pipe_in(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (true);
		i++;
	}
	return (false);
}

static bool	pipe_parse(char *str)
{
	int		i;
	char	**s;

	i = 0;
	s = ft_split(str, ' ');
	while (s[i] && is_pipe_in(s[i]) == false)
		i++;
	if (!s[i] || !s[i + 1])
		return (ft_free_split(s), false);
	if (last_char(s[i]) == '|')
	{
		if (s[i + 1][0] == '|' && s[i + 1][1] != '|')
		{
			ft_putendl_fd(PIPE_SYNTAX_ERR, STDERR_FILENO);
			return (ft_free_split(s), true);
		}
		else if (s[i + 1][0] == '|' && s[i + 1][1] == '|')
		{
			ft_putendl_fd(PIPE2_SYNTAX_ERR, STDERR_FILENO);
			return (ft_free_split(s), true);
		}
	}
	ft_free_split(s);
	return (false);
}

bool	check_syntax_error(t_var *var, int i)
{
	if (!var->str_in)
		return (false);
	if (pipe_check(var->str_in) == true)
		return (true);
	while(var->str_in[i] && is_quote_between(var->str_in, i) == 0)
	{

		if ((var->str_in[i] == '<'
				&& ((var->str_in[i + 1] == '\0')
					|| (var->str_in[i + 1] == '<' && var->str_in[i + 2] == '\0')
					|| (var->str_in[i + 1] == '>' && var->str_in[i + 2] == '\0')
					|| (var->str_in[i + 1] == '<' && var->str_in[i + 2] == '<'
						&& var->str_in[i + 3] == '\0')
				))
			|| (var->str_in[i] == '>'
				&& ((var->str_in[i + 1] == '\0')
					|| (var->str_in[i + 1] == '>' && var->str_in[i + 2] == '\0')
				)))
		{
			ft_putendl_fd(NL_SYNTAX_ERR, STDERR_FILENO);
			return (true);
		}
		else if ((var->str_in[i] == '>'
				&& (var->str_in[i + 1] == '<' && var->str_in[i + 2] == '\0'))
			|| (var->str_in[i] == '<' && var->str_in[i + 1] == '<'
				&& var->str_in[i + 2] == '<' && var->str_in[i + 3] == '<'
				&& (var->str_in[i + 4] == '\0')))
		{
			ft_putendl_fd(IN_SYNTAX_ERR, STDERR_FILENO);
			return (true);
		}
		else if ((var->str_in[i] == '>' && var->str_in[i + 1] == '>'
				&& var->str_in[i + 2] == '<' && var->str_in[i + 3] == '<')
			|| (var->str_in[i] == '<' && var->str_in[i + 1] == '<'
				&& var->str_in[i + 2] == '<' && var->str_in[i + 3] == '<'
				&& var->str_in[i + 4] == '<' && var->str_in[i + 5] != '<'))
		{
			ft_putendl_fd(IN2_SYNTAX_ERR, STDERR_FILENO);
			return (true);
		}
		else if (var->str_in[i] == '<' && var->str_in[i + 1] == '<'
			&& var->str_in[i + 2] == '<' && var->str_in[i + 3] == '<'
			&& var->str_in[i + 4] == '<' && var->str_in[i + 5] == '<')
		{
			ft_putendl_fd(IN3_SYNTAX_ERR, STDERR_FILENO);
			return (true);
		}
		else if ((var->str_in[i] == '<' && var->str_in[i + 1] == '<')
			&& (var->str_in[i + 2] == '>' && (var->str_in[i + 3] == '\0')))
		{
			ft_putendl_fd(OUT_SYNTAX_ERR, STDERR_FILENO);
			return (true);
		}
		else if (((var->str_in[i] == '>' && var->str_in[i + 1] == '>')
				&& (var->str_in[i + 2] == '>' && (var->str_in[i + 3] == '>')))
			|| ((var->str_in[i] == '<' && var->str_in[i + 1] == '<')
				&& (var->str_in[i + 2] == '>' && var->str_in[i + 3] == '>')))
		{
			ft_putendl_fd(OUT2_SYNTAX_ERR, STDERR_FILENO);
			return (true);
		}
		else if ((var->str_in[i] == '>' && var->str_in[i + 1] == '<')
			&& (var->str_in[i + 2] == '>'))
		{
			ft_putendl_fd(IO_SYNTAX_ERR, STDERR_FILENO);
			return (true);
		}
		if (check_parse(*var) == true)
			return (true);
		i++;
	}
	return (false);
}

static bool	check_parse(t_var var)
{
	int		i;

	i = 0;
	var.s = ft_split(var.str_in, ' ');
	while (var.s[i] && in_out_in(var, i) == false)
		i++;
	if (!var.s[i] || !var.s[i + 1])
		return (ft_free_split(var.s), false);
	if (last_char(var.s[i]) == '<' || last_char(var.s[i]) == '>')
	{
		if (var.s[i + 1][0] == '>' && var.s[i + 1][1] != '>')
		{
			ft_putendl_fd(OUT_SYNTAX_ERR, STDERR_FILENO);
			return (ft_free_split(var.s), true);
		}
		else if (var.s[i + 1][0] == '>' && var.s[i + 1][1] == '>')
		{
			ft_putendl_fd(OUT2_SYNTAX_ERR, STDERR_FILENO);
			return (ft_free_split(var.s), true);
		}
		if (check_parse_bis(var, i) == true)
			return (true);
	}
	ft_free_split(var.s);
	return (false);
}

static bool	check_parse_bis(t_var var, int i)
{
	if (var.s[i + 1][0] == '<' && var.s[i + 1][1] == '<'
		&& var.s[i + 1][2] == '<')
	{
		ft_putendl_fd(IN3_SYNTAX_ERR, STDERR_FILENO);
		return (ft_free_split(var.s), true);
	}
	else if (var.s[i + 1][0] == '<' && var.s[i + 1][1] == '<')
	{
		ft_putendl_fd(IN2_SYNTAX_ERR, STDERR_FILENO);
		return (ft_free_split(var.s), true);
	}
	else if (var.s[i + 1][0] == '<' && var.s[i + 1][1] == '>')
	{
		ft_putendl_fd(IO_SYNTAX_ERR, STDERR_FILENO);
		return (ft_free_split(var.s), true);
	}
	else if (var.s[i + 1][0] == '<')
	{
		ft_putendl_fd(IN_SYNTAX_ERR, STDERR_FILENO);
		return (ft_free_split(var.s), true);
	}
	return (false);
}

static bool	in_out_in(t_var var, int i)
{
	int	j;

	j = 0;
	while (var.s[i][j])
	{
		if (var.s[i][j] == '<' || var.s[i][j] == '>')
			return (true);
		j++;
	}
	return (false);
}

static char	last_char(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1])
		i++;
	return (str[i]);
	// if (str[i] == '<' || str[i] == '>')
	// 	return (true);
	// return (false);
}

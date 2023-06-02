/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:40:27 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/02 16:46:13 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	init_start(t_var *var)
// {
// 	// int		a;
// 	// t_token	*tmp;
// 	// t_token	*tmp2;

// 	// a = 0;
// 	// tmp = malloc(sizeof(t_token));
// 	var->todo = NULL;
// 	var->nb_pipe = ft_nb_pipe(var->str);
// 	var->index = 0;
// 	if (var->recu == false)
// 		var->i = 0;
// }


// t_token	*get_token(t_var *var)
// {
// 	t_token	*t_new;
// 	t_token	*tmp;

// 	// if (!var->str)
// 	// 	return (NULL);
// 	init_start(var);
// 	tmp = NULL;
// 	t_new = token_init(var);
// 	// if (tmp && tmp->next)
// 		// token_add_front(&t_new, tmp);
// 	var->i++;
// 	while ((var->index == 0 || var->spipe[var->index - 1])
// 		&& var->spipe[var->index])
// 	{
// 		var_init(var);
// 		while ((var->s && var->s[var->i]) || var->btodo == true)
// 		{
// 				tmp = token_init(var);
// 				var->i++;
// 			if (tmp != NULL && already_cmd(t_new, tmp) != true) //&& already_cmd(var->tkn_past, tmp) != true)
// 				token_add_back(&t_new, tmp);
// 		}
// 		if (var->nb_pipe-- > 0) //&& var->spipe[var->index + 1] != NULL)
// 		{
// 			tmp = token_pipe();
// 			token_add_back(&t_new, tmp);
// 		}
// 		var_init(var);
// 		var->index++;
// 		var->i = 0;
// 	}
// 	// if (tmp && var->recu == false)
// 	// 	token_clear(&tmp, free);
// 	return (t_new);
// }

// t_token	*token_init(t_var *var)
// {
// 	if (var_init(var) == false || (!var->s[var->i] && var->btodo == false)
// 		|| (var->btodo == false && var->i != 0 && var->s[var->i][0] == '-'))
// 		return (NULL);
// 	var->todo = NULL;
// 	if (var->s && is_redirect_in(var->s[var->i]) == true && var->recu == false)
// 		return (get_recutoken(var));
// 	var->is_quote = false;
// 	if (var->s && var->s[var->i] && var->s[var->i][0] == '<')
// 	{
// 		if (token_infile(var) == -1)
// 			return (NULL);
// 	}
// 	else if (var->s && var->s[var->i] && var->s[var->i][0] == '>')
// 		token_outfile(var);
// 	else if (var->s && var->s[var->i])
// 	{
// 		// if (is_quote(var) != 0)
// 		// 	dub_quote(var);
// 		// else if (is_quote(var->s[var->i]) == 1)
// 		// 	single_quote(var);
// 		// else
// 		// {
// 		if (is_builtin(var->s[var->i]) == true)
// 			token_builtin(var);
// 		else
// 			token_cmd(var);
// 		token_arg(var);
// 	}
// 	var->new_tkn->next = NULL;
// 	return (var->new_tkn);
// }


// gerer var env et '' ""

/*
echo "$(echo "upg")"		echo $(echo "upg")
	upg
echo '$(echo"upg")'
	$(echo"upg")
*/

//gerer les space de '<' et '>' ex: <<in>>out	heredoc et out append

//ok	:

//	gerer si | avant cmd "| || cat -e"	ok
// gerer les string (ex : echo hello)
//differencier un infile d'un argument de cmd
//	(ex: echo bonjour : echo, bonjour mais aussi bonjour, null	a enlever)
//gerer plusieurs infile	ok
// refaire strjoin pour add space	ok
//gerer les spaces de '|' ex : echo bonjour|rev	doit faire ruojnob	ok


// ____________________________________________________________________________________________________________________________
// ____________________________________________________________________________________________________________________________


void	init_start(t_var *var)
{
	var->index = 0;
	var->nb_pipe = ft_nb_pipe(var->str);
	var->i = 0;
}

t_token	*get_token(t_var *var)
{
	t_token	*t_new;
	t_token	*tmp;

	// if (!var->str)
	// 	return (NULL);
	init_start(var);
	tmp = NULL;
	t_new = token_init(var);
	// if (tmp && tmp->next)
		// token_add_front(&t_new, tmp);
	var->i++;
	while ((var->index == 0 || var->spipe[var->index - 1])
		&& var->spipe[var->index])
	{
		var_init(var);
		while ((var->s && var->s[var->i]))
		{
				tmp = token_init(var);
				var->i++;
			if (tmp != NULL && already_cmd(t_new, tmp) != true) //&& already_cmd(var->tkn_past, tmp) != true)
				token_add_back(&t_new, tmp);
		}
		if (var->nb_pipe-- > 0) //&& var->spipe[var->index + 1] != NULL)
		{
			tmp = token_pipe();
			token_add_back(&t_new, tmp);
		}
		var_init(var);
		var->index++;
		var->i = 0;
	}
	// 	token_clear(&tmp, free);
	return (t_new);
}

t_token	*token_init(t_var *var)
{
	if (var_init(var) == false)	// || (var->i != 0 && var->s[var->i][0] == '-') var->i != 0 prmet de gerer le cas ou | -e | comme une cmd
		return (NULL);
	if (var->s && var->s[var->i] && var->s[var->i][0] == '<')
	{
		token_infile(var);
	}
	else if (var->s && var->s[var->i] && var->s[var->i][0] == '>')
		token_outfile(var);
	else if (var->s && var->s[var->i])
	{
		// if (is_quote(var) != 0)
		// 	dub_quote(var);
		// else if (is_quote(var->s[var->i]) == 1)
		// 	single_quote(var);
		// else
		// {
		if (is_builtin(var->s[var->i]) == true)
			token_builtin(var);
		else
			token_cmd(var);
		token_arg(var);
	}
	var->new_tkn->next = NULL;
	return (var->new_tkn);
}

// GERER LE CAS OU -e AVANT COMMANDE MAIS PAS EN POSITION 0		ok en remove "|| (var->i != 0 && var->s[var->i][0] == '-')"

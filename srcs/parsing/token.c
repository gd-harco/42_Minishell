/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:40:27 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/28 15:32:32 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		get_token(t_token *t_new, t_token *tmp, t_var *var);
static t_token	*token_init(t_var *var);

static void	init_start(t_var *var)
{
	var->index = 0;
	var->nb_pipe = ft_nb_pipe(var->str);
	var->i = 0;
}

t_token	*get_token_list(t_var *var)
{
	t_token	*t_new;
	t_token	*tmp;

	if (!var->str)
		return (NULL);
	init_start(var);
	tmp = NULL;
	t_new = token_init(var);
	var->i++;
	while ((var->index == 0 || var->spipe[var->index - 1])
		&& var->spipe[var->index])
	{
		ft_free_split_secure(var->s);
		ft_free_split_secure(var->spipe);
		get_token(t_new, tmp, var);
	}
	return (t_new);
}

static void	get_token(t_token *t_new, t_token *tmp, t_var *var)
{
	var_init(var);
	while ((var->s && var->s[var->i]))
	{
		ft_free_split_secure(var->s);
		ft_free_split_secure(var->spipe);
		token_clear(var->new_tkn);
		tmp = token_init(var);
		var->i++;
		if (tmp != NULL && already_cmd(t_new, tmp) != true)
			token_add_back(&t_new, tmp);
		token_clear(tmp);
	}
	if (var->nb_pipe-- > 0) //&& var->spipe[var->index + 1] != NULL)
	{
		tmp = token_pipe();
		token_add_back(&t_new, tmp);
	}
	ft_free_split(var->s);
	ft_free_split(var->spipe);
	// ft_free_split_secure(var->s);
	// ft_free_split_secure(var->spipe);
	token_clear(var->new_tkn);
	var_init(var);
	var->index++;
	var->i = 0;
}

static t_token	*token_init(t_var *var)
{
	if (var_init(var) == false)
	{
		ft_free_split_secure(var->s);
		ft_free_split_secure(var->spipe);
		token_clear(var->new_tkn);
		return (NULL);
	}
	if (var->s && var->s[var->i] && var->s[var->i][0] == '<')
	{
		if (token_infile(var) == -1)
		{
			return (NULL);
		}
	}
	else if (var->s && var->s[var->i] && var->s[var->i][0] == '>')
	{
		if (token_outfile(var) == -1)
		{
			return (NULL);
		}
	}
	else if (var->s && var->s[var->i])
	{
		if (is_builtin(var->s[var->i]) == true)
			token_builtin(var);
		else
			token_cmd(var);
		token_arg(var);
	}
	var->new_tkn->next = NULL;
	return (var->new_tkn);
}

/*

TODO : gerer ls -a > $USER doit faire comme ls -a > "$USER" 
				et ecrire tdutel non pas $USER en name_file
gerer  NORME, LEAKS


/!\
TODO	OK
// gerer "$ , $USER" et $,$USER pour afficher la , est non $tdutel
// gerer les quote dans infile outfile : ls > "<E" doit creer un file <E

//TODO	OK
quand metachar juste apres $ n'ecris pas apres le metachar :
							ls << in"s$.,a USER"	ecrit just ins$

POUR CELA, reprendre la fonction env_symbol()	OK
/!\
*/

	// || (var->i != 0 && var->s[var->i][0] == '-') var->i != 0
	//prmet de gerer le cas ou | -e | comme une cmd

//gerer si name infile est <e 	error si < ou > dans fct in/out.file

// GERER LE CAS OU -e AVANT COMMANDE MAIS PAS EN POSITION 0	
//	ok en remove "|| (var->i != 0 && var->s[var->i][0] == '-')"

// gerer var env et '' ""

//gerer les space de '<' et '>' ex: <<in>>out	heredoc et out append

//ok	:

//	gerer si | avant cmd "| || cat -e"	ok
// gerer les string (ex : echo hello)
//differencier un infile d'un argument de cmd
//	(ex: echo bonjour : echo, bonjour mais aussi bonjour, null	a enlever)
//gerer plusieurs infile	ok
// refaire strjoin pour add space	ok
//gerer les spaces de '|' ex : echo bonjour|rev	doit faire ruojnob	ok

//TOKEN-REDIRECT.C

//<in>out cat makefile| cat<in2 || ls|

// enlever les arg de trop de la lst_tkn (cat <in>ot makefile 	sup makefile)

//gerer  dans infile : cat < in>out makefile
//gerer quandnecrit pas tout: cat <in >out<in2 Makefile	n'ecrit pas le >out<in2
//ok

//	<in>out cat -e Makefile et
//	gerer cat <in0<in>out makefile	ecrit 2 fois la cmd

//		cat in>out makefile|cat<in>out > out		segfault
//mettre la condition dans infile outfile argument et autres...

//	<in>out >out cat|echo lo	

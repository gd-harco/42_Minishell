/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:40:27 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/05 17:02:14 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		get_token(t_token *t_new, t_var *var);
// static t_token	*token_init(t_var *var);

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
	tmp = token_init(var);
	if (tmp == NULL)
	{
		return (NULL);
	}
	t_new = malloc(sizeof(t_token));
	if (t_new == NULL)
	{
		// Gestion de l'erreur d'allocation mémoire, si nécessaire
		// ...
		token_clear(&tmp);
		return (NULL);
	}
	token_memcpy(t_new, tmp);
	token_clear(&tmp);
	// t_new = tknnew(var);
	// token_clear(&var->new_tkn);
	var->i++;
	if (var->s)
	{
		while ((var->index == 0 || var->spipe[var->index - 1])
			&& var->spipe[var->index])
		{
			ft_free_split_secure(&var->s);
			ft_free_split_secure(&var->spipe);
			get_token(t_new, var);
		}
	}
	return (t_new);
}

static void	get_token(t_token *t_new, t_var *var)
{
	t_token	*tmp;
	t_token	*tnew;

	var_init(var);
	while ((var->s && var->s[var->i]))
	{
		ft_free_split_secure(&var->s);
		ft_free_split_secure(&var->spipe);
		tmp = token_init(var);
		if (!tmp)
		{
			token_clear(&t_new);
			free_var(var);
			exit(EXIT_FAILURE); //TODO: call exit function
		}
		tnew = malloc(sizeof(t_token));
		if (!tnew)
			exit(EXIT_FAILURE); //TODO: call exit function ;
		token_memcpy(tnew, tmp);
		token_clear(&tmp);
		var->i++;
		if (tnew != NULL && already_cmd(t_new, tnew) != true)
			token_add_back(&t_new, tnew);
	}
	if (var->nb_pipe-- > 0) //&& var->spipe[var->index + 1] != NULL)
	{
		tmp = token_pipe();
		tnew = malloc(sizeof(t_token));
		if (!tnew)
			exit(EXIT_FAILURE); //TODO: call exit function ;
		token_memcpy(tnew, tmp);
		token_clear(&tmp);
		token_add_back(&t_new, tnew);
	}
	ft_free_split_secure(&var->s);
	ft_free_split_secure(&var->spipe);
	// token_clear(&var->new_tkn);	/*probleme : quand free, free aussi t_new /!\*/
	var_init(var);
	// token_clear(&var->new_tkn);
	var->index++;
	var->i = 0;
}

t_token	*token_init(t_var *var)
{
	var->new_tkn = malloc(sizeof(t_token));
	if (!var->new_tkn || var_init(var) == false)
	{
		ft_free_split_secure(&var->s);
		ft_free_split_secure(&var->spipe);
		free(var->new_tkn);
		return (NULL);
	}
	if (var->s && var->s[var->i] && var->s[var->i][0] == '<')
	{
		if (token_infile(var) == -1)
		{
			free(var->new_tkn);
			return (NULL);
		}
	}
	else if (var->s && var->s[var->i] && var->s[var->i][0] == '>')
	{
		if (token_outfile(var) == -1)
		{
			free(var->new_tkn);
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

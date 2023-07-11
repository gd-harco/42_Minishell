/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:40:27 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/10 19:36:43 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		get_token(t_token *t_new, t_var *var);
static void		token_list_bis(t_var *var, t_token	*t_new);
static void		token_bis(t_token *t_new, t_var *var, t_token *tmp);

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
		return (NULL);
	t_new = malloc(sizeof(t_token));
	if (t_new == NULL)
		return (token_clear(&tmp), NULL);
	token_memcpy(t_new, tmp);
	token_clear(&tmp);
	var->i++;
	if (var->s)
	{
		token_list_bis(var, t_new);
	}
	return (t_new);
}

static void	token_list_bis(t_var *var, t_token	*t_new)
{
	while ((var->index == 0 || var->spipe[var->index - 1])
		&& var->spipe[var->index])
	{
		ft_free_split_secure(&var->s);
		ft_free_split_secure(&var->spipe);
		get_token(t_new, var);
	}
}

static void	get_token(t_token *t_new, t_var *var)
{
	t_token	*tmp;
	t_token	*tnew;

	var_init(var);
	while ((var->s && var->s[var->i]))
	{
		token_bis(t_new, var, tmp);
	}
	if (var->nb_pipe-- > 0)
	{
		tmp = token_pipe();
		if (!tmp)
			exit_free(var, t_new, NULL);
		tnew = malloc(sizeof(t_token));
		if (!tnew)
			exit_free(var, t_new, tmp);
		token_memcpy(tnew, tmp);
		token_clear(&tmp);
		token_add_back(&t_new, tnew);
	}
	ft_free_split_secure(&var->s);
	ft_free_split_secure(&var->spipe);
	var_init(var);
	var->index++;
	var->i = 0;
}

static void	token_bis(t_token *t_new, t_var *var, t_token *tmp)
{
	t_token	*tnew;

	ft_free_split_secure(&var->s);
	ft_free_split_secure(&var->spipe);
	tmp = token_init(var);
	if (!tmp)
	{
		token_clear(&t_new);
		free_var(var);
		free(var->new_tkn);
		exit(EXIT_FAILURE);
	}
	tnew = malloc(sizeof(t_token));
	if (!tnew)
	{
		token_clear(&t_new);
		token_clear(&tmp);
		free_var(var);
		exit(EXIT_FAILURE);
	}
	token_memcpy(tnew, tmp);
	token_clear(&tmp);
	var->i++;
	if (tnew != NULL && already_cmd(t_new, tnew) != true)
		token_add_back(&t_new, tnew);
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

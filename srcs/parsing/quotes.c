/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:25:29 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/05 16:51:31 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quote_manager(t_var *var, t_varenv *v_e)
{
	t_var_quote	v_q;

	v_q.t[1] = '\0';
	var->quote = NULL;
	v_q.split_tmp = ft_split(var->s[v_e->j], ';');
	if (!v_q.split_tmp)
		return ;
	v_q.tmp = NULL;
	var->quote = NULL;
	v_q.i = 0;
	while (v_q.split_tmp[v_q.i])
	{
		if (is_quote_in(v_q.split_tmp[v_q.i]) == 1)
			single_quote(v_q.split_tmp[v_q.i], var, &v_q.tmp);
		else if (is_quote_in(v_q.split_tmp[v_q.i]) == 2)
			dub_quote(v_q.split_tmp[v_q.i], var, v_e, &v_q.tmp);
		else
		{
			if (no_quote(var, v_e, &v_q) == -1)
				return (free_quote(&v_q));
		}
		v_q.i++;
	}
	var->quote = ft_strdup(v_q.tmp);
	free_quote(&v_q);
}

void	quote_manager_inout(t_var *var, t_varenv *v_e)
{
	t_var_quote	v_q;

	v_q.t[1] = '\0';
	var->quote = NULL;
	v_q.split_tmp = ft_split(ft_trunc_start(var->s[v_e->j], "<>", *var), ';');
	if (!v_q.split_tmp)
		return ;
	v_q.tmp = NULL;
	var->quote = NULL;
	v_q.i = 0;
	while (v_q.split_tmp[v_q.i])
	{
		if (is_quote_in(v_q.split_tmp[v_q.i]) == 1)
			single_quote(v_q.split_tmp[v_q.i], var, &v_q.tmp);
		else if (is_quote_in(v_q.split_tmp[v_q.i]) == 2)
			dub_quote(v_q.split_tmp[v_q.i], var, v_e, &v_q.tmp);
		else
		{
			if (no_quote(var, v_e, &v_q) == -1)
				return (free_quote(&v_q));
		}
		v_q.i++;
	}
	var->quote = ft_strdup(v_q.tmp);
	free_quote(&v_q);
}

/*

/!\
gerer "$ , $USER" et $,$USER pour afficher la , est non $tdutel

gerer les quote dans infile outfile : ls > "<E" doit creer un file <E


echo "$(echo "upg")"	=	echo $(echo "upg")
		upg

echo '$(echo"upg")'
	$(echo"upg")

*/

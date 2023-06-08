/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:06:42 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/02 14:33:59 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_here_doc	*fill_hd_data(t_token *token_list, size_t nb_here_doc);
static void			write_in_here_doc(t_here_doc *here_doc, size_t nb_here_doc);
static size_t		count_here_doc(t_token *token_list);
static int			*turn_pipe_in_fd(t_here_doc *here_doc, size_t nb_here_doc);

int	*get_here_doc_fd(t_token *token_list)
{
	size_t		nb_here_doc;
	t_token		*tmp;
	t_here_doc	*here_doc;
	int			*here_doc_fd;

	tmp = token_list;
	nb_here_doc = count_here_doc(tmp);
	if (nb_here_doc == 0)
		return (NULL);
	here_doc = fill_hd_data(token_list, nb_here_doc);
	here_doc_fd = turn_pipe_in_fd(here_doc, nb_here_doc);
	free(here_doc);
	return (here_doc_fd);
}

static size_t	count_here_doc(t_token *token_list)
{
	size_t	nb_here_doc;

	nb_here_doc = 0;
	while (token_list)
	{
		if (token_list->type == HERE_DOC)
			nb_here_doc++;
		token_list = token_list->next;
	}
	return (nb_here_doc);
}

static int	*turn_pipe_in_fd(t_here_doc *here_doc, size_t nb_here_doc)
{
	size_t	i;
	int		*here_doc_fd;

	i = -1;
	here_doc_fd = ft_calloc(nb_here_doc, sizeof(int));
	while (++i < nb_here_doc)
	{
		here_doc_fd[i] = dup(here_doc[i].pipe_fd[0]);
		close(here_doc[i].pipe_fd[0]);
	}
	return (here_doc_fd);
}

static t_here_doc	*fill_hd_data(t_token *token_list, size_t nb_here_doc)
{
	t_here_doc	*here_doc;
	t_token		*tmp;
	size_t		i;

	here_doc = ft_calloc(nb_here_doc, sizeof(t_here_doc));
	if (!here_doc)
		exit(EXIT_FAILURE);//TODO: Call exit function
	tmp = token_list;
	i = 0;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
		{
			here_doc[i].delimiter = tmp->content[0];
			if (pipe(here_doc[i].pipe_fd) == -1)
				exit(EXIT_FAILURE);//TODO: Call exit function
			i++;
		}
		tmp = tmp->next;
	}
	write_in_here_doc(here_doc, nb_here_doc);
	return (here_doc);
}

static void	write_in_here_doc(t_here_doc *here_doc, size_t nb_here_doc)
{
	size_t	i;

	i = 0;
	while (i < nb_here_doc)
	{
		here_doc[i].tmp_char = readline(HD_PROMPT);
		while (!ft_strcmp(here_doc[i].tmp_char, here_doc[i].delimiter))
		{
			write(here_doc[i].pipe_fd[1], here_doc[i].tmp_char,
				ft_strlen(here_doc[i].tmp_char));
			free(here_doc[i].tmp_char);
			write(here_doc[i].pipe_fd[1], "\n", 1);
			here_doc[i].tmp_char = readline(HD_PROMPT);
		}
		free(here_doc[i].tmp_char);
		close(here_doc[i].pipe_fd[1]);
		i++;
	}
}

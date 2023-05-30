/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:33:05 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/30 10:11:38 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*get_next_delimiter(t_token *token);
static void		fill_here_doc(t_exec *data, t_here_doc *here_doc);

//TODO gerer les signaux pour les heredoc

/**
 * @brief Malloc the good number of t_here_doc and call fill_here_doc
 * at the end of the function, every heredoc
 * has a pipe_fd with the read end open,
 * and the write end closed.
 * both the delimiter and the tmp_char are freed
 * @param data
 */
void	process_here_doc(t_exec *data)
{
	size_t	i;

	i = -1;
	data->here_doc = malloc(sizeof(t_here_doc) * data->nb_here_doc);
	if (data->here_doc == NULL)
		exit(EXIT_FAILURE);//TODO: call function pointer exit
	while (++i < data->nb_here_doc)
		fill_here_doc(data, &data->here_doc[i]);
}

static t_token	*get_next_delimiter(t_token *token)
{
	while (token)
	{
		if (token->type == HERE_DOC)
			return (token);
		token = token->next;
	}
	return (NULL);
}

static void	fill_here_doc(t_exec *data, t_here_doc *here_doc)
{
	here_doc->link = get_next_delimiter(data->token_list);
	here_doc->delimiter = ft_strdup(here_doc->link->content[0]);
	pipe(here_doc->pipe_fd);
	here_doc->tmp_char = readline("> ");
	while (!ft_strcmp(here_doc->tmp_char, here_doc->delimiter))
	{
		write(here_doc->pipe_fd[1], here_doc->tmp_char,
			ft_strlen(here_doc->tmp_char));
		write(here_doc->pipe_fd[1], "\n", 1);
		free(here_doc->tmp_char);
		here_doc->tmp_char = readline("> ");
	}
	close(here_doc->pipe_fd[1]);
	free(here_doc->delimiter);
	free(here_doc->tmp_char);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:33:05 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/19 17:26:12 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*get_next_delimiter(t_token *token);
static void		get_user_doc(t_exec *data);

void	process_here_doc(t_exec *data)
{
	int		i;

	i = -1;
	while (++i < data->nb_here_doc)
		get_user_doc(data);
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

static void	get_user_doc(t_exec *data)
{
	int		pipe_fd[2];
	char	*delimiter;
	char	*tmp_char;
	t_token	*tmp;

	tmp = get_next_delimiter(data->minishell_data->token_list);
	delimiter = ft_strdup(tmp->content[0]);
	pipe(pipe_fd);
	tmp_char = readline("> ");
	while (!ft_strcmp(tmp_char, delimiter))
	{
		write(pipe_fd[1], tmp_char, ft_strlen(tmp_char));
		write(pipe_fd[1], "\n", 1);
		free(tmp_char);
		tmp_char = readline("> ");
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	free(delimiter);
	close(pipe_fd[0]);
	free(tmp_char);
}

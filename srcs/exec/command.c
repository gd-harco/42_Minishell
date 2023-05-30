/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:19:25 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/20 11:34:47 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_infile_fd(t_exec *data, t_token *first_link);
static int	get_outfile_fd(t_token *first_link);
static char	**get_cmd_array(t_token *first_link);

void	fill_cmd(t_exec *data)
{
	int		i;
	t_token	*first_link;

	i = 0;
	first_link = data->minishell_data->token_list;
	while (i < data->nb_cmd)
	{
		data->cmd[i].in_fd = get_infile_fd(data, first_link);
		data->cmd[i].out_fd = get_outfile_fd(first_link);
		data->cmd[i].cmd = get_cmd_array(first_link);
		i++;
		while (first_link->type != PIPE)
			first_link = first_link->next;
		first_link = first_link->next;
	}
}

static int	get_infile_fd(t_exec *data, t_token *first_link)
{
	t_token	*tmp;
	int		fd;

	tmp = first_link;
	fd = STDIN_FILENO;
	while (tmp->type != PIPE)
	{
		if (tmp->type == FILE_IN)
			fd = open(tmp->content[0], O_RDONLY);
		else if (tmp->type == HERE_DOC)
			fd = data->here_doc->pipe_fd[0];
		tmp = tmp->next;
	}
	return (fd);
}

static int	get_outfile_fd(t_token *first_link)
{
	t_token	*tmp;
	int		fd;

	tmp = first_link;
	fd = STDOUT_FILENO;
	while (tmp->type != PIPE)
	{
		if (tmp->type == FILE_OUT)
			fd = open(tmp->content[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tmp->type == FILE_OUT_APPEND)
			fd = open(tmp->content[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
		tmp = tmp->next;
	}
	return (fd);
}

static char	**get_cmd_array(t_token *first_link)
{
	t_token	*tmp;

	tmp = first_link;
	while (tmp->type != PIPE)
	{
		if (tmp->type == CMD || tmp->type == BUILTIN)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

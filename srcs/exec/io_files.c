/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:10:37 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/30 16:01:28 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_io_file(t_cmd	*cmd)
{
	//TODO: Handle multiple infile, if one infile doesn't exist, print error
	int	cur_outfile;

	if (cmd->in_type == INFILE)
		cmd->file_fd[0] = open(cmd->in_file, O_RDONLY);
	else if (cmd->in_type == HERE_DOC_I)
		ft_dprintf(STDOUT_FILENO, "todo here_doc"); //TODO: here_doc
	else
		cmd->file_fd[0] = dup(STDIN_FILENO);
	cur_outfile = 0;
	if (cmd->out_type == OUTFILE || cmd->out_type == OUTFILE_APPEND)
	{
		while (cmd->out_file[cur_outfile] != NULL)
		{
			if (cmd->out_type == OUTFILE)
				cmd->file_fd[1]
					= open(cmd->out_file[cur_outfile], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (cmd->out_type == OUTFILE_APPEND)
				cmd->file_fd[1]
					= open(cmd->out_file[cur_outfile], O_WRONLY | O_CREAT | O_APPEND, 0644);
			cur_outfile++;
		}
	}
	else
		cmd->file_fd[1] = STDOUT_FILENO;
}

int	get_io_file_path(t_cmd *cmd, t_token *first_token)
{
	t_token	*tmp;
	int		nb_infile;
	int		nb_outfile;

	if (cmd->in_type == INFILE)
	{
		nb_infile = 0;
		tmp = first_token;
		while (tmp && tmp->type != FILE_IN)
			tmp = tmp->next;
		// cmd->in_file = ft_strdup(tmp->content[0]);
	}
	else
		cmd->in_file = NULL;
	if (cmd->out_type != 0)
	{
		nb_outfile = 0;
		tmp = first_token;
		while (tmp)
		{
			if (tmp->type == FILE_OUT || tmp->type == FILE_OUT_APPEND)
				nb_outfile++;
			tmp = tmp->next;
		}
		tmp = first_token;
		cmd->out_file = ft_calloc(sizeof(char *), (nb_outfile + 1));
		if (cmd->out_file == NULL)
			exit(EXIT_FAILURE); //TODO: call function pointer exi
		cmd->out_file[nb_outfile] = NULL;
		nb_outfile = 0;
		while (tmp)
		{
			if (tmp->type == FILE_OUT || tmp->type == FILE_OUT_APPEND)
				cmd->out_file[nb_outfile++] = ft_strdup(tmp->content[0]);
			tmp = tmp->next;
		}
	}
	else
		cmd->out_file = NULL;
}

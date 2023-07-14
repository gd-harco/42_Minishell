/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 07:45:01 by gd-harco          #+#    #+#             */
/*   Updated: 2023/07/14 07:45:04 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		free_hd_fd(t_exec *exec_data, size_t last_hd_free);

void	free_exec(t_exec *exec_data)
{
	size_t	i;
	size_t	str_to_free;

	close(exec_data->std_save[0]);
	close(exec_data->std_save[1]);
	token_clear(&exec_data->token_list);
	if (exec_data->here_doc_fd)
		free_hd_fd(exec_data, 0);
	free(exec_data->pid);
	if (exec_data->cmd)
	{
		i = exec_data->nb_cmd;
		while (i--)
		{
			if (exec_data->cmd[i].argv == NULL)
				continue ;
			str_to_free = ft_array_length((void **)exec_data->cmd[i].argv);
			while (str_to_free--)
				free(exec_data->cmd[i].argv[str_to_free]);
			free(exec_data->cmd[i].argv);
		}
		free(exec_data->cmd);
	}
	free(exec_data);
}

static void	free_hd_fd(t_exec *exec_data, size_t last_hd_free)
{
	while (last_hd_free < exec_data->nb_here_doc)
		close(exec_data->here_doc_fd[last_hd_free++]);
	free(exec_data->here_doc_fd);
}

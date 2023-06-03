/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:40:24 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/02 18:12:41 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(t_token *f_token);
char	**get_cmd_argv(t_token *f_token);
void	get_cmd_io(t_token *f_token, t_cmd cmd, t_exec *exec_data);

t_cmd	*get_cmd_data(t_exec *exec_data)
{
	t_cmd	*cmd;
	size_t	current_cmd;
	t_token	*cmd_first_token;

	current_cmd = 0;
	cmd_first_token = exec_data->token_list;
	cmd = ft_calloc(exec_data->nb_cmd, sizeof(t_cmd));
	if (!cmd)
		exit(EXIT_FAILURE);//TODO: Call exit function
	while (current_cmd < exec_data->nb_cmd)
	{
		cmd[current_cmd].path = get_cmd_path(cmd_first_token);
		cmd[current_cmd].argv = get_cmd_argv(cmd_first_token);
		get_cmd_io(cmd_first_token, cmd[current_cmd], exec_data);
		current_cmd++;
	}
	return (cmd);
}


char	*get_cmd_path(t_token *f_token)
{
	char	*path;

	path = NULL;
	while (f_token && f_token->type != CMD)
		f_token = f_token->next;
	path = ft_strdup(f_token->content[0]);
	return (path);
}

char	**get_cmd_argv(t_token *f_token)
{
	char	**argv;
	char	**tmp;
	int		i;

	while (f_token && f_token->type != CMD)
		f_token = f_token->next;
	if (!f_token->content[1])
	{
		argv = ft_calloc(2, sizeof(char *));
		if (!argv)
			exit(EXIT_FAILURE);//TODO: Call exit function
		argv[0] = ft_strdup(f_token->content[0]);
		return (argv);
	}
	tmp = ft_split (f_token->content[1], ' ');
	argv = ft_calloc(ft_array_length((void **)tmp) + 2, sizeof(char *));
	if (!argv)
		exit(EXIT_FAILURE);//TODO: Call exit function
	argv[0] = ft_strdup(f_token->content[0]);
	i = 0;
	while (tmp[++i])
		argv[i + 1] = ft_strdup(tmp[i]);
	return (argv);
}

void	get_cmd_io(t_token *f_token, t_cmd cmd, t_exec *exec_data)
{
	t_token	*tmp;

	tmp = f_token;
	cmd.io_fd[0] = dup(STDIN_FILENO);
	cmd.io_fd[1] = dup(STDOUT_FILENO);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == FILE_IN)
			cmd.io_fd[0] = open(tmp->content[0], O_RDONLY);
		else if (tmp->type == HERE_DOC)
			cmd.io_fd[0] = exec_data->here_doc_fd[exec_data->nb_current_hd++];
		else if (tmp->type == FILE_OUT)
			cmd.io_fd[1] = open(tmp->content[0],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tmp->type == FILE_OUT_APPEND)
			cmd.io_fd[1] = open(tmp->content[0],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd.io_fd[0] == -1 || cmd.io_fd[1] == -1)
			exit(IO_FAILURE);//TODO: Call exit function case infile or outfile fail
		tmp = tmp->next;
	}
}

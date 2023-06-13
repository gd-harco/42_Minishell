/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:40:24 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/05 21:49:49 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_cmd_argv(t_token **f_token);
static char	**cmd_with_no_args(t_token **f_token);
static void	set_builtin(t_cmd *cmd);

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
		cmd[current_cmd].argv = get_cmd_argv(&cmd_first_token);
		set_builtin(&cmd[current_cmd++]);
	}
	return (cmd);
}

static char	**get_cmd_argv(t_token **f_token)
{
	char	**argv;
	char	**tmp;
	int		i;

	while (*f_token && (*f_token)->type != CMD && (*f_token)->type != BUILTIN)
		*f_token = (*f_token)->next;
	if (!(*f_token)->content[1])
		return (cmd_with_no_args(f_token));
	tmp = ft_split ((*f_token)->content[1], ' ');
	argv = ft_calloc(ft_array_length((void **)tmp) + 2, sizeof(char *));
	if (!argv)
		exit(EXIT_FAILURE);//TODO: Call exit function
	argv[0] = ft_strdup((*f_token)->content[0]);
	i = -1;
	while (tmp[++i])
		argv[i + 1] = ft_strdup(tmp[i]);
	*f_token = (*f_token)->next;
	ft_free_split(tmp);
	return (argv);
}

static char	**cmd_with_no_args(t_token **f_token)
{
	char	**argv;

	argv = ft_calloc(2, sizeof(char *));
	if (!argv)
		exit(EXIT_FAILURE);//TODO: Call exit function
	argv[0] = ft_strdup((*f_token)->content[0]);
	*f_token = (*f_token)->next;
	return (argv);
}

static void	set_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "echo"))
		cmd->builtin = ECHO;
	else if (ft_strcmp(cmd->argv[0], "cd"))
		cmd->builtin = CD;
	else if (ft_strcmp(cmd->argv[0], "pwd"))
		cmd->builtin = PWD;
	else if (ft_strcmp(cmd->argv[0], "export"))
		cmd->builtin = EXPORT;
	else if (ft_strcmp(cmd->argv[0], "unset"))
		cmd->builtin = UNSET;
	else if (ft_strcmp(cmd->argv[0], "env"))
		cmd->builtin = ENV;
	else if (ft_strcmp(cmd->argv[0], "exit"))
		cmd->builtin = EXIT;
	else
		cmd->builtin = NONE;
}
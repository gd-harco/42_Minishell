#include "minishell.h"

static int	get_in_fd(t_token *token, t_exec *exec_data);
static int	get_out_fd(t_token *token);

void	exec_piped_cmd(t_exec *exec_data, size_t current_cmd)
{
	dprintf(2, "exec_piped_cmd\n");
	handle_io(exec_data, current_cmd);
	if (exec_data->cmd[current_cmd].builtin != NONE)
	{
		exec_builtin(exec_data, current_cmd);
		free_exec(exec_data);
		exit(EXIT_SUCCESS);
	}
	execve(exec_data->cmd[current_cmd].argv[0],
		exec_data->cmd[current_cmd].argv, exec_data->envp);
	dprintf(STDERR_FILENO, "execve failed in cmd %zu\n", current_cmd);
	exit(EXIT_FAILURE);//TODO: Call exit function
}

void	handle_io(t_exec *exec_data, size_t current_cmd)
{
	size_t	i;
	t_token	*tmp;
	int		fd[2];

	i = 0;
	tmp = exec_data->token_list;
	while (tmp && i < current_cmd)
	{
		if (tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == FILE_IN || tmp->type == HERE_DOC)
		{
			fd[0] = get_in_fd(tmp, exec_data);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
		else if (tmp->type == FILE_OUT || tmp->type == FILE_OUT_APPEND)
		{
			fd[1] = get_out_fd(tmp);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		tmp = tmp->next;
	}
}

void	exec_builtin(t_exec *exec_data, size_t current_cmd)
{
	if (exec_data->cmd[current_cmd].builtin == ECHO)
		echo(exec_data->cmd[current_cmd].argv);
	else if (exec_data->cmd[current_cmd].builtin == CD)
		cd(exec_data->cmd[current_cmd].argv, exec_data);
//	else if (exec_data->cmd[current_cmd].builtin == PWD)
//		pwd(exec_data->cmd[current_cmd].argv, exec_data->envp);
//	else if (exec_data->cmd[current_cmd].builtin == EXPORT)
//		export(exec_data->cmd[current_cmd].argv, exec_data->envp);
//	else if (exec_data->cmd[current_cmd].builtin == UNSET)
//		unset(exec_data->cmd[current_cmd].argv, exec_data->envp);
//	else if (exec_data->cmd[current_cmd].builtin == ENV)
//		env(exec_data->envp);
//	else if (exec_data->cmd[current_cmd].builtin == EXIT)
//		exit_shell(exec_data->cmd[current_cmd].argv);
}

int	get_in_fd(t_token *token, t_exec *exec_data)
{
	int	fd;

	if (token->type == FILE_IN)
		fd = open(token->content[0], O_RDONLY);
	else if (token->type == HERE_DOC)
		fd = exec_data->here_doc_fd[exec_data->nb_current_hd++];
	else
		fd = -1;
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: %s: %s\n",
			strerror(errno), token->content[0]);
		exit(IO_FAILURE);//TODO: Call exit function
	}
	return (fd);
}

int	get_out_fd(t_token *token)
{
	int	fd;

	if (token->type == FILE_OUT)
		fd = open(token->content[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (token->type == FILE_OUT_APPEND)
		fd = open(token->content[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: %s: %s\n",
			strerror(errno), token->content[0]);
		exit(IO_FAILURE);//TODO: Call exit function
	}
	return (fd);
}

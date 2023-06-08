#include "minishell.h"

//void	handle_io(t_exec *exec_data, size_t current_cmd);

void	exec_piped_cmd(t_exec *exec_data, size_t current_cmd)
{
//	handle_io(exec_data, current_cmd);
	execve(exec_data->cmd[current_cmd].argv[0],
		exec_data->cmd[current_cmd].argv, exec_data->envp);
	dprintf(STDERR_FILENO, "execve failed in cmd %zu\n", current_cmd);
	exit(EXIT_FAILURE);//TODO: Call exit function
}

//void	handle_io(t_exec *exec_data, size_t current_cmd)
//{
//	size_t	i;
//	t_token	*tmp;
//
//	i = 0;
//	tmp = exec_data->token_list;
//	while (tmp && i < current_cmd)
//	{
//		if (tmp->type == PIPE)
//			i++;
//		tmp = tmp->next;
//	}
//	while
//}

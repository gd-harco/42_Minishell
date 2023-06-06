#include "minishell.h"

void	close_child_unused_fd(size_t cmd_nb, t_pipe_fd *pipe_fd, size_t nb_pipe)
{
	close(pipe_fd[cmd_nb].pipe_fd[0]);
	cmd_nb++;
	while (cmd_nb < nb_pipe)
	{
		close(pipe_fd[cmd_nb].pipe_fd[0]);
		close(pipe_fd[cmd_nb++].pipe_fd[1]);
	}
}

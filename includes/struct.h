/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:17:21 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/05 22:18:03 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

//-----------------STRUCTURES-----------------//

enum e_type {
	UNDEFINED = 0,
	HERE_DOC = 1,
	PIPE = 2,
	FILE_IN = 3 ,
	FILE_OUT = 4,
	FILE_OUT_APPEND = 5,
	CMD = 6,
	BUILTIN = 7
};

typedef struct s_token
{
	char			**content;
	enum e_type		type;
	struct s_token	*next;
}				t_token;

typedef struct s_minishell
{
	char	**envp;
	t_token	*token_list;
}				t_minishell;

typedef struct s_here_doc
{
	int		pipe_fd[2];
	char	*delimiter;
	char	*tmp_char;
}				t_here_doc;

typedef struct s_cmd
{
	char			**argv;
}				t_cmd;

typedef struct s_pipe_fd
{
	int		pipe_fd[2];
}				t_pipe_fd;

typedef struct s_exec
{
	char		**envp;
	t_token		*token_list;
	size_t		nb_cmd;
	size_t		nb_pipe;
	int			*here_doc_fd;
	size_t		nb_current_hd;
	t_cmd		*cmd;
	pid_t		*pid;
	int			std_save[2];
	int			pipe_fd[2];
}				t_exec;

#endif

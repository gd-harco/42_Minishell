/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:17:21 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/21 14:54:56 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

//-----------------STRUCTURES-----------------//

enum e_type {
	UNDEFINED,
	HERE_DOC,
	PIPE,
	FILE_IN,
	FILE_OUT,
	FILE_OUT_APPEND,
	CMD,
	BUILTIN
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
	t_token	*link;
}				t_here_doc;

enum e_i_type {
	STDIN = 0,
	INFILE = 1,
	HERE_DOC_I = 2
};

enum e_o_type {
	STDOUT = 0,
	OUTFILE = 1,
	OUTFILE_APPEND = 2
};

typedef struct s_cmd
{
	int				command_id;
	enum e_i_type	in_type;
	enum e_o_type	out_type;
	char			*path;
	char			**cmd;
	char			**envp;
}				t_cmd;

typedef struct s_exec
{
	t_minishell	*minishell_data;
	int			nb_cmd;
	int			nb_here_doc;
	t_here_doc	*here_doc;
	t_cmd		*cmd;
}				t_exec;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:17:21 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/01 14:18:33 by tdutel           ###   ########.fr       */
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

//in "file_fd", 0 is for input, 1 is for output.
typedef struct s_cmd
{
	size_t			command_id;
	enum e_i_type	in_type;
	enum e_o_type	out_type;
	char			*path;
	char			**cmd;
	char			*in_file;
	char			**out_file;
	pid_t			pid;
	int				file_fd[2];
}				t_cmd;

typedef struct s_exec
{
	char		**envp;
	t_token		*token_list;
	size_t		nb_cmd;
	size_t		nb_here_doc;
	t_here_doc	*here_doc;
	t_cmd		*cmd;
	int			pipe_fd[2];
}				t_exec;

typedef struct s_var
{
	char	*str;		//la commande prompt
	char	**s;		// chaque mots espacés
	char	**spipe;	//phrase split par les |
	int		nb_pipe;
	char	**envp;
	int		index;
	int		i;
	char	**path;
	char	*s_p;
	char	*arg;
	char	*env;
	bool	recu;
	t_token	*new_tkn;
	int		lenquote;
	char	*quote;
	bool	is_quote;
	// t_token	*tkn_past;
}				t_var;

typedef struct s_varenv
{
	int		i;
	int		j;
	int		k;
	int		m;
	char	*var_env;
}				t_varenv;

#endif

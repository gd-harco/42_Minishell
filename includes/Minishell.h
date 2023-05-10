/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:10:06 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/10 13:46:26 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <sys/stat.h>
# include <dirent.h>
# include "../lib/libft/includes/libft.h"
# include <errno.h>

char	*process(char *str, char **path);
char	**get_path(char **envp);

typedef struct s_cmd_table t_cmd_table;
/*
	¨cmd_array¨ is an array of all the command passed by the user. The string in [x][0] will always be the path to the command to launch,
	and all the other string of the line will be the argument to pass to the exec. I must be ended by a NULL character.
	"io_array" is a
*/
struct s_cmd_table
{
	char		**cmd_array;
	char		**infile;
	char		**outfile;		//gerer les append et iork
	int			fd_infile;
	int			fd_outfile;
	int			fd_error;
	t_cmd_table	*next_cmd;
};


#endif

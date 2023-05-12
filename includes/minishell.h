/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:10:06 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/12 16:29:09 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//-----------------INCLUDES-----------------//
# include "../lib/libft/includes/libft.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>

//-----------------STRUCTURES-----------------//
//Pour parsing, ne prendre en compte que les tokens de type STRING,
//PIPE, CHEVRON_IN, DOUBLE_CHEVRON_IN, CHEVRON_OUT, DOUBLE_CHEVRON_OUT
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

//-----------------FUNCTIONS-----------------//

//------------------PATH.C-------------------//
char	**path_arg_cat(char **src, char *root_arg);
char	**get_path(char **envp);
char	*process(char *str, char **path, int *ind);

//-----------------TOKEN.C-------------------//
t_token	*get_token(char *str, char **envp);
t_token	*token_init(char *str, char **envp, int *i);
//--------------SECOND_PARSING.C------------//
void	second_parsing(t_token *token_list);

#endif

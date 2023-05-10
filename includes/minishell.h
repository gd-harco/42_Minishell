/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:10:06 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/10 15:14:38 by gd-harco         ###   ########lyon.fr   */
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
	CHEVRON_IN,
	DOUBLE_CHEVRON_IN,
	STRING,
	PIPE,
	CMD,
	CALL_ENV_VAR,
	BUILTIN,
	DOUBLE_CHEVRON_OUT,
	CHEVRON_OUT
};

typedef struct s_token
{
	char			**content;
	enum e_type		type;
	struct s_token	*next;
}				t_token;

//-----------------FUNCTIONS-----------------//
char	*process(char *str, char **path);
char	**get_path(char **envp);
#endif

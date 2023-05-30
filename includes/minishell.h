/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:10:06 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/19 13:39:15 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//-----------------INCLUDES-----------------//

//########### PERSONNAL LIB HEADERS ##########//
# include "../lib/libft/includes/libft.h"

//########### PROJECT SPECIFICS HEADERS ##########//
# include "builtins.h"

//########### SYSTEM LIB HEADERS ##########//
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

typedef struct s_minishell
{
	char	**envp;
	t_token	*token_list;
}				t_minishell;

typedef struct s_var
{
	char	*str;
	char	**s;
	char	**spipe;
	char	**envp;
	int		index;
	int		i;
	char	**path;
	char	*s_p;
	char	*arg;
	char	*env;
	t_token	*new_tkn;
}				t_var;

//------------------PROMPT.C------------------//
char	*get_user_input(void);

//------------------PATH.C-------------------//
char	**get_path(char **envp);
char	**path_arg_cat(char **src, char *root_arg);
char	*process(char *str, char **path, int ind);

//-----------------TOKEN.C-------------------//
t_token	*get_token(t_var *var);
t_token	*token_init(t_var *var);

//---------------TOKEN_FCT.C---------------//
int		token_infile(t_var *var);
void	token_outfile(t_var *var);
t_token	*token_pipe(void);

//---------------TOKEN_CMD_FCT.C---------------//
void	token_builtin(t_var *var);
void	token_cmd(t_var *var);

//---------------TOKEN_CHECK.C---------------//
bool	already_cmd(t_token *t_new, t_token *tmp);
void	token_arg(t_var *var);
bool	var_init(t_var *var);

//-----------------UTILS.C-----------------//
bool	is_builtin(char *str);
bool	not_in_out(char **s, int j);
bool	is_last_infile(char **s, int i);
char	*ft_strjoinsp(char const *s1, char const *s2);

//--------------SECOND_PARSING.C------------//
void	second_parsing(t_token *token_list);

# define ROCKET_LOGO "##################################\n\
####################################,\n\
######################################\n\
######################################,\n\
###########               #############\n\
###########               #############\n\
######################################\n\
#####################################*\n\
####################################\n\
#################################/\n\
#################################/\n\
###########           #############\n\
###########            *############\n\
###########              ############.\n\
###########               #############\n\n"


#endif

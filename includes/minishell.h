/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:10:06 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/24 15:31:37 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//-----------------INCLUDES-----------------//

//########### PERSONNAL LIB HEADERS ##########//

# include "../lib/libft/includes/libft.h"

//########### PROJECT SPECIFICS HEADERS ##########//

# include "builtins.h"
# include "exec.h"

//########### SYSTEM LIB HEADERS ##########//

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

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

//-----------------FUNCTION-----------------//

//################# PROMPT.C #################//
char	*get_user_input(void);

//################# PATH.C #################//
char	**get_path(char **envp);
char	**path_arg_cat(char **src, char *root_arg);
char	*process(char *str, char **path, int ind);

//################# TOKEN.C #################//
t_token	*get_token(t_var *var);
t_token	*token_init(t_var *var);

//################# TOKEN_CHECK.C################# //
bool	already_cmd(t_token *t_new, t_token *tmp);
void	token_arg(t_var *var);
bool	var_init(t_var *var);

//-----------------UTILS.C-----------------//
bool	is_builtin(char *str);
bool	not_in_out(char **s, int j);
bool	is_last_infile(char **s, int i);
char	*ft_strjoinsp(char const *s1, char const *s2);

//---------------TOKEN_FCT.C---------------//
int		token_infile(t_var *var);
void	token_outfile(t_var *var);
t_token	*token_pipe(void);

//---------------TOKEN_CMD_FCT.C---------------//
void	token_builtin(t_var *var);
void	token_cmd(t_var *var);

# define ROCKET_LOGO "\033[0;31m\nBienvenue dans le Minishell de la Team Rocket!\n\n##################################\n\
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
###########               #############\n\n\033[0m"

#endif

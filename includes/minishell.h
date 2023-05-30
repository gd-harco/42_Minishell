/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:10:06 by tdutel            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/25 15:02:44 by gd-harco         ###   ########lyon.fr   */
=======
/*   Updated: 2023/05/29 15:35:24 by tdutel           ###   ########.fr       */
>>>>>>> Tim
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
# include <sys/wait.h>
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

<<<<<<< HEAD
//-----------------FUNCTION-----------------//

//################# PROMPT.C #################//
=======
typedef struct s_varenv
{
	int		i;
	int		j;
	int		k;
	int		m;
	char	*var_env;
}				t_varenv;

//------------------PROMPT.C------------------//
>>>>>>> Tim
char	*get_user_input(void);

//################# PATH.C #################//
char	**get_path(char **envp);
char	**path_arg_cat(char **src, char *root_arg);
char	*process(char *str, char **path, int ind);

//################# TOKEN.C #################//
t_token	*get_token(t_var *var);
t_token	*token_init(t_var *var);

<<<<<<< HEAD
//################# TOKEN_CHECK.C################# //
=======
//---------------TOKEN_FCT.C---------------//
int		token_infile(t_var *var);
void	token_outfile(t_var *var);
t_token	*token_pipe(void);

//---------------TOKEN_CMD_FCT.C---------------//
bool	is_env_in(t_var var, int j);
void	token_builtin(t_var *var);
void	token_cmd(t_var *var);
bool	is_metachar(char c);
char	*ft_trunc(char *str, int start, char c);

//---------------TOKEN_ENV_VAR.C---------------//
void	env_arg(t_var *var, t_varenv *v_e);

//---------------TOKEN_CHECK.C---------------//
>>>>>>> Tim
bool	already_cmd(t_token *t_new, t_token *tmp);
void	token_arg(t_var *var);
bool	var_init(t_var *var);
char	*check_var(t_var *var, t_varenv *v_e);

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

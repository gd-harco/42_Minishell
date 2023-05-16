/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:10:06 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/16 14:15:12 by tdutel           ###   ########.fr       */
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
	t_token	**token_list;
}				t_minishell;

//------------------PATH.C-------------------//
char	*get_user_input(void);
char	**path_arg_cat(char **src, char *root_arg);
char	**get_path(char **envp);
char	*process(char *str, char **path, int *ind);

//-----------------TOKEN.C-------------------//
t_token	*get_token(char *str, char **envp);
t_token	*token_init(char *str, char **envp, int *i, char **s);

//--------------SECOND_PARSING.C------------//
void	second_parsing(t_token *token_list);

//-----------------UTILS.C-----------------//
bool	is_builtin(char *str);
bool	not_in_out(char **s, int j);
bool	is_last_infile(char **s, int i);
char	*ft_strjoinsp(char const *s1, char const *s2);

//---------------TOKEN_FCT.C---------------//
int		token_infile(t_token *new, char **s, int **i);
void	token_outfile(t_token *new, char **s, int **i);
void	token_pipe(t_token *new, char **s, int **i);
void	token_builtin(t_token *new, char **s, int **i);
void	token_cmd(char *str, t_token *new, int **i, char **envp);

#endif

// int	token_infile(t_token *new, char **s, int **i)
// {
// 	if (is_last_infile(s, **i) != true)
// 	{
// 		++**i;
// 		return (-1);
// 	}
// 	if (s[**i][1] == '<')
// 	{
// 		if (s[**i][2] != '\0')
// 			new->content[0] = ft_strdup(ft_substr(s[**i], 1, ft_strlen(s[**i])));
// 		else
// 			new->content[0] = ft_strdup(s[++**i]);
// 		new->type = HERE_DOC;
// 	}
// 	else if (s[**i][1] != '\0')
// 	{
// 		new->type = FILE_IN;
// 		new->content[0] = ft_strdup(ft_substr(s[**i], 1, ft_strlen(s[**i])));
// 	}
// 	else
// 	{
// 		new->type = FILE_IN;
// 		new->content[0] = ft_strdup(s[++**i]);
// 	}
// 	new->content[1] = NULL;
// 	return (0);
// }

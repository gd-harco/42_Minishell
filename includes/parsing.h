/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:44:55 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/31 10:20:31 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"

//-----------------FUNCTION-----------------//

//################# PATH.C #################//
char	**get_path(char **envp);
char	**path_arg_cat(char **src, char *root_arg);
char	*process(char *str, char **path, int ind);

//################# TOKEN.C #################//
t_token	*get_token(t_var *var);
t_token	*token_init(t_var *var);
void	token_add_back(t_token **token, t_token *new);

//################# TOKEN_CHECK.C################# //
bool	already_cmd(t_token *t_new, t_token *tmp);
void	token_arg(t_var *var);
bool	var_init(t_var *var, t_quote *quote);
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
bool	is_env_in(t_var var, int j);
bool	is_metachar(char c);
char	*ft_trunc(char *str, int start, char c);

//---------------TOKEN_ENV_VAR.C---------------//
void	env_arg(t_var *var, t_varenv *v_e);

//---------------TOKEN_ENV_VAR.C---------------//
bool	is_redirect_in(char *str);
t_token	*get_recutoken(t_var *var);
char	*ft_split_redirect(char **str);

#endif

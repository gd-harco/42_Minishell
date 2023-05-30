/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:44:55 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/30 10:48:32 by tdutel           ###   ########.fr       */
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

//################# TOKEN_CHECK.C################# //
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

#endif

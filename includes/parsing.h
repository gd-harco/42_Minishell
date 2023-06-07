/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:44:55 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/07 10:50:29 by tdutel           ###   ########.fr       */
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

//-----------------QUOTES.C----------------//
void	quote_manager(t_var *var, t_varenv *v_e);

char	*ft_truncstr(t_var var, t_varenv v_e, int start, char *c);

//################# TOKEN.C #################//
t_token	*get_token_list(t_var *var);
// void	struct_clear(t_var *var);
void	free_var(t_var *var);
//################# TOKEN_CHECK.C################# //
bool	already_cmd(t_token *t_new, t_token *tmp);
void	token_arg(t_var *var);
int		ft_nb_pipe(char *str);

//---------------TOKEN_CMD_FCT.C---------------//
void	token_builtin(t_var *var);
void	token_cmd(t_var *var);
bool	is_env_in(t_var var, int j);
bool	is_env_in_quote(t_var var, int j);
bool	is_metachar(char c);
int		is_quote_instr(char *str, int ind);
int		is_quote_in(char *str);
//---------------TOKEN_ENV_VAR.C---------------//
void	env_arg(t_var *var, t_varenv *v_e);

//---------------TOKEN_FCT.C---------------//
void	token_infile(t_var *var);
void	token_outfile(t_var *var);
t_token	*token_pipe(void);

//---------------TOKEN_UTILS.C---------------//
t_token	*token_last(t_token *token);
void	token_add_back(t_token **token, t_token *new);
void	token_clear(t_token *tkn);

//-----------------UTILS.C-----------------//
bool	var_init(t_var *var);
bool	is_builtin(char *str);
bool	has_in_out(char **s, int j);
char	*check_var(t_var *var, t_varenv *v_e);
char	*ft_trunc(char *str, int start, char c);

//-----------------UTILS2.C----------------//
char	*ft_space_str(t_var *var);
char	*ft_strjoinsp(char *s1, char *s2);
char	*ft_freestrjoin(char *s1, char *s2);
char	*ft_free_process(char *to_free, char *to_return);

// bool	already_pipe(t_token t_new);
// char	*ft_truncstr(char *str, int start, char *c);
// char	*trunc_rest(char *str, int start, char *c);

#endif

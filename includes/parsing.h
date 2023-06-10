/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:44:55 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/09 16:23:56 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"

//#################### FUNCTION ####################//
//-------------------- FUNCTION --------------------//
/*
*/
//#################### PATH.C ####################//
char	**get_path(char **envp);
char	*process(char *str, char **path, int ind);
//-------------------- PATH.C --------------------//
/*
*/
//#################### QUOTES_ENV.C ####################//
void	quote_env(char *str_tmp, t_var *var, t_varenv *v_e);
//-------------------- QUOTES_ENV.C --------------------//
/*
*/
//#################### QUOTES_UTILS.C ####################//
void	free_quote(t_var_quote *v_q);
char	*ft_reload_dup(char *str, t_var *var);
char	*ft_substrvar(char const *s, unsigned int start, size_t len, t_var var);
//-------------------- quotes_utils.c --------------------//
/*
*/
//#################### QUOTES.C ####################//
void	quote_manager(t_var *var, t_varenv *v_e);
//-------------------- QUOTES.C --------------------//
/*
*/
//#################### TOKEN_CHECK.C ####################//
bool	already_cmd(t_token *t_new, t_token *tmp);
void	token_arg(t_var *var);
int		ft_nb_pipe(char *str);
//-------------------- TOKEN_CHECK.C --------------------//
/*
*/
//#################### TOKEN_CMD_FCT.C ####################//
void	token_builtin(t_var *var);
void	token_cmd(t_var *var);
//-------------------- TOKEN_CMD_FCT.C --------------------//
/*
*/
//#################### TOKEN_ENV_VAR.C ####################//
void	env_arg(t_var *var, t_varenv *v_e);
//-------------------- TOKEN_ENV_VAR.C --------------------//
/*
*/
//#################### TOKEN_FCT.C ####################//
void	token_infile(t_var *var);
void	token_outfile(t_var *var);
t_token	*token_pipe(void);
//-------------------- TOKEN_FCT.C --------------------//
/*
*/
//#################### TOKEN_IS_IN.C ####################//
bool	is_env_in(t_var var, int j);
bool	is_env_in_str(char *str);
int		is_quote_in(char *str);
bool	is_metachar(char c);
//-------------------- TOKEN_IS_IN.C --------------------//
/*
*/
//#################### TOKEN_UTILS.C ####################//
t_token	*token_last(t_token *token);
void	token_add_back(t_token **token, t_token *new);
void	token_clear(t_token *tkn);
//-------------------- TOKEN_UTILS.C --------------------//
/*
*/
//#################### TOKEN.C ####################//
t_token	*get_token_list(t_var *var);
// void	struct_clear(t_var *var);
void	free_var(t_var *var);
//-------------------- TOKEN.C --------------------//
/*
*/
//#################### UTILS_JOIN.C ####################//
char	*ft_strjoinsp(char *s1, char *s2, int n);
//-------------------- UTILS_JOIN.C --------------------//
/*
*/
//#################### UTILS.C ####################//		
bool	var_init(t_var *var);
bool	is_builtin(char *str);
bool	has_in_out(char **s, int j);
char	*check_var(t_var *var, t_varenv *v_e);				
char	*ft_free_process(char *to_free, char *to_return);
//-------------------- UTILS.C --------------------//
/*
*/
//#################### UTILS2.C ####################//
char	*ft_space_str(t_var *var);
char	*ft_free_process(char *to_free, char *to_return);
//-------------------- UTILS2.C --------------------//

char	*ft_trunc(char *str, int start, char *c, t_var var);
// bool	already_pipe(t_token t_new);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:57:11 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/03 12:49:20 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "struct.h"
# define HD_PROMPT "heredoc> "
# define IO_FAILURE 42

//-----------------FUNCTION-----------------//

//########### EXECUTION.C ###########//
void	master_exec(t_minishell *minishell_data);

//########### HERE_DOC.C ###########//
int		*get_here_doc_fd(t_token *token_list);

//########### TRANSLATE.C ###########//
t_cmd	*get_cmd_data(t_exec *exec_data);

//########### IO_HANDLING.C ###########//
void	get_cmd_io(t_token *f_token, t_cmd cmd, t_exec *exec_data);

#endif

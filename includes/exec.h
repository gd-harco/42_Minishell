/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:57:11 by gd-harco          #+#    #+#             */
/*   Updated: 2023/06/01 14:13:48 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "struct.h"

//-----------------FUNCTION-----------------//

//########### EXECUTION.C ###########//
void		master_exec(t_minishell *minishell_data);

//########### HERE_DOC.C ###########//
t_here_doc	*get_here_doc_data(t_token *token_list);

#endif

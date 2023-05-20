/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:57:11 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/20 10:19:17 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H


# include "struct.h"

//-----------------FUNCTION-----------------//

//########### EXECUTION.C ###########//
void	master_exec(t_minishell *minishell_data);

//########### GET_ITEM_NB.C ###########//
int		get_nb_cmd(t_token *token);
int		get_nb_here_doc(t_token *token);

//########### HERE_DOC.C ###########//
void	process_here_doc(t_exec *data);

//########### COMMAND.C ###########//
void	fill_cmd(t_exec *data);

#endif

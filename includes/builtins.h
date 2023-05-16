/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:38:51 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/16 11:57:16 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//-----------------FUNCTIONS-----------------//

void	echo(char **str, bool n, int fd_out);
void	pwd(void);
void	unset(char **str);
void	env(char **envp);

#endif

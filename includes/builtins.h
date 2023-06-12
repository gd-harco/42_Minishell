/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:38:51 by gd-harco          #+#    #+#             */
/*   Updated: 2023/05/16 12:30:50 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "struct.h"
//-----------------FUNCTIONS-----------------//

void	echo(char **argv);
void	cd(char **argv, t_exec *exec_data);
void	pwd(void);
//void	export(char **argv, char **envp);
//void	unset(char **argv, char **envp);
//void	env(char **envp);
//void	exit_shell(int status, void **things_to_free);

#endif

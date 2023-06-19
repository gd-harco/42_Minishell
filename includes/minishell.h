/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:10:06 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/30 10:46:38 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define EXIT_EOF 101
//-----------------INCLUDES-----------------//

//########### PERSONAL LIB HEADERS ##########//

# include "../lib/libft/includes/libft.h"

//########### PROJECT SPECIFICS HEADERS ##########//

# include "builtins.h"
# include "exec.h"
# include "parsing.h"

//########### SYSTEM LIB HEADERS ##########//

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

//-----------------FUNCTION-----------------//
//################# PROMPT.C #################//
char	*get_user_input(void);

# define ROCKET_LOGO "\033[0;31m\n\033[2JBienvenue dans le Minishell de la Team Rocket!\n\n##################################\n\
####################################,\n\
######################################\n\
######################################,\n\
###########               #############\n\
###########               #############\n\
######################################\n\
#####################################*\n\
####################################\n\
#################################/\n\
#################################/\n\
###########           #############\n\
###########            *############\n\
###########              ############.\n\
###########               #############\n\n\033[0m"

#endif

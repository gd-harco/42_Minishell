#ifndef SIG_H
# define SIG_H

# include <signal.h>
# include "struct.h"

typedef struct s_sig
{
	struct sigaction	*int_prompt;
	struct sigaction	*int_exec;
	struct sigaction	*quit_prompt;
	struct sigaction	*quit_exec;
}	t_sig;

void	init_sigaction(t_sig *sig);
void	sig_c_exec(int sig);
void	sig_c_prompt(int sig);
void	sig_d_int(int sig);

#endif

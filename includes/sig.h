#ifndef SIG_H
# define SIG_H

# include <signal.h>
# include "struct.h"

typedef struct s_sig
{
	struct sigaction	*c_prompt;
	struct sigaction	*c_exec;
	struct sigaction	*d_int;
}	t_sig;

void	init_sigaction(t_sig *sig);
void	sig_c_exec(int sig);
void	sig_c_prompt(int sig);
void	sig_d_int(int sig);

#endif

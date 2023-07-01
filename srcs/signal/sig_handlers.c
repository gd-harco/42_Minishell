#include "minishell.h"

void	sig_c_prompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	printf("sig_c_prompt\n");
}

void	sig_c_exec(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	printf("sig_c_exec\n");
}

void	sig_d_int(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	printf("sig_d_int\n");
}

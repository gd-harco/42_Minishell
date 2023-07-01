#include "minishell.h"

static void	init_c_prompt_sig(struct sigaction *to_init);
static void	init_c_exec_sig(struct sigaction *to_init);
static void	init_d_sig(struct sigaction *to_init);

void	init_sigaction(t_sig *sig)
{
	sig->c_prompt = malloc(sizeof(struct sigaction));
	sig->c_exec = malloc(sizeof(struct sigaction));
	sig->d_int = malloc(sizeof(struct sigaction));
	init_c_exec_sig(sig->c_exec);
	init_c_prompt_sig(sig->c_prompt);
	init_d_sig(sig->d_int);
}

static void	init_d_sig(struct sigaction *to_init)
{
	to_init->sa_handler = sig_d_int;
	sigemptyset(&to_init->sa_mask);
	to_init->sa_flags = 0;
}

static void	init_c_exec_sig(struct sigaction *to_init)
{
	to_init->sa_handler = sig_c_exec;
	sigemptyset(&to_init->sa_mask);
	to_init->sa_flags = 0;
}

static void	init_c_prompt_sig(struct sigaction *to_init)
{
	to_init->sa_handler = sig_c_prompt;
	sigemptyset(&to_init->sa_mask);
	to_init->sa_flags = 0;
}

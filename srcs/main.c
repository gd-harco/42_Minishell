/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:09:31 by tdutel            #+#    #+#             */
/*   Updated: 2023/07/01 17:11:49 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_shell_env(char **envp);
void	init_secret_array(t_minishell *data, bool secret);

//TODO man stat = recuperer la valeur de retour


int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;
	t_var		var;
	bool		secret;

//TODO get rid of the secret bool, replace it with a define EASTER_EGG in minishell.h
//TODO bien verifier que la commande envoye est bien un path et pas juste un binaire
	if (argc == 1)
		secret = true;
	else
		secret = false;
	(void)argv;
	data.sig = malloc(sizeof(t_sig));
	init_sigaction(data.sig);
	sigaction(SIGINT, data.sig->int_prompt, data.sig->int_exec);
	sigaction(SIGQUIT, data.sig->quit_prompt, data.sig->quit_exec);
	init_secret_array(&data, secret);
	data.envp = init_shell_env(envp);
	var.env_cpy = data.envp;
	printf(ROCKET_LOGO);
	var.str_in = get_user_input();
	var.str = ft_space_str(&var);
	while (42)
	{
		if (!var.str_in)
		{
			clear_history();
			ft_free_secure(&var.str_in);
			ft_free_secure(&var.str);
			ft_free_array((void **)data.envp);
			ft_printf("exit\n");
			exit(EXIT_EOF);
		}
		if (var.str)
		{
			if (var.str_in && *(var.str_in))
				add_history(var.str_in);
			data.token_list = get_token_list(&var);
			free_var(&var);
			if (data.token_list)
				master_exec(&data);
			token_clear(&data.token_list);
			// exit (0);
		}
		var.str_in = get_user_input();
		var.str = ft_space_str(&var);
	}
}

char	**init_shell_env(char **envp)
{
	char	**new_envp;
	char	*pwd;
	char	*old_pwd;
	char	*shlvl;

	if (envp[0])
	{
		new_envp = (char **)ft_array_dup((void **)envp, false, true);
	}
	else
	{
		new_envp = ft_calloc(5, sizeof (char *));
		pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
		new_envp[0] = pwd;
		old_pwd = ft_strdup("OLDPWD");
		new_envp[1] = old_pwd;
		shlvl = ft_strdup("SHLVL=1");
		new_envp[2] = shlvl;
		new_envp[3] = ft_strdup("PATH=");
	}
	return (new_envp);
}

void	init_secret_array(t_minishell *data, bool secret)
{
	if (secret == false)
		data->secret_array = NULL;
	else
	{
		data->secret_array = ft_calloc(3, sizeof(char *));
		data->secret_array[0] = ft_strdup("/usr/bin/eog");
		data->secret_array[1] = ft_strjoin(
				getcwd(NULL, 0), "/assets/secret.gif");
	}
}

void	free_var(t_var *var)
{
	ft_free_secure(&var->str_in);
	ft_free_secure(&var->str);
	ft_free_split_secure(&var->s);
	ft_free_split_secure(&var->spipe);
	// token_clear(&var->new_tkn);
}

// cat -e Makefile |pwd >out33

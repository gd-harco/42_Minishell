/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:09:31 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/27 12:59:24 by tdutel           ###   ########.fr       */
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

//TODO bien verifier que la commande envoye est bien un path et pas juste un binaire
	if (argc == 1)
		secret = true;
	else
		secret = false;
	(void)argv;
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
			rl_clear_history();
			free(var.str_in);
			free(var.str);
			ft_free_array((void **)data.envp);
			ft_printf("exit\n");
			exit(EXIT_EOF);
		}
		if (var.str_in && *(var.str_in))
			add_history(var.str_in);
		data.token_list = get_token_list(&var);
		if (data.token_list)
			master_exec(&data);
		free_var(&var);
		exit (0);
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
		new_envp = ft_calloc(4, sizeof (char *));
		pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
		new_envp[0] = pwd;
		old_pwd = ft_strdup("OLDPWD");
		new_envp[1] = old_pwd;
		shlvl = ft_strdup("SHLVL=1");
		new_envp[2] = shlvl;
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
	if (var->str_in)
		free(var->str_in);
	if (var->str)
		free(var->str);
	if (var->s)
		ft_free_split((void *)var->s);
	if (var->spipe)
		ft_free_split((void *)var->spipe);
	if (var->new_tkn)
		token_clear(var->new_tkn);
}

	// if (var->env)
	// 	free(var->env);

// void	free_var(t_var *var)
// {
// 	if (var->s)
// 		ft_free_array((void *)var->s);
// 	if (var->spipe)
// 		ft_free_array((void *)var->spipe);
// 	if (var->s_p)
// 		free(var->s_p);
// 	if (var->arg)
// 		free(var->arg);
// 	// if (var->env)
// 	// 	free(var->env);
// 	// if (var->new_tkn)
// 	// 	token_clear(&var->new_tkn, free);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-harco <gd-harco@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:09:31 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/16 14:47:06 by gd-harco         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*data;
	char		*str;
	t_token		*tmp;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_minishell));
	data->envp = envp;
	printf(ROCKET_LOGO);
	str = get_user_input();
	while (42)
	{
		add_history(str);
		data->token_list = get_token(str, envp);
		tmp = data->token_list;
		while (tmp)
		{
			ft_printf("\n\nTOKEN\n");
			ft_printf("content[0] : %s\n", tmp->content[0]);
			ft_printf("content[1] : %s\n", tmp->content[1]);
			ft_printf("type : %i\n", tmp->type);
			ft_printf("next : %p\n", tmp->next);
			tmp = tmp->next;
		}
		// first_elem(str, envp);
		str = get_user_input();
	}
	return (0);
}

// str = "< infile grep if | wc -l > outfile"
// str = "ls -la | cat -e > out"
// str = "echo -n lalalou > out"


// s	[0]	 	 [1]	   [2]		[3]	   [4]  [5]  	[6]    [7]	  [8]	   [9]
// s = "<\0" "infile\0" "grep\0" "if\0" "|\0" "wc\0" "-l\0" ">\0" "outfile\0" "NULL"



// s	[0]	 	 [1]	   [2]		[3]	   [4]  [5]
// s = "echo"	 "-n"	 "lalalou"  ">"   "out" "NULL"



// t_token	*first_elem(char *str, char **envp)
// {
// 	t_token	*new;
// 	char	**s;
// 	int		i;
// 	char	**path;
//     char	*s_p;
// 	char	*arg;

// 	arg = NULL;
// 	s = ft_split(str, ' ');
// 	i = 0;
// 	new = malloc(sizeof(t_token));
// 	// if (s[0][0] == '<')
// 	// {
// 	// 	new->content = malloc(sizeof(char *) * 2);
// 	// 	if(!new->content)
// 	// 		return (NULL);
// 	// 	new->content[0] = ft_strdup(s[0]);
// 	// 	new->content[1] = NULL;
// 	// 	if (s[0][1] == '<')
// 	// 		new->type = DOUBLE_CHEVRON_IN;
// 	// 	else
// 	// 		new->type = CHEVRON_IN;
// 	// }
// 	if (is_builtin(s[0]) == true)
// 	{
// 		while (s[i + 1] && s[i + 1][0] == '-' )
// 		{
// 			arg = ft_strjoin(arg, s[i + 1]);
// 			i++;
// 		}
// 		new->content = malloc(sizeof(char *) * 2);
// 		if(!new->content)
// 			return (NULL);
// 		new->content[0] = ft_strdup(s[0]);
// 		new->content[1] = ft_strdup(arg);
// 		new->type = BUILTIN;
// 	}
// 	else
// 	{
// 		while (s[i + 1] && s[i + 1][0] == '-' )
// 		{
// 			arg = ft_strjoin(arg, s[i + 1]);
// 			i++;
// 		}
// 		path = get_path(envp);
//         s_p = process(str, path);
// 		new->content = malloc(sizeof(char *) * (2));
// 		if (!new->content)
// 			return (NULL);
// 		new->content[0] = ft_strdup(s_p);
// 		new->content[1] = ft_strdup(arg);
// 		new->type = CMD;
// 	}
// 	new->next = NULL;
// 	return (new);
// }


// t_token	*other_elem(char *str, char **envp, int	index)
// {
// 	t_token	*new;
// 	char	**s;
// 	int		i;
// 	char	**path;
//     char	*s_p;
// 	char	*arg;

// 	s = ft_split(str, ' ');
// 	new = malloc(sizeof(t_token));
// 	while(s[index] && s[index][0] == '-')
// 		index++;
// 	// if (s[index][0] == '>')
// 	// {
// 	// 	new->content = malloc(sizeof(char *) * 2);
// 	// 	if(!new->content)
// 	// 		return (NULL);
// 	// 	new->content[0] = ft_strdup(s[0]);
// 	// 	new->content[1] = NULL;
// 	// 	if (s[index][1] == '>')
// 	// 		new->type = DOUBLE_CHEVRON_IN;
// 	// 	else
// 	// 		new->type = CHEVRON_IN;
// 	// }
// 	if (is_builtin(s[index]) == true)
// 	{
// 		while (s[index + i + 1] && s[index + i + 1][0] == '-' )
// 		{
// 			arg = ft_strjoin(arg, s[index + i + 1]);
// 			i++;
// 		}
// 		new->content = malloc(sizeof(char *) * 2);
// 		if (!new->content)
// 			return (NULL);
// 		new->content[0] = ft_strdup(s[index]);
// 		new->content[1] = ft_strdup(arg);
// 		new->type = BUILTIN;
// 	}
// 	else
// 	{
// 		while (s[index + i + 1] && s[index + i + 1][0] == '-' )
// 		{
// 			arg = ft_strjoin(arg, s[index + i + 1]);
// 			i++;
// 		}
// 		path = get_path(envp);
// 		s_p = process(str, path);
// 		new->content = malloc(sizeof(char *) * (2));
// 		if (!new->content)
// 			return (NULL);
// 		new->content[0] = ft_strdup(s_p);
// 		new->content[1] = ft_strdup(arg);
// 		new->type = CMD;
// 	}
// 	new->next = NULL;
// 	return (new);

// }

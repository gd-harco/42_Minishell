/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:09:31 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/12 16:52:47 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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




















int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_token	*tkn;
	t_token	*tmp;

	(void)argc;
	(void)argv;
	tkn = malloc(sizeof(t_token *));
	str = readline("Minishell$");
	while(42)
	{
		add_history(str);
		tkn = get_token(str, envp);
		tmp = tkn;
		while (tmp->next)
		{
			ft_printf("TOKEN\n");
			ft_printf("content[0] : %s\n", tmp->content[0]);
			ft_printf("content[1] : %s\n", tmp->content[1]);
			ft_printf("type : %i\n", tmp->type);
			ft_printf("next : %p\n", tmp->next);
			tmp = tmp->next;
		}
		// first_elem(str, envp);
		str = readline("Minishell$");
	}
	return (0);
}

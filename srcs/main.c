/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:09:31 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/11 12:39:59 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	is_builtin(char *str);
static bool is_word(char *str, char *str2);

// str = "< infile grep if | wc -l > outfile"
// str = "ls -la | cat -e > out"
// str = "echo -n lalalou > out"


// s	[0]	 	 [1]	   [2]		[3]	   [4]  [5]  	[6]    [7]	  [8]	   [9]
// s = "<\0" "infile\0" "grep\0" "if\0" "|\0" "wc\0" "-l\0" ">\0" "outfile\0" "NULL"



// s	[0]	 	 [1]	   [2]		[3]	   [4]  [5]  
// s = "echo"	 "-n"	 "lalalou"  ">"   "out" "NULL"


t_token	*first_elem(char *str, char **envp)
{
	t_token	*new;
	char	**s;
	int		i;
	int		j;
	char	**path;
    char	*s_p;

	s = ft_split(str, ' ');
	i = 0;
	new = malloc(sizeof(t_token));
	if (s[0][0] == '<')
	{
		new->content = malloc(sizeof(char *) * 2);
		if(!new->content)
			return (NULL);
		new->content[0] = strdup(s[0]);
		new->content[1] = NULL;
		if (s[0][1] == '<')
			new->type = DOUBLE_CHEVRON_IN;
		else
			new->type = CHEVRON_IN;
	}
	else if (is_builtin(s[0]) == true)
	{
		while (s[i + 1][0] == '-' )
			i++;
		j = 0;
		new->content = malloc(sizeof(char *) * (2 + i));
		if(!new->content)
			return (NULL);
		new->content[0] = strdup(s[0]);
		while (++j <= i)
			new->content[j] = strdup(s[j]);
		new->content[j] = NULL;
		new->type = BUILTIN;
	}
	else
	{
		while (s[i + 1][0] == '-' )
			i++;
		j = 0;
		path = get_path(envp);
        s_p = process(str, path);
        if (!s_p)
            return(NULL);
		new->content = malloc(sizeof(char *) * (2 + i));
		if (!new->content)
			return (NULL);
		new->content[0] = ft_strdup(s_p);
		while (++j <= i)
			new->content[j] = strdup(s[j]);
		new->content = NULL;
		new->type = STRING;
	}
	new->next = NULL;
	return (new);
}

static bool is_word(char *str, char *str2)
{
	int i;
	while (str[i] || str2[i])
	{
		if (str[i] != str2[i])
			return (false);
		i++;
	}
	if (str[i] == str2[i])
		return (true);
	else
		return (false);
}

static bool	is_builtin(char *str)
{
	if (is_word(str, "cd") == true || is_word(str, "pwd") == true 
		|| is_word(str, "echo") ==true || is_word(str, "export") == true
			|| is_word(str, "unset") == true || is_word(str, "env") == true 
				|| is_word(str, "exit") == true )
		return (true);
	else
		return (false);
}

int main(int argc, char **argv, char **envp)
{
    char    *str;
    int     i;

    (void)argc;
    (void)argv;
    i = 0;
    str = readline("Minishell$");
	while(i < 5)
	{
		add_history(str);
        first_elem(str, envp);
        i++;
        str = readline("Minishell$");
	}
	return (0);
}

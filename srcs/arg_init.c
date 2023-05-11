/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:59:10 by tdutel            #+#    #+#             */
/*   Updated: 2023/05/11 11:00:17 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_isstring(char *str);
void	token_add_back(t_token **token, char *str);
t_token	*token_last(t_token *token);
bool	is_builtin(char *str);
bool is_word(char *str, char *str2);

t_token	*get_token(char *str, char **envp)
{
	char	**s;
	t_token	*new;
	int		i;

	(void)envp;
	s = ft_split(str, ' ');
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->next = NULL;
	i = 0;
	if (s[0][0] == '<')
	{
		new->content[0] = malloc(sizeof(char) * 2);
		new->content[0][0] = '<';
		if (s[0][1] == '<')
		{
			new->content[0][1] = '<';
			new->type = DOUBLE_CHEVRON_IN;
		}
		else
			new->type = CHEVRON_IN;
	}
	else
	{
		while(ft_isstring(s[i]) == true)
			token_add_back(&new, s[i]);
	}
	return (new);
}

bool	ft_isstring(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i] == false))
			return (false);
		i++;
	}
	return (true);
}

t_token	*token_last(t_token *token)
{
	while (token && token->next)
		token = token->next;
	return (token);
}


void	token_add_back(t_token **token, char *str)
{
	t_token	*tail;
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->next = NULL;
	new->content = malloc(sizeof(char) * (ft_strlen(str) + 1));
	new->content[0] = ft_strdup(str);
	if (ft_isstring(str) == true)
		new->type = STRING;
	if (str[0] == '|')
		new->type = PIPE;
	else if (str[0] == '<' && str[1] == '<')
		new->type = DOUBLE_CHEVRON_IN;
	else if (str[0] == '<')
		new->type = CHEVRON_IN;
	else if (is_builtin(str) == true)
		new->type = BUILTIN;
	if (!token)
		return ;
	if (*token)
	{
		tail = token_last(*token);
		tail->next = new;
	}
	else
		*token = new;
}

bool	is_builtin(char *str)
{
	if (is_word(str, "cd") == true || is_word(str, "pwd") == true 
		|| is_word(str, "echo") ==true || is_word(str, "export") == true
			|| is_word(str, "unset") == true || is_word(str, "env") == true 
				|| is_word(str, "exit") == true )
		return (true);
	else
		return (false);
}

bool is_word(char *str, char *str2)
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

int main(int argc, char **argv, char **envp)
{
    char    *str;
	char	**s;
    int     i;

    (void)argc;
    (void)argv;
    i = 0;
    str = readline("");
	s = ft_split(str, ' ');
	while(s[i] != NULL)
	{
		get_token(s[i], envp);
	}
    while (i < 5 ) //detect SIGINT ou SIGTERM ?
    {
        add_history(str);
        get_token(str, envp);
        // echo_cmd(str);
        // cd_cmd(str);
        i++;
        printf("Minishell$ ");
        str = readline("");
    }
    return (0);
}

// t_token *cmd_init(char *str, char **envp)
// {
//     t_token *t_new;
//     char **s;
//     char **path;
//     char *s_p;

//     s = ft_split(str, ' ');
//     t_new = malloc(sizeof(t_token));
//     if (!t_new)
//         return(NULL);
//     t_new->next = NULL;
//     if (s[0][0] != '<')
//     {
//         path = get_path(envp);
//         s_p = process(str, path);
//         if (!s_p)
//             return(NULL);
//         t_new->content = malloc(sizeof (char *) * 2);
//         t_new->content[0] = malloc(sizeof(char *) * (ft_strlen(s_p) + 1));
//         t_new->content[0] = ft_strdup(s_p);
//         t_new->content[1] = NULL;
//     }
//     printf("%s\n", s_p);
    
//     return (t_new);
// }

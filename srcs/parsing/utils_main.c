/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:45:08 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/12 16:13:01 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_var(t_var *var)
{
	if (var->str_in)
		free(var->str_in);
	if (var->str)
		free(var->str);
	if (var->s)
		ft_free_array((void *)var->s);
	if (var->spipe)
		ft_free_array((void *)var->spipe);
	if (var->path)
		ft_free_array((void *)var->path);
	if (var->s_p)
		free(var->s_p);
	// if (var->envp)
	if (var->arg)
		free(var->arg);
	if (var->env)
		free(var->env);
	if (var->new_tkn)
		token_clear(var->new_tkn);
}

void	free_data(t_minishell *data)
{
	if (data->envp)
		ft_free_array((void *)data->envp);
	if (data->token_list)
		token_clear(data->token_list);
}

t_list	*ft_lstcharnew(char *content);

t_list	*lst_env(char **envp)
{
	t_list	*lst;
	t_list	*tmp;
	int		i;
	size_t	debug_len;

	i = 0;
	debug_len = ft_array_length((void **)envp);
	lst = ft_calloc(sizeof(t_list), 1);
	if (!lst)
		return (NULL);
	tmp = ft_calloc(sizeof(t_list), 1);
	if (!tmp)
		return (NULL);
	lst = ft_lstnew((char *)envp[i]);
	while (envp[++i])
	{
		tmp = ft_lstnew((void *)envp[i]);
		printf("%s\n", (char *)tmp->content);
		ft_lstadd_back(&lst, tmp);
		printf("%s\n", (char *)lst->content);
	}
	(void)debug_len;
	return (lst);
}

// t_list	*ft_lstcharnew(char *content)
// {
// 	t_list	*new;

// 	new = malloc(sizeof(t_list));
// 	if (!new)
// 		return (NULL);
// 	new->next = NULL;
// 	new->content = ft_strdup(content);
// 	return (new);
// }


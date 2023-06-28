/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:46:03 by tdutel            #+#    #+#             */
/*   Updated: 2023/06/28 14:02:46 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_secure(char **elem)
{
	if (*elem != NULL)
		free(*elem);
	*elem = NULL;
}


void	ft_free_split_secure(char **splitted_element)
{
	size_t	i;

	if (splitted_element == NULL)
		return ;
	i = 0;
	while ((splitted_element)[i])
	{
		free((splitted_element)[i]);
		i++;
		// splitted_element[i++] = NULL;
	}
	free(splitted_element);
	splitted_element = NULL;
}

void	ft_free_split_secure2(char ***splitted_element)
{
	size_t	i;

	if (*splitted_element == NULL)
		return ;
	i = 0;
	while ((*splitted_element)[i])
	{
		ft_free_secure((splitted_element)[i]);
		i++;
		// splitted_element[i++] = NULL;
	}
	ft_free_secure(*splitted_element);
	splitted_element = NULL;
}

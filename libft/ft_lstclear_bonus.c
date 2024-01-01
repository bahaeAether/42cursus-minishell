/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baboulou <baboulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:49:14 by hnaama            #+#    #+#             */
/*   Updated: 2023/12/27 11:44:34 by baboulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*l_tmp;

	tmp = *lst;
	while (tmp)
	{
		del(tmp->content);
		l_tmp = tmp;
		tmp = tmp->next;
		free (l_tmp);
	}
	*lst = NULL;
}

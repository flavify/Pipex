/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 07:03:04 by fvoicu            #+#    #+#             */
/*   Updated: 2023/05/21 15:55:36 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstadd_back(t_list **list, t_list *new)
{
	t_list	*temp;

	if ((!list && !*list) || !new)
		return ;
	if (*list == NULL)
		*list = new;
	else
	{
		temp = ft_lstlast(*list);
		temp->next = new;
	}	
}

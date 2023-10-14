/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fv_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 02:34:15 by fvoicu            #+#    #+#             */
/*   Updated: 2023/10/14 02:44:15 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fv_free_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free (array[i]);
			++i;
		}
	}
	free (array);
}

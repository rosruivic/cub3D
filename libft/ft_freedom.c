/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freedom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:31:02 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/03/21 19:53:35 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_freedom(char **matrix)
{
	size_t	i;

	i = 0;
	if (matrix)
	{
		while (matrix[i])
		{
			ft_bzero(matrix[i], ft_strlen(matrix[i]));
			free(matrix[i]);
			matrix[i] = NULL;
			i++;
		}
		free(matrix);
		matrix = NULL;
	}
	return (matrix);
}

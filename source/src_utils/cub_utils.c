/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:30:35 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/03/22 18:30:36 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_delete_nl(char *str)
{
	int		len;
	char	*tmp;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (str[len - 1] == '\n')
	{
		tmp = ft_substr(str, 0, len - 1);
		ft_free_null_void_return(&str);
		return (tmp);
	}
	return (str);
}

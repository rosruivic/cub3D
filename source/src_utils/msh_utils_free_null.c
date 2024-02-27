#include "cub3D.h"

void	ft_free_null_void_return(char **str)
{
	if (*str != NULL)
	{
		ft_bzero(*str, ft_strlen(*str));
		free(*str);
		*str = NULL;
	}
}

char	*ft_free_null_no_void_return(char *str)
{
	if (str != NULL)
	{
		ft_bzero(str, ft_strlen(str));
		free(str);
		str = NULL;
	}
	return (str);
}

char	**ft_freedom_null(char **matrix)
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

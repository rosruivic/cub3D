//#include "../includes/cub3D.h"
//#include "includes/cub3D.h"
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
		free(str);
		return(tmp);
	}
	return (str);
}

void	ft_print_matrix(char **mtx)
{
	int	i;

	i = -1;
	if (!mtx)
		return ;
	while (++i < ft_matrix_len(mtx))
		ft_printf("%s\n", mtx[i]);
	ft_printf("\n");
}

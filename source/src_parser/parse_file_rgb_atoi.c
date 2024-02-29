#include "cub3D.h"

void	ft_rgb_atoi(t_data *d, char camp, char **color)
{
	int	i;

	i = -1;
	if (camp == 'C')
	{
		d->rgb_c = ft_calloc(3, sizeof(int));
		if (!d->rgb_c)
			ft_error_pull_data(d, ERROR_MALLOC, color);
	}
	else if (camp == 'F')
	{
		d->rgb_f = ft_calloc(3, sizeof(int));
		if (!d->rgb_f)
			ft_error_pull_data(d, ERROR_MALLOC, color);
	}
	while (++i < 3)
	{
		if ((ft_strlen(color[i]) > 3 || !ft_is_str_digits(color[i]))
			|| (ft_atoi(color[i]) > 255 || ft_atoi(color[i]) < 0))
			ft_error_pull_data(d, ERROR_INVALID_RGB_RANGE, color);
		if (camp == 'C')
			d->rgb_c[i] = ft_atoi(color[i]);
		else if (camp == 'F')
			d->rgb_f[i] = ft_atoi(color[i]);
	}
}

/* El tipo uint32_t es un tipo numérico entero sin signo que puede almacenar 
valores entre 0 y 4294967295. Cuando almacenas un valor hexadecimal en una 
variable uint32_t, estás almacenando el valor numérico que representa ese 
hexadecimal, no la representación de caracteres del hexadecimal.

Por ejemplo, si tienes el valor hexadecimal 0xFF, esto es equivalente al 
valor decimal 255. Si almacenas 0xFF en una variable uint32_t, la variable 
contendrá el valor 255, no la cadena de caracteres "FF".

Si quieres convertir los valores RGB a un valor uint32_t en formato hexadecimal, 
puedes hacerlo de la siguiente manera en C:

	#include <stdint.h>

	uint32_t rgb_to_hex(int r, int g, int b)
	{
	    return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
	}

	int main()
	{
	    uint32_t hex = rgb_to_hex(255, 0, 0);
	    printf("%X\n", hex);  // Output: FF0000
	    return 0;
	}


En este código, la función rgb_to_hex convierte los valores RGB a un valor 
uint32_t en formato hexadecimal. Los operadores de desplazamiento << se utilizan 
para mover los bits de los valores RGB a las posiciones correctas en el valor 
hexadecimal, y el operador | se utiliza para combinar estos valores. 
El operador & 0xFF se utiliza para asegurar que solo se utilicen los 8 bits 
menos significativos de cada valor RGB.
 */
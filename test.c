#include "fdf_lib.h"

void	f_add(int	***c)
{
	*c = malloc(sizeof(**c) * 2);
	(*c)[0] = malloc(sizeof(***c) * 2);
	(*c)[1] = malloc(sizeof(***c) * 2);
	(*c)[0][0] = 1;
	(*c)[0][1] = 2;
	(*c)[1][0] = 3;
	(*c)[1][1] = 4;

	// *c = malloc(sizeof(**c) * 2);
	// **c = malloc(sizeof(***c) * 2);
	// *(*c + 1) = malloc(sizeof(***c) * 2);
	// ***c = 1;
	// **(*c + 1) = 3;
	// *(**c + 1) = 2;
	// *(*(*c + 1) + 1) = 4;
}

int	main(void)
{
	int		a;
	float	d;
	int		b;

	a = 9;
	d = (float)a / 2;
	printf("%f\n", d);
}

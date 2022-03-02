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

void	funk2(float a[4])
{
	printf("%f\n", a[1]);
}

int	main(void)
{
	float xxyy[4];

	xxyy = (float [4]){0, 1, 2, 3};
	funk2(xxyy);
}

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
	int	a[2][2];
	int	**b;
	int *c;

	a[0][0] = 1;
	a[0][1] = 2;
	a[1][0] = 1;
	a[1][1] = 2;

	b = &a[0];
	// printf("%d\n", *(*b + 1));
	printf("%d\n", *c);
	printf("%d\n", a[0][0]);
}

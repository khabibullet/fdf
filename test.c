#include <mlx.h>
#include <math.h>
#include "fdf_lib.h"


void	f_add(int	**a)
{
	**a = malloc(sizeof(*a));
}

int main()
{
	int	*a;

	a = NULL;
	f_add(&a);
	*a = 13;
	printf("%d - %d\n", a[0], a[1]);
}

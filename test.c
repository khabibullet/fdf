#include "fdf_lib.h"

int	key_press(int keycode, t_mlx *gen)
{
	if (keycode == KEY_D)
		gen->pressed.d = 1;
	else if (keycode == KEY_A)
		gen->pressed.a = 1;
	else if (keycode == KEY_W)
		gen->pressed.w = 1;
	else if (keycode == KEY_S)
		gen->pressed.s = 1;
	else if (keycode == KEY_E)
		gen->pressed.e = 1;
	else if (keycode == KEY_Q)
		gen->pressed.q = 1;
	else if (keycode == KEY_P)
	{
		if (gen->proj_type == 1)
			gen->proj_type = 0;
		else if (gen->proj_type == 0)
			gen->proj_type = 1;
	}
	else if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	gen->shift[0] = gen->pressed.d - gen->pressed.a;
	gen->shift[1] = gen->pressed.w - gen->pressed.s;
	gen->shift[2] = gen->pressed.e - gen->pressed.q;
	return (0);
}

int	key_release(int keycode, t_mlx *gen)
{
	if (keycode == KEY_D)
		gen->pressed.d = 0;
	else if (keycode == KEY_A)
		gen->pressed.a = 0;
	else if (keycode == KEY_W)
		gen->pressed.w = 0;
	else if (keycode == KEY_S)
		gen->pressed.s = 0;
	else if (keycode == KEY_E)
		gen->pressed.e = 0;
	else if (keycode == KEY_Q)
		gen->pressed.q = 0;
	gen->shift[0] = gen->pressed.d - gen->pressed.a;
	gen->shift[1] = gen->pressed.w - gen->pressed.s;
	gen->shift[2] = gen->pressed.e - gen->pressed.q;
	return (0);
}

int	exit_hook(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

int	mouse_hook(int x2, int y2, t_mlx *gen)
{
	static int	flag;
	static int	x1;
	static int	y1;

	if (flag)
	{
		gen->angles[0] += ((float)(x2 - x1)) * gen->mouse_sens;
		gen->angles[1] += ((float)(y2 - y1)) * gen->mouse_sens;
		if (gen->angles[0] > 360)
			gen->angles[0] -= 360;
		if (gen->angles[0] < -360)
			gen->angles[0] += 360;
		if (gen->angles[1] > 360)
			gen->angles[1] -= 360;
		if (gen->angles[1] < -360)
			gen->angles[1] += 360;
	}
	x1 = x2;
	y1 = y2;
	flag = 1;
	return (0);
}

int	main_loop(t_mlx	*gen)
{
	printf("%f, %f, %f, %f, %d\n", gen->shift[0], gen->shift[1], gen->shift[2], gen->angles[0], gen->proj_type);
	usleep(16667);
	return (0);
}

int	main(void)
{
	t_mlx	gen;

	gen.foc = 0;
	gen.mouse_sens = 1;
	gen.angles[0] = 0;
	gen.angles[1] = 0;
	gen.proj_type = 0;
	gen.pressed = (t_keys){0};
	gen.mlx = mlx_init();
	gen.win = mlx_new_window(gen.mlx, 300, 300, "test");
	mlx_hook(gen.win, X_EVENT_KEY_PRESS, 0, &key_press, &gen);
	mlx_hook(gen.win, X_EVENT_KEY_RELEASE, 0, &key_release, &gen);
	mlx_hook(gen.win, X_EVENT_EXIT, 0, &exit_hook, &gen);
	mlx_hook(gen.win, X_EVENT_MOUSE_MOVE, 0, &mouse_hook, &gen);
	mlx_loop_hook(gen.mlx, &main_loop, &gen);
	mlx_loop(gen.mlx);
}

#include "fils_de_fer.h"

void	draw_line_high(t_mlx *mlx, t_pixel p0, t_pixel p1, int color)
{
	int	dx;
	int	dy;
	int	xi;
	int	delta;

	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	delta = (2 *dx) - dy;
	while (p0.y <= p1.y)
	{
		put_pixel(mlx, p0.x, (p0.y)++, color);
		if (delta > 0)
		{
			p0.x += xi;
			delta += (2 * (dx - dy));
		}
		else
			delta += 2 * dx;
	}
}

void	draw_line_low(t_mlx *mlx, t_pixel p0, t_pixel p1, int color)
{
	int	yi;
	int	dx;
	int	dy;
	int	delta;

	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	delta = (2 * dy) - dx;
	while (p0.x <= p1.x)
	{
		put_pixel(mlx, (p0.x)++, p0.y, color);
		if (delta > 0)
		{
			p0.y += yi;
			delta += (2 * (dy - dx));
		}
		else
			delta += 2 * dy;
	}
}

/**
 * - Optimized form of the Bresenham Line Algorithm
 */
void	draw_bresenham_line(t_mlx *mlx, t_pixel start, t_pixel end, int color)
{
	int	dx;
	int	dy;

	dx = abs(end.x - start.x);
	dy = abs(end.y - start.y);
	if (dy < dx)
	{
		if (start.x > end.x)
			draw_line_low(mlx, end, start, color);
		else
			draw_line_low(mlx, start, end, color);
	}
	else
	{
		if (start.y > end.y)
			draw_line_high(mlx, end, start, color);
		else
			draw_line_high(mlx, start, end, color);
	}
}

/**
 * - Initializes and calculates the angles for each perspective
 */
void	init_angles(t_map *map)
{
	map->angle = M_PI / 6;
	map->map_scale = 20.0;
}

// /**
//  * NOTE: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
//  * - Bresenham's algorithm in plain code
//  * - This is one of the implementation examples on considering a principle on
//  *	integer incremental error
//  */
// void	draw_bresenham_line(t_mlx *mlx, t_pixel start, t_pixel end, int color)
// {
// 	int	dx;
// 	int	dy;
// 	int	x_step;
// 	int	y_step;
// 	int	delta;
// 	int	delta2;

// 	dx = abs(end.x - start.x);
// 	dy = abs(end.y - start.y);
// 	x_step = (start.x < end.x) ? 1 : -1;
// 	y_step = (start.y < end.y) ? 1 : -1;
// 	delta = dx - dy;
// 	while (start.x != end.x || start.y != end.y)
// 	{
// 		put_pixel(mlx, start.x, start.y, color);
// 		delta2 = 2 * delta;
// 		if (delta2 > -dy)
// 		{
// 			delta -= dy;
// 			start.x += x_step;
// 		}
// 		if (delta2 < dx)
// 		{
// 			delta += dx;
// 			start.y += y_step;
// 		}
// 	}
// 	put_pixel(mlx, end.x, end.y, color); // draw the last point
// }

#include "fils_de_fer.h"

/**
 * - TODO: add reference and info, add calculations on centering the pixel value,
 * 	and scaling it properly, and then add the window of instructions (maybe)
 *
 * @param x the abscissa
 * @param y the ordinate
 * @param z the altitude
 * @param map data of rotations, scaling and offset
 */
t_pixel calc_isometric(t_map *map, int x, int y, int z)
{
	t_pixel	p;
	double	scale = map->map_scale;
	double	angle = map->iso_angle; // M_PI / 6

	// Convert to double for math
	double xd = (double)x;
	double yd = (double)y;
	double zd = (double)z * map->z_scale;

	// Apply rotation around X axis
	double y1 = yd * cos(map->rot_x) - zd * sin(map->rot_x);
	double z1 = yd * sin(map->rot_x) + zd * cos(map->rot_x);

	// Apply rotation around Y axis
	double x2 = xd * cos(map->rot_y) + z1 * sin(map->rot_y);
	double z2 = -xd * sin(map->rot_y) + z1 * cos(map->rot_y);

	// Apply rotation around Z axis
	double x3 = x2 * cos(map->rot_z) - y1 * sin(map->rot_z);
	double y3 = x2 * sin(map->rot_z) + y1 * cos(map->rot_z);

	// Isometric projection
	double iso_x = (x3 - y3) * cos(angle);
	double iso_y = -z2 + (x3 + y3) * sin(angle);

	p.x = (int)(iso_x * scale + WIN_W / 2);
	p.y = (int)(iso_y * scale + WIN_H / 2);
	return p;
}

/**
 * NOTE: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 * - Bresenham's algorithm in plain code
 */
void	draw_bresenham_line(t_mlx *mlx, t_pixel start, t_pixel end, int color)
{
	int	dx;
	int	dy;
	int	x_step;
	int	y_step;
	int	delta;
	int	delta2;

	dx = abs(end.x - start.x);
	dy = abs(end.y - start.y);
	x_step = (start.x < end.x) ? 1 : -1;
	y_step = (start.y < end.y) ? 1 : -1;
	delta = dx - dy; // delta variable decides which pixel is closest
	while (start.x != end.x || start.y != end.y)
	{
		put_pixel(mlx, start.x, start.y, color);
		delta2 = 2 * delta;
		if (delta2 > -dy)
		{
			delta -= dy;
			start.x += x_step;
		}
		if (delta2 < dx)
		{
			delta += dx;
			start.y += y_step;
		}
	}
	put_pixel(mlx, end.x, end.y, color); // draw the last point
}

/**
 * - Initializes and calculates the angles for each perspective
 */
void	init_angles(t_map *map)
{
	map->iso_angle = M_PI / 6;
	map->map_scale = 20.0;
}

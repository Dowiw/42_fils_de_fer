#include "fils_de_fer.h"

/**
 * - Return string of the selected mode
 */
static char	*find_viewpoint(t_map *map)
{
	if (map->rot_x != 0.0
		|| map->rot_y != 0.0
		|| map->rot_z != 0.0)
		return ("Rotated");
	else if (map->viewmode == MODE_Z_AXIS)
		return ("Orthrographic Plan View");
	else if (map->viewmode == MODE_ISOMETRIC)
		return ("Isometric View");
	else if (map->viewmode == MODE_Y_AXIS)
		return ("Y-Axis View");
	else if (map->viewmode == MODE_X_AXIS)
		return ("X-Axis View");
	else
		return ("Isometric View");
}

/**
 * - Drawing strings of texts after the image is rendered.
 * - Unfortunately, knowing where to put the pixels is all about magic numbers.
 * 	Maybe digging into how spaces and indents are formed in Word or Docs could
 * 	help but it will take more time. Maybe in the next graphic project.
 */
void	draw_menu(t_mlx *mlx, t_map *map)
{
	char	*intro;
	char	*view;
	char	*viewpoint;
	char	*how;

	intro = "Fils de Fer by kmonjard :)";
	view = "View mode: ";
	viewpoint = find_viewpoint(map);
	how = "How to use: ";
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 50, 50, 0xFFFFFF, intro);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 50, 100, 0xFFFFFF, view);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 150, 100, 0xFFFFFF, viewpoint);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 150, 100, 0xFFFFFF, how);
}

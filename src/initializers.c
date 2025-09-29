/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:48:41 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/16 11:48:42 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fils_de_fer.h"

/**
 * - Initializes height and width to 0 and points to NULL
 */
void	init_map(t_map *map)
{
	map->viewmode = MODE_ISOMETRIC;
	map->height = 0;
	map->width = 0;
	map->z_arr = NULL;
	map->colors = NULL;
	map->offset_w = 0.0;
	map->offset_h = 0.0;
	map->z_scale = 1.0;
	map->size = 0.0;
	map->view = 0.0;
	map->rot_x = 0.0;
	map->rot_y = 0.0;
	map->rot_z = 0.0;
}

/**
 * - Initialize the mlx struct (not confused for mlx_init)
 * - sets 0 for ints, NULL for pointers
 */
void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->win_ptr = NULL;
	mlx->img_ptr = NULL;
	mlx->img_data = NULL;
	mlx->bpp = 0;
	mlx->endian = 0;
	mlx->size_line = 0;
	init_details(mlx->details);
}

/**
 * - Extension of init_mlx_lib to put image data
 * - Frees things if NULL is returned
 */
static int	put_img_data(t_mlx *mlx, int *bpp, int *size_line, int *endian)
{
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, bpp, size_line, endian);
	if (!mlx->img_data)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		write(2, "Error: mlx_get_data_addr failed\n", 33);
		return (0);
	}
	return (1);
}

/**
 * - Initializes the library into the struct
 * - Also attaches the used event hooks to the window
 * - NOTE: data is only for key events
 */
int	init_mlx_lib(t_mlx *mlx, t_fdf_data *data)
{
	init_mlx(mlx);
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_W, WIN_H, "Fils de Fer");
	if (!mlx->win_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		return (0);
	}
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_W, WIN_H);
	if (!mlx->img_ptr)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		return (0);
	}
	if (!put_img_data(mlx, &mlx->bpp, &mlx->size_line, &mlx->endian))
		return (0);
	init_mlx_events(data);
	return (1);
}

/**
 * - Initializes and calculates the angles for isometric view
 * - pi / 6 being 30 degrees
 * - Also centralizes it beforehand
 */
void	init_angles(t_map *map)
{
	int		mid_x;
	int		mid_y;
	t_pixel	center;

	mid_x = (map->width - 1) / 2;
	mid_y = (map->height - 1) / 2;
	map->viewmode = MODE_ISOMETRIC;
	map->view = M_PI / 6;
	map->offset_h = 0;
	map->offset_w = 0;
	map->size = 1.0;
	map->size = calc_size(map);
	center = calc_iso(map, mid_x, mid_y, map->z_arr[mid_y][mid_x]);
	map->offset_w = WIN_W / 2 - center.x;
	map->offset_h = WIN_H / 2 - center.y;
}

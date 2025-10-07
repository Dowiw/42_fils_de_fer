/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 10:20:25 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/25 10:20:26 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fils_de_fer.h"

void	redraw(t_fdf_data *data)
{
	clear_image(&data->mlx);
	draw_map(data);
}

/**
 * - Draw the isometric view again
 */
void	reset(t_fdf_data *data)
{
	data->map.rot_x = 0.0;
	data->map.rot_y = 0.0;
	data->map.rot_z = 0.0;
	data->map.z_scale = 1.0;
	init_angles(&data->map);
}

/**
 * - Draw the map in parallel view (orthrographic plan)
 */
void	draw_plan_view(t_fdf_data *data)
{
	data->map.view = 0.0;
	data->map.rot_x = 0.0;
	data->map.rot_y = 0.0;
	data->map.rot_z = 0.0;
}

/**
 * - Find central pixel and put it in the center of the map
 */
void	centralize(t_map *map)
{
	int		mid_x;
	int		mid_y;
	t_pixel	center;

	map->offset_w = 0.0;
	map->offset_h = 0.0;
	mid_x = (map->width - 1) / 2;
	mid_y = (map->height - 1) / 2;
	center = calc_view(map, mid_x, mid_y, map->z_arr[mid_y][mid_x]);
	map->offset_w = WIN_W / 2 - center.x;
	map->offset_h = WIN_H / 2 - center.y;
}

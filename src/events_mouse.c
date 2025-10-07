/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:39:22 by kmonjard          #+#    #+#             */
/*   Updated: 2025/10/07 19:39:23 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fils_de_fer.h"
#include <X11/Xlib.h>

/**
 * - mlx hook passes x and y values of mouse and which button pressed
 * - left click: zoom in, right click: zooms out
 */
int	handle_mouse(int button, int x, int y, t_fdf_data *data)
{
	double	prev_scale;
	double	zoom;
	double	map_x;
	double	map_y;

	if (data->map.viewmode == MODE_TWO_POINT)
		return (0);
	prev_scale = data->map.size;
	if (button == Button1)
		zoom = 1.2;
	else if (button == Button3)
		zoom = 0.8;
	else
		return (0);
	map_x = (x - data->map.offset_w) / prev_scale;
	map_y = (y - data->map.offset_h) / prev_scale;
	data->map.size *= zoom;
	data->map.offset_w = x - map_x * data->map.size;
	data->map.offset_h = y - map_y * data->map.size;
	clear_image(&data->mlx);
	draw_map(data);
	return (0);
}

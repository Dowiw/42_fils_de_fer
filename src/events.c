/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:49:59 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/16 16:50:01 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fils_de_fer.h"

/**
 * - Handle key inputs
 */
static int	handle_key(int keycode, t_fdf_data *data)
{
	if (keycode == XK_Escape)
	{
		free_data(data);
		exit(EXIT_FAILURE);
	} // magnitutes of about 5.7 degrees
	else if (keycode == XK_minus)
		data->map.z_scale -= 0.1;
	else if (keycode == XK_equal)
		data->map.z_scale += 0.1;
	else if (keycode == XK_Left)
		data->map.rot_z -= 0.1;
	else if (keycode == XK_Right)
		data->map.rot_z += 0.1;
	else if (keycode == XK_w)
		data->map.rot_x += 0.1;
	else if (keycode == XK_s)
		data->map.rot_x -= 0.1;
	else if (keycode == XK_a)
		data->map.rot_y += 0.1;
	else if (keycode == XK_d)
		data->map.rot_y -= 0.1;
	clear_image(&data->mlx);
	draw_map(data);
	return (0);
}

/**
 * - Handle close (the x button)
 */
static int	handle_close(t_fdf_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
	return (0);
}

static int	expose_handler(t_fdf_data *data)
{
	clear_image(&data->mlx);
	draw_map(data);
	return (0);
}

/**
 * - Initializer of events into the window
 */
void	init_mlx_events(t_fdf_data *data)
{
	mlx_key_hook(data->mlx.win_ptr, handle_key, data);
	mlx_hook(data->mlx.win_ptr, EVENT_DESTROY, 0, handle_close, data);
	mlx_hook(data->mlx.win_ptr, EVENT_EXPOSE, 1L << 15, expose_handler, data);
}

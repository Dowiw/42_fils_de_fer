/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 08:45:08 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/25 09:12:55 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fils_de_fer.h"
#include <mlx.h>

/**
 * - Handles keys that are released
 */
int	key_release(int keycode, t_fdf_data *data)
{
	if (keycode == XK_t)
		data->mlx.pan_up = 0;
	else if (keycode == XK_g)
		data->mlx.pan_down = 0;
	else if (keycode == XK_f)
		data->mlx.pan_left = 0;
	else if (keycode == XK_h)
		data->mlx.pan_right = 0;
	else if (keycode == XK_o)
		data->map.orth_view = 0;
	return (0);
}

/**
 * - More key pressing hooks
 */
static void	more_key_press(int keycode, t_fdf_data *data)
{
	if (keycode == XK_w)
		data->map.rot_x += 0.1;
	else if (keycode == XK_s)
		data->map.rot_x -= 0.1;
	else if (keycode == XK_a)
		data->map.rot_y += 0.1;
	else if (keycode == XK_d)
		data->map.rot_y -= 0.1;
	else if (keycode == XK_minus)
		data->map.size -= 1.0;
	else if (keycode == XK_equal)
		data->map.size += 1.0;
	else if (keycode == XK_i)
		redraw_iso(data);
	else if (keycode == XK_o)
		data->map.orth_view = 1;
	else if (keycode == XK_c)
		centralize(data);
}

/**
 * - Handles key pressed
 */
int	key_press(int keycode, t_fdf_data *data)
{
	if (keycode == XK_t)
		data->mlx.pan_up = 1;
	else if (keycode == XK_g)
		data->mlx.pan_down = 1;
	else if (keycode == XK_f)
		data->mlx.pan_left = 1;
	else if (keycode == XK_h)
		data->mlx.pan_right = 1;
	else if (keycode == XK_Escape)
	{
		free_data(data);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == XK_Down)
		data->map.z_scale -= 0.1;
	else if (keycode == XK_Up)
		data->map.z_scale += 0.1;
	else if (keycode == XK_Left)
		data->map.rot_z += 0.1;
	else if (keycode == XK_Right)
		data->map.rot_z -= 0.1;
	more_key_press(keycode, data);
	return (0);
}

/**
 * - Loop for redrawing the offset again and again
 */
int	loop_hook(t_fdf_data *data)
{
	if (data->mlx.pan_left)
		data->map.offset_w -= 1.0;
	else if (data->mlx.pan_right)
		data->map.offset_w += 1.0;
	else if (data->mlx.pan_up)
		data->map.offset_h -= 1.0;
	else if (data->mlx.pan_down)
		data->map.offset_h += 1.0;
	clear_image(&data->mlx);
	draw_map(data);
	return (0);
}

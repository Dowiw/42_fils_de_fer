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
#include <stdlib.h>
#include <X11/keysym.h>

/**
 * - Centralizes view and redraws per passed key
 */
static void	do_view_changes(int keycode, t_fdf_data *data)
{
	if (keycode == XK_1)
		data->map.viewmode = MODE_ISOMETRIC;
	else if (keycode == XK_2)
		data->map.viewmode = MODE_Z_AXIS;
	else if (keycode == XK_3)
		data->map.viewmode = MODE_X_AXIS;
	else if (keycode == XK_4)
		data->map.viewmode = MODE_Y_AXIS;
	else if (keycode == XK_5)
		data->map.viewmode = MODE_TWO_POINT;
	centralize(&data->map);
	redraw(data);
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
	else if (keycode == XK_c)
		centralize(&data->map);
	if (keycode == XK_1
		|| keycode == XK_2
		|| keycode == XK_3
		|| keycode == XK_4
		|| keycode == XK_5)
		do_view_changes(keycode, data);
	else
		redraw(data);
}

/**
 * - Handles key pressed for bonus
 */
void	key_press(int keycode, t_fdf_data *data)
{
	if (keycode == XK_t)
		data->map.offset_h -= 5.0;
	else if (keycode == XK_g)
		data->map.offset_h += 5.0;
	else if (keycode == XK_f)
		data->map.offset_w -= 5.0;
	else if (keycode == XK_h)
		data->map.offset_w += 5.0;
	else if (keycode == XK_Down)
		data->map.z_scale -= 0.1;
	else if (keycode == XK_Up)
		data->map.z_scale += 0.1;
	else if (keycode == XK_Left)
		data->map.rot_z += 0.1;
	else if (keycode == XK_Right)
		data->map.rot_z -= 0.1;
	else if (keycode == XK_r)
		reset(data);
	more_key_press(keycode, data);
}

/**
 * - For no bonus
 * - Will check for bonus boolean
 */
int	mandatory_keys(int keycode, t_fdf_data *data)
{
	if (keycode == XK_Escape)
	{
		free_data(data);
		exit(EXIT_SUCCESS);
	}
	if (data->bonus)
		key_press(keycode, data);
	return (0);
}

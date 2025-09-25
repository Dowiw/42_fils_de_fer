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
 * - Handle close (the x button)
 */
static int	handle_close(t_fdf_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
	return (0);
}

/**
 * - Handles minimizing and maximizing
 */
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
	mlx_hook(data->mlx.win_ptr, EVENT_DESTROY, 0, handle_close, data);
	mlx_hook(data->mlx.win_ptr, EVENT_EXPOSE, 1L << 15, expose_handler, data);
	mlx_hook(data->mlx.win_ptr, EVENT_KEY_PRESS, 1L << 0, key_press, data);
	mlx_hook(data->mlx.win_ptr, EVENT_KEY_RELEASE, 1L << 1, key_release, data);
	mlx_loop_hook(data->mlx.mlx_ptr, loop_hook, data);
}

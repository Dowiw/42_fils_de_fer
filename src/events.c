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
int	handle_key(int keycode, t_fdf_data *data)
{
	if (keycode == XK_Escape)
	{
		free_data(data);
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
 * - Handle close (the x button)
 */
int	handle_close(t_fdf_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
	return (0);
}

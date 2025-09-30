/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:31 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/11 15:25:21 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fils_de_fer.h"
#include <mlx.h>
#include <unistd.h>
#include <stdio.h>

/**
 * - Main (assumes maps are in correct format)
 */
int	main(int ac, char **av)
{
	t_fdf_data	data;

	data.bonus = true;
	if (ac != 2 || !is_valid_format(av[1]))
		return (write(2, "Usage: ./fdf <valid file in .fdf format>\n", 42), 1);
	if (!parse_map(av[1], &data.map))
		return (1);
	if (!init_mlx_lib(&data.mlx, &data))
	{
		free_map(&data.map);
		perror("Error: failed initializing library");
		return (1);
	}
	draw_map(&data);
	mlx_loop(data.mlx.mlx_ptr);
}

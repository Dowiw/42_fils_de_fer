/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:31 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/11 15:25:21 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <mlx.h>

#include <math.h>

#include <unistd.h>

#include <stdlib.h>

/**
 * - Main (assumes maps are in correct format)
 */
int main(int ac, char **av)
{
	void	*mlx_ptr;

	if (ac != 2)
		return (write(2 ,"Usage: ./fdf <valid file in .fdf format>\n", 42), 1);
	mlx_ptr = mlx_init();

	mlx_destroy_display(mlx_ptr); // very important frees for 0 leaks
	free(mlx_ptr);
}

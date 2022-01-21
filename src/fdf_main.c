/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:14:31 by haitkadi          #+#    #+#             */
/*   Updated: 2022/01/20 22:14:34 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	calc_zoom(int *zoom, int width)
{
	if (width > 400)
		*zoom = 2;
	if (width < 300)
		*zoom = 5;
	if (width < 100)
		*zoom = 20;
}

static	void	fdf(char *file_name, int zoom, int altitude)
{
	t_mlx	mlx;
	t_data	img;

	ft_bzero(&img.dimensions, sizeof(t_dimensions));
	ft_bzero(&mlx, sizeof(t_mlx));
	img.map = get_map_from_fd(file_name, &img.dimensions);
	if (img.dimensions.horizontal == 0 && img.dimensions.vertical == 0)
		return ;
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, 2550, 1380, "FDF");
	img.img = mlx_new_image(img.mlx, 2550, 1380);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	if (zoom)
		mlx.zoom = zoom;
	else
		calc_zoom(&mlx.zoom, img.dimensions.horizontal);
	if (altitude)
		mlx.altitude = altitude;
	else
		mlx.altitude = 1;
	draw(&img, img.map, img.dimensions, mlx);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_key_hook(img.win, key_hook, &img);
	mlx_loop(img.mlx);
}

static	int	check_isdigit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		fdf(av[1], 0, 0);
	}
	else if (ac == 4)
	{
		if (check_isdigit(av[2]) || check_isdigit(av[3]))
		{
			write(1, "\e[1;31mERROR: Bad arguments\e[0m", 27);
			return (0);
		}
		fdf(av[1], ft_atoi(av[2]), ft_atoi(av[3]));
	}
	else
		write(1, "\e[1;31mERROR: Bad arguments\e[0m", 27);
	return (0);
}

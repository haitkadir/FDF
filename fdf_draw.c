/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:41:21 by haitkadi          #+#    #+#             */
/*   Updated: 2022/01/20 17:41:24 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 2550 && y < 1380)
	{
		dst = data->addr + (y * data->line_length + x * \
				(data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

static	void	iso_pro(int *x, int *y, int z)
{
	int	x_tmp;
	int	y_tmp;

	x_tmp = *x;
	y_tmp = *y;
	*x = (x_tmp - y_tmp) * cos(0.523599);
	*y = -z + (x_tmp + y_tmp) * sin(0.523599);
}

static	void	drawline_util(t_data ***img, t_mlx mlx, t_draw vars)
{
	while (1)
	{
		my_mlx_pixel_put(&***img, mlx.x0 + 1200, mlx.y0 + 200, mlx.color);
		if (mlx.x0 == mlx.x1 && mlx.y0 == mlx.y1)
			break ;
		vars.e2 = 2 * vars.err;
		if (vars.e2 >= vars.dy)
		{
			vars.err += vars.dy;
			mlx.x0 += vars.sx;
		}
		if (vars.e2 <= vars.dx)
		{
			vars.err += vars.dx;
			mlx.y0 += vars.sy;
		}
	}
}

static	void	zooming(t_mlx *mlx)
{
	mlx->x0 *= mlx->zoom;
	mlx->y0 *= mlx->zoom;
	mlx->x1 *= mlx->zoom;
	mlx->y1 *= mlx->zoom;
}

void	drawline(t_data **img, t_mlx mlx, int ***map)
{
	t_draw	vars;

	ft_bzero(&vars, sizeof(t_draw));
	vars.z = map[mlx.y0][mlx.x0][0];
	vars.z1 = map[mlx.y1][mlx.x1][0];
	zooming(&mlx);
	if (vars.z != 0)
		vars.z *= mlx.altitude;
	if (vars.z1 != 0)
		vars.z1 *= mlx.altitude;
	iso_pro(&mlx.x0, &mlx.y0, vars.z);
	iso_pro(&mlx.x1, &mlx.y1, vars.z1);
	vars.dx = abs(mlx.x1 - mlx.x0);
	if (mlx.x0 < mlx.x1)
		vars.sx = 1;
	else
		vars.sx = -1;
	vars.dy = -abs(mlx.y1 - mlx.y0);
	if (mlx.y0 < mlx.y1)
		vars.sy = 1;
	else
		vars.sy = -1;
	vars.err = vars.dx + vars.dy;
	drawline_util(&img, mlx, vars);
}

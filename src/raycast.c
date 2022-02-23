/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 09:38:26 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/23 14:50:26 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	variable_set(t_mpl *v, t_point next)
{
	v->dx = next.x;
	v->dy = next.y;
	v->incx = 0.001;
	v->incy = 0.001;
	if (v->dx == 0)
		v->incx = 0;
	if (v->dx < 0)
	{
		v->dx = -v->dx;
		v->incx = -v->incx;
	}
	if (v->dy == 0)
		v->incy = 0;
	if (v->dy < 0)
	{
		v->dy = -v->dy;
		v->incy = -v->incy;
	}
	v->ddx = v->dx * 2;
	v->ddy = v->dy * 2;
}

static void	ft_x_major(t_ray *r, t_point mp, t_map map)
{
	r->v.errorprev = r->v.dx;
	r->v.error = r->v.dx;
	while (1)
	{
		mp.x += r->v.incx;
		r->v.error += r->v.ddy;
		if (r->v.error > r->v.ddx)
		{
			mp.y += r->v.incy;
			r->v.error -= r->v.ddx;
			if (r->v.error + r->v.errorprev < r->v.ddx)
			{
				if(map.mapdata[(int)(mp.y - r->v.incy)][(int)mp.x] == '1')
				{
					r->hit.x = mp.x;
					r->hit.y = mp.y - r->v.incy;
					break;
				}
			}
			else if (r->v.error + r->v.errorprev > r->v.ddx)
			{
				if (map.mapdata[(int)mp.y][(int)(mp.x - r->v.incx)] == '1')
				{
					r->hit.x = mp.x - r->v.incx;
					r->hit.y = mp.y;
					break ;
				}
			}
			else
			{
				if (map.mapdata[(int)mp.y][(int)(mp.x - r->v.incx)] == '1' &&
					map.mapdata[(int)(mp.y - r->v.incy)][(int)mp.x] == '1')
				{
					r->hit.x = mp.x - r->v.incx;
					r->hit.y = mp.y - r->v.incy;
					break ;
				}
			}
		}
		if (map.mapdata[(int)mp.y][(int)mp.x] == '1')
		{
			r->hit.x = mp.x;
			r->hit.y = mp.y;
			break ;
		}
		r->v.errorprev = r->v.error;
	}
}

static void	ft_y_major(t_ray *r, t_point mp, t_map map)
{
	r->v.errorprev = r->v.dy;
	r->v.error = r->v.dy;
	while (1)
	{
		mp.y += r->v.incy;
		r->v.error += r->v.ddx;
		if (r->v.error > r->v.ddy)
		{
			r->v.error -= r->v.ddy;
			mp.x += r->v.incx;
			if (r->v.error + r->v.errorprev < r->v.ddy)
			{
				if (map.mapdata[(int)mp.y][(int)(mp.x - r->v.incx)] == '1')	// x
				{
					r->hit.x = mp.x - r->v.incx;
					r->hit.y = mp.y;
					break ;
				}
			}
			else if (r->v.error + r->v.errorprev > r->v.ddy)
			{
				if (map.mapdata[(int)(mp.y - r->v.incy)][(int)mp.x] == '1')	// y
				{
					r->hit.x = mp.x;
					r->hit.y = mp.y - r->v.incy;
					break ;
				}
			}
			else
			{
				if (map.mapdata[(int)mp.y][(int)(mp.x - r->v.incx)] == '1' &&
					map.mapdata[(int)(mp.y - r->v.incy)][(int)mp.x] == '1')	//양옆에 막혀있을 때
				{
					r->hit.x = mp.x - r->v.incx;
					r->hit.y = mp.y - r->v.incy;
					break ;
				}
			}
		}
		if (map.mapdata[(int)mp.y][(int)mp.x] == '1')
		{
			r->hit.x = mp.x;
			r->hit.y = mp.y;
			break ;
		}
		r->v.errorprev = r->v.error;
	}
}

static void	hit_ray(t_ray *r, t_vars *data, double ray_angle)
{
	t_point	next;
	t_point player;
	int x;
	int y;

	player.x = data->player.px / data->tile_size;
	player.y = data->player.py / data->tile_size;
	next.x = cos(ray_angle);
	next.y = sin(ray_angle);
	variable_set(&r->v, next);
	r->wall_hit = 0;
	r->is_v = 0;
	if (r->v.ddx > r->v.ddy)
		ft_x_major(r, player, data->map);
	else
		ft_y_major(r, player, data->map);
}

static double camera_angle(double ra, double pa)
{
	double ca;

	ca = pa - ra;
	if (ca < 0)
		ca += (2 * PI);
	if (ca > (2 * PI))
		ca -= (2 * PI);
	return (ca);
}


double	distance(float x1,float x2, float y1, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void draw_wall(t_vars *vars, t_ray ray, double dist, int x)
{
	int	width;
	int	height;
	int	drawStart;
	int	drawEnd;
	float lineH;

	width = 1;
	height = WINDOW_HEIGHT;
	lineH =  DIST_PROJ_PLANE / dist;
	if (lineH > height)
		lineH = height;
	drawStart = -(lineH / 2) + (height / 2);
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = (lineH / 2) + (height / 2);
	if (drawEnd >= height)
		drawEnd = height - 1;

	int	h;
	int	sw, ew;
	int	y = vars->screen.size_line;
	int	green = 0x00CD00;
	int	blue = 0x0000CD;

	h = 0;
	while (h + drawStart < drawEnd)
	{
		sw = x * width;
		ew = sw + width;
		while (sw <= ew)
		{
			if (dist <= 10)
			{
					if (ray.is_v == 1)
						vars->screen.data[((h + drawStart) * y) + sw] = green;
					else
						vars->screen.data[((h + drawStart) * y) + sw] = blue;
			}
			sw++;
		}
		h++;
	}
}

void	ray_draw(t_vars *data)
{
	double	dist;
	t_p     start;
	t_p     end;
	double	ca;
	double	pa;
	double	ra;
	int	i;

	pa = data->player.pa;
	i = 0;
    ra = pa - (FOV_ANGLE / 2.0);
	while (i < WINDOW_WIDTH)
	{
		ca = camera_angle(ra, pa);
		hit_ray(&data->ray, data, ra);
		dist = distance(data->player.px, data->ray.hit.x * data->tile_size, data->player.py, data->ray.hit.y * data->tile_size) * cos(ca) / data->tile_size;
		if (dist <= 1)
			dist = 1;
		start.x = data->player.px;
		start.y = data->player.py;
		end.x = data->ray.hit.x * data->tile_size;
		end.y = data->ray.hit.y * data->tile_size;
	//	draw_line(data, start, end);
		draw_wall(data, data->ray, dist, i);
        ra += FOV_ANGLE / WINDOW_WIDTH;
		i++;
	}
}

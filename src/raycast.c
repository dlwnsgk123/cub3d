/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 09:38:26 by junhalee          #+#    #+#             */
/*   Updated: 2022/02/22 18:44:45 by junhalee         ###   ########.fr       */
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
					r->m_dir.x = mp.x;
					r->m_dir.y = mp.y - r->v.incy;
					break ;
				}
			}
			else if (r->v.error + r->v.errorprev > r->v.ddx)
			{
				if (map.mapdata[(int)mp.y][(int)(mp.x - r->v.incx)] == '1')
				{
					r->m_dir.x = mp.x - r->v.incx;
					r->m_dir.y = mp.y;
					break ;
				}
			}
			else
			{
				if (map.mapdata[(int)mp.y][(int)(mp.x - r->v.incx)] == '1' &&
					map.mapdata[(int)(mp.y - r->v.incy)][(int)mp.x] == '1')
				{
					r->m_dir.x = mp.x - r->v.incx;
					r->m_dir.y = mp.y - r->v.incy;
					break ;
				}
			}
		}
		if (map.mapdata[(int)mp.y][(int)mp.x] == '1')
		{
			r->m_dir.x = mp.x;
			r->m_dir.y = mp.y;
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
					r->m_dir.x = mp.x - r->v.incx;
					r->m_dir.y = mp.y;
					break ;
				}
			}
			else if (r->v.error + r->v.errorprev > r->v.ddy)
			{
				if (map.mapdata[(int)(mp.y - r->v.incy)][(int)mp.x] == '1')	// y
				{
					r->m_dir.x = mp.x;
					r->m_dir.y = mp.y - r->v.incy;
					break ;
				}
			}
			else
			{
				if (map.mapdata[(int)mp.y][(int)(mp.x - r->v.incx)] == '1' &&
					map.mapdata[(int)(mp.y - r->v.incy)][(int)mp.x] == '1')	//양옆에 막혀있을 때
				{
					r->m_dir.x = mp.x - r->v.incx;
					r->m_dir.y = mp.y - r->v.incy;
					break ;
				}
			}
		}
		if (map.mapdata[(int)mp.y][(int)mp.x] == '1')
		{
			r->m_dir.x = mp.x;
			r->m_dir.y = mp.y;
			break ;
		}
		r->v.errorprev = r->v.error;
	}
}

static void	hit_ray(t_ray *r, t_vars *data, double ray_angle)
{
	t_point	next;
	t_point player;

	player.x = data->player.px / data->tile_size;
	player.y = data->player.py / data->tile_size;
	next.x = cos(ray_angle);
	next.y = sin(ray_angle);
	variable_set(&r->v, next);
	r->hit = 0;
	if (r->v.ddx > r->v.ddy)
		ft_x_major(r, player, data->map);
	else
		ft_y_major(r, player, data->map);
	//r->hit = hit_direction(r->m_dir);
}

static double camera_angle(double ra, double pa)
{
	double ca;

	ca = pa - ra;
	if (ca < 0)
		ca += (2 * M_PI);
	if (ca > (2 * M_PI))
		ca -= (2 * M_PI);
	return (ca);
}

/*
double	distance(float px,float py, t_point dir)
{
	return (sqrt((dir.x - pos.x) * (dir.x - pos.x) +
			(dir.y - pos.y) * (dir.y - pos.y)));
}
*/

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
	while (i < 60)
	{
		ca = camera_angle(ra, pa);
		hit_ray(&data->ray, data, ra);
		data->ray.s_dir.x = data->ray.m_dir.x * data->tile_size;
		data->ray.s_dir.y = data->ray.m_dir.y * data->tile_size;
//		dist = distance(data->player.mp, data->ray.m_dir) * cos(ca);
		if (dist <= 1)
			dist = 1;
		start.x = data->player.px;
		start.y = data->player.py;
		end.x = data->ray.s_dir.x;
		end.y = data->ray.s_dir.y;
		draw_line(data, start, end);
		//hit_ray_draw(data, dist, i);
        ra += FOV_ANGLE / 60;
		i++;
	}
}

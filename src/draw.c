/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:54:02 by seungiki          #+#    #+#             */
/*   Updated: 2022/02/27 15:23:08 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_texture_color(t_vars *vars, t_ray ray, t_render r, int y_point)
{
	int	tex_x;
	int	tex_y;
	int	tex_type;
	int	tex_width;
	int	distance_from_top;

	tex_type = ray.wall_dir;
	tex_width = vars->texture[tex_type].width;
	if (ray.hit_v)
		tex_x = (fmod(ray.hity, TILE_SIZE) \
			* (double)tex_width / TILE_SIZE);
	else
		tex_x = (fmod(ray.hitx, TILE_SIZE) \
			* (double)tex_width / TILE_SIZE);
	distance_from_top = y_point + r.wall_start
		- (WINDOW_HEIGHT / 2) + (r.wall_height / 2);
	tex_y = distance_from_top * \
			((double)vars->texture[tex_type].height / r.wall_height);
	return (vars->texture[tex_type].data[tex_y * tex_width + tex_x]);
}

static void	render_init(t_render *r, t_ray ray, t_vars *vars)
{
	ray.dist *= cos(ray.ra - vars->player.pa);
	r->wall_height = TILE_SIZE / ray.dist
		* ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2));
	r->wall_start = (WINDOW_HEIGHT / 2) - (r->wall_height / 2);
	if (r->wall_start < 0)
		r->wall_start = 0;
	r->wall_end = (r->wall_height / 2) + (WINDOW_HEIGHT / 2);
	if (r->wall_end > WINDOW_HEIGHT)
		r->wall_end = WINDOW_HEIGHT;
}

void	draw_wall(t_vars *vars, t_ray ray, int ray_index)
{
	int			y;
	t_render	r;

	y = 0;
	render_init(&r, ray, vars);
	while (y + r.wall_start < r.wall_end)
	{
		vars->screen.data[((y + r.wall_start) * WINDOW_WIDTH) + ray_index] = \
			get_texture_color(vars, ray, r, y);
		y++;
	}
}

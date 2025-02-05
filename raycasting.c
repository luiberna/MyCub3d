/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:18:51 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/05 18:34:03 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void calculate_dist(t_player *player, t_ray *ray)
{
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
    }
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
    }
}

void DDA(t_data *data, t_player *player, t_ray *ray)
{
    (void)player;
    while(1)
    {
        if(ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if(data->map[ray->map_y][ray->map_x] == '1')
            break;
    }
    if (ray->side == 0)
        ray->wall_dist = ray->side_dist_x - ray->delta_dist_x;
    else
        ray->wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

void wall_render(t_player *player, t_ray *ray)
{
    ray->wall_height = (int)(SCREEN_H / ray->wall_dist);
    ray->start_pos_draw = -ray->wall_height / 2 + SCREEN_H / 2;
    if (ray->start_pos_draw < 0)
        ray->start_pos_draw = 0;
    ray->end_pos_draw = ray->wall_height / 2 + SCREEN_H / 2;
    if (ray->end_pos_draw >= SCREEN_H)
        ray->end_pos_draw = SCREEN_H;
    if (ray->side == 0)
        ray->wall_x = player->pos_y + ray->wall_dist * ray->ray_dir_y;
    else
        ray->wall_x = player->pos_x + ray->wall_dist * ray->ray_dir_x;
    ray->wall_x -= floor(ray->wall_x);
}

int  get_direction(t_ray *ray)
{
	if(ray->side == 0)
	{
		if(ray->ray_dir_x < 0)
			return (W);
		else
			return (E);
	}	
	else
	{
		if(ray->ray_dir_y > 0)
			return (S);
		else 
			return (N);
	}
}

void get_pixel_map(t_data *data, t_ray *ray, int x)
{
    int dir;
    double step;
    double pos;
    int color;
    int tex_y;

    dir = get_direction(ray);
    ray->text_x = (int)(ray->wall_x * CUBE);
    if (dir == W || dir == S)
        ray->text_x = CUBE - ray->text_x - 1;
    step = 1.0 * CUBE / ray->wall_height;
    pos = (ray->start_pos_draw - (-ray->wall_height / 2 + SCREEN_H / 2)) * step;
    if (pos < 0)
        pos = 0;
    while (ray->start_pos_draw < ray->end_pos_draw)
    {
        tex_y = (int)pos & (CUBE - 1);
        pos += step;
        color = data->texture_buffer[dir][tex_y * CUBE + ray->text_x];
        if (ray->side == 1)
            color = (color >> 1) & 0x7F7F7F;
        if (color > 0)
            data->pixel_map[ray->start_pos_draw][x] = color;
        ray->start_pos_draw++;
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:22:35 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/03 20:18:32 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void check_movement(t_player *player, char **map, double new_x, double new_y)
{
    if (map[(int)(new_y)][(int)(new_x + 0.2)] != '1' &&
        map[(int)(new_y - 0.2)][(int)(new_x)] != '1' &&
        map[(int)(new_y + 0.2)][(int)(new_x)] != '1' &&
        map[(int)(new_y)][(int)(new_x - 0.2)] != '1')
    {
        player->pos_x = new_x;
        player->pos_y = new_y;
    }
}

void move_player3(t_player *player, char **map, double sin_angle, double cos_angle)
{
    double new_x;
    double new_y;
    
    new_x = player->pos_x;
    new_y = player->pos_y;
    if (player->key_left)
    {
        new_x -= player->plane_x * SPEED;
        new_y -= player->plane_y * SPEED;
    }
    if (player->key_right)
    {
        new_x += player->plane_x * SPEED;
        new_y += player->plane_y * SPEED;
    }
    check_movement(player, map, new_x, new_y);
}

void move_player2(t_player *player, char **map)
{
    double new_x;
    double new_y;
    double cos_angle;
    double sin_angle;
    
    cos_angle = cos(player->angle);
    sin_angle = sin(player->angle);
    new_x = player->pos_x;
    new_y = player->pos_y;
    if (player->angle > 2 * PI)
        player->angle -= 2 * PI;
    if (player->angle < 0)
        player->angle += 2 * PI;
    if (player->key_down)
    {
        new_x -= player->dir_x * SPEED;
        new_y -= player->dir_y * SPEED;
    }
    if (player->key_up)
    {
        new_x += player->dir_x * SPEED;
        new_y += player->dir_y * SPEED;
    }
    check_movement(player, map, new_x, new_y);
    move_player3(player, map, sin_angle, cos_angle);
}

void move_player(t_player *player, char **map)
{
    double old_dir_x;
    double old_plane_x;
    
    old_dir_x = player->dir_x;
    old_plane_x = player->plane_x;
    if (player->left_rotate)
    {
        player->angle -= RSPEED;
        player->dir_x = player->dir_x * cos(-RSPEED) - player->dir_y * sin(-RSPEED);
        player->dir_y = old_dir_x * sin(-RSPEED) + player->dir_y * cos(-RSPEED);
        player->plane_x = player->plane_x * cos(-RSPEED) - player->plane_y * sin(-RSPEED);
        player->plane_y = old_plane_x * sin(-RSPEED) + player->plane_y * cos(-RSPEED);
        
    }
    if (player->right_rotate)
    {
        player->angle += RSPEED;

        player->dir_x = player->dir_x * cos(RSPEED) - player->dir_y * sin(RSPEED);
        player->dir_y = old_dir_x * sin(RSPEED) + player->dir_y * cos(RSPEED);
        player->plane_x = player->plane_x * cos(RSPEED) - player->plane_y * sin(RSPEED);
        player->plane_y = old_plane_x * sin(RSPEED) + player->plane_y * cos(RSPEED);
    }
    move_player2(player, map);
}

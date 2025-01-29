/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:22:35 by luiberna          #+#    #+#             */
/*   Updated: 2025/01/29 02:14:36 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int key_press(int keycode, t_cube *cube)
{
    if(keycode == KW)
        cube->player->key_up = true;
    if(keycode == KS)
        cube->player->key_down = true;
    if(keycode == A)
        cube->player->key_left = true;
    if(keycode == D)
        cube->player->key_right = true;
    if(keycode == LEFT)
        cube->player->left_rotate = true;
    if(keycode == RIGHT)
        cube->player->right_rotate = true;
    return 0;
}

int key_release(int keycode, t_cube *cube)
{
    if(keycode == KW)
        cube->player->key_up = false;
    if(keycode == KS)
        cube->player->key_down = false;
    if(keycode == A)
        cube->player->key_left = false;
    if(keycode == D)
        cube->player->key_right = false;
    if(keycode == LEFT)
        cube->player->left_rotate = false;
    if(keycode == RIGHT)
        cube->player->right_rotate = false;
    return 0;
}

void check_movement(t_player *player, char **map, double new_x, double new_y)
{
    if (map[(int)(new_y + 0.4)][(int)(new_x + 0.4)] != '1' &&
        map[(int)(new_y)][(int)(new_x)] != '1' &&
        map[(int)(new_y + 0.4)][(int)(new_x)] != '1' &&
        map[(int)(new_y)][(int)(new_x + 0.4)] != '1')
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
        new_x -= sin_angle * SPEED;
        new_y += cos_angle * SPEED;
    }
    if (player->key_right)
    {
        new_x += sin_angle * SPEED;
        new_y -= cos_angle * SPEED;
    }
    check_movement(player, map, new_x, new_y);
}

void move_player2(t_player *player, char **map, double sin_angle, double cos_angle)
{
    double new_x;
    double new_y;
    
    new_x = player->pos_x;
    new_y = player->pos_y;
    if (player->key_down)
    {
        new_x += cos_angle * SPEED;
        new_y += sin_angle * SPEED;
    }
    if (player->key_up)
    {
        new_x -= cos_angle * SPEED;
        new_y -= sin_angle * SPEED;
    }
    check_movement(player, map, new_x, new_y);
    move_player3(player, map, sin_angle, cos_angle);
}

void move_player(t_player *player, char **map)
{
    double cos_angle;
    double sin_angle;

    cos_angle = cos(player->angle);
    sin_angle = sin(player->angle);
    if (player->left_rotate)
        player->angle -= RSPEED;
    if (player->right_rotate)
        player->angle += RSPEED;
    if (player->angle > 2 * PI)
        player->angle -= 2 * PI;
    if (player->angle < 0)
        player->angle += 2 * PI;
    move_player2(player, map, sin_angle, cos_angle);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:22:35 by luiberna          #+#    #+#             */
/*   Updated: 2025/01/29 00:12:57 by luiberna         ###   ########.fr       */
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

void move_player2(t_player *player, double sin_angle, double cos_angle)
{
    if (player->left_rotate)
        player->angle -= RSPEED;
    if (player->right_rotate)
        player->angle += RSPEED;
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;
    if (player->key_left)
    {
        player->pos_x -= sin_angle * SPEED;
        player->pos_y += cos_angle * SPEED;
    }
}

void move_player(t_player *player, char **map)
{
    double cos_angle;
    double sin_angle;

    cos_angle = cos(player->angle);
    sin_angle = sin(player->angle);
    if (player->key_down)
    {
        player->pos_x += cos_angle * SPEED;
        player->pos_y += sin_angle * SPEED;
    }
    if (player->key_up)
    {
        player->pos_x -= cos_angle * SPEED;
        player->pos_y -= sin_angle * SPEED;
    }
    if (player->key_right)
    {
        player->pos_x += sin_angle * SPEED;
        player->pos_y -= cos_angle * SPEED;
    }
    move_player2(player, sin_angle, cos_angle);
}

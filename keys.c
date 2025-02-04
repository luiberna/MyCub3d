/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:18:14 by luiberna          #+#    #+#             */
/*   Updated: 2025/02/04 20:42:20 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int key_press(int keycode, t_cube *cube)
{
    if (keycode == 109)
        cube->player->minimap = !cube->player->minimap;
    if (keycode == 65307)
        close_window(cube);
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

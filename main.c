#include "../Includes/cub3d.h"

void raycaster(t_cube *cube)
{
    int x;

    x = 0;
    while(x < SCREEN_W)
    {
        cube->ray = ft_calloc(1, sizeof(t_ray));
        init_ray(cube->data, cube->player, cube->ray, x);
        calculate_dist(cube->player, cube->ray);
        DDA(cube->data, cube->player, cube->ray);
        wall_render(cube->player, cube->ray);
        get_pixel_map(cube->data, cube->ray, x);
        free(cube->ray);
        x++;
    }
}

void render(t_cube *cube)
{
    raycaster(cube);
    draw_pixel_map(cube, cube->data);
}

int update_game(t_cube *cube)
{
    clear_pixel_map(cube->data);
    clear_image(cube);
    move_player(cube->player, cube->data->map);
    render(cube);
    if (cube->player->minimap)
        draw_minimap(cube);
    mlx_put_image_to_window(cube->mlx, cube->win, cube->img->img, 0, 0);
    return 0;
}

int main(int argc, char **argv)
{
    t_cube cube;

    check_errors(argc, argv);
    init_cube(&cube, argv[1]);
    load_textures(&cube, cube.data);
    mlx_hook(cube.win, 2, 1L<<0, key_press, &cube);
    mlx_hook(cube.win, 3, 1L<<1, key_release, &cube);
    mlx_loop_hook(cube.mlx, update_game, &cube);
    mlx_hook(cube.win, 17, 0, close_window, &cube);
    mlx_loop(cube.mlx);
    return 0;
}

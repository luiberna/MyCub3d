#include "../Includes/cub3d.h"

void clear_image(t_cube *cube)
{
    for(int y = 0; y < SCREEN_H; y++)
        for(int x = 0; x < SCREEN_W; x++)
            put_pixel(x, y, 0, cube);
}

int close_window(t_cube *cube)
{
    free_cube(cube);
    exit(0);
    return 0;
}

int update_game(t_cube *cube)
{
    clear_image(cube);
    move_player(cube->player, cube->data->map);
    draw_minimap(cube);
    //render(cube);
    return 0;
}

int main(int argc, char **argv)
{
    t_cube cube;

    check_errors(argc, argv);
    init_cube(&cube, argv[1]);

    mlx_hook(cube.win, 2, 1L<<0, key_press, &cube);       // ✅ Pass &cube
    mlx_hook(cube.win, 3, 1L<<1, key_release, &cube);     // ✅ Pass &cube
    mlx_loop_hook(cube.mlx, update_game, &cube);         // ✅ Calls move_player()
    mlx_hook(cube.win, 17, 0, close_window, &cube);

    mlx_loop(cube.mlx);
    free_cube(&cube);
    return 0;
}

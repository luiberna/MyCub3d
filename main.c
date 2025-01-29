#include "../Includes/cub3d.h"

void get_player_position(t_data *data, t_player *player)
{
    int x;
    int y;
    
    y = 0;
    while (data->map[y]) {
        x = 0;
        while (data->map[y][x]) {
            if (data->map[y][x] == 'N' || data->map[y][x] == 'E' || data->map[y][x] == 'S' || data->map[y][x] == 'W') {
                player->pos_x = x;
                player->pos_y = y;
                return ;
            }
            x++;
        }
        y++;
    }
}

void init_player(t_data *data, t_player *player)
{
    get_player_position(data, player);
    player->angle = PI / 2;

    player->key_up = false;
    player->key_down = false;
    player->key_right = false;
    player->key_left = false;

    player->left_rotate = false;
    player->right_rotate = false;
}

void init_data(t_data *data, char *file)
{
    data->map = get_map(file);
    //print_map(data->map);
    data->map_height = get_map_height(file);
    data->map_width = get_map_width(data);
    data->pixel_map = get_pixel_map(data);
    //data->rff_map = 
    data->textures = get_textures(file);
}

void init_cube(t_cube *cube, char *file)
{
    cube->data = ft_calloc(1, sizeof(t_data));
    init_data(cube->data, file);

    cube->player = ft_calloc(1, sizeof(t_player));
    init_player(cube->data ,cube->player);

    cube->mlx = mlx_init();
    if (!cube->mlx)
        print_error("ERROR: Failed to initialize MLX\n");
    
    cube->win = mlx_new_window(cube->mlx, SCREEN_W, SCREEN_H, "Cube3D");
    if (!cube->win)
        print_error("ERROR: Failed to create MLX window\n");

    cube->img = ft_calloc(1, sizeof(t_image));
    cube->img->img = mlx_new_image(cube->mlx, SCREEN_W, SCREEN_H);
    if (!cube->img->img)
        print_error("ERROR: Failed to create image\n");
    cube->img->addr = mlx_get_data_addr(cube->img->img, &cube->img->bpp, &cube->img->size_line, &cube->img->endian);
}

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

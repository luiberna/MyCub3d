#include "../Includes/cub3d.h"

void get_player_position(t_data *data, t_player *player) {
    int x;
    int y;
    
    y = 0;
    while (data->map[y]) {
        x = 0;
        while (data->map[y][x]) {
            if (data->map[y][x] == 'N' || data->map[y][x] == 'E' || data->map[y][x] == 'S' || data->map[y][x] == 'W') {
                player->pos_x = x;
                player->pos_y = y;
            }
            x++;
        }
        y++;
    }
}

void init_player(t_cube *cube, t_player *player) {
    get_player_position(cube->data, player);
    printf("Player X: %d\nPlayer Y: %d\n", player->pos_x, player->pos_y);
}

void init_data(t_data *data, char *file) {
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
    cube->data = ft_calloc(sizeof(t_data), 1);
    init_data(cube->data, file);
    cube->player = ft_calloc(sizeof(t_player), 1);
    init_player(cube, cube->player);
    // init_img(&cube->img);
    cube->mlx = mlx_init();
    cube->win = mlx_new_window(cube->mlx, SCREEN_W, SCREEN_H, "Cube3d");
    cube->img = ft_calloc(sizeof(t_image), 1);
    cube->img->img = mlx_new_image(cube->mlx, SCREEN_W, SCREEN_H);
    cube->img->addr = mlx_get_data_addr(cube->img->img, &cube->img->bpp, &cube->img->size_line, &cube->img->endian);
    mlx_put_image_to_window(cube->mlx, cube->win, cube->img, 0, 0);
}

int main(int argc, char **argv) {
    t_cube cube;

    check_errors(argc, argv);
    init_cube(&cube, argv[1]);
    draw_minimap(&cube);
    mlx_loop_hook(&cube.mlx, draw_minimap, &cube);
    mlx_loop(&cube.mlx);
    free_cube(&cube);
    return 0;
}
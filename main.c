#include "../Includes/cub3d.h"

int key_press(int keycode, t_player *player)
{
    if(keycode == KW)
        player->key_up = true;
    if(keycode == KS)
        player->key_down = true;
    if(keycode == A)
        player->key_left = true;
    if(keycode == D)
        player->key_right = true;
    if(keycode == LEFT)
        player->left_rotate = true;
    if(keycode == RIGHT)
        player->right_rotate = true;
    return 0;
}

int key_release(int keycode, t_player *player)
{
    if(keycode == KW)
        player->key_up = false;
    if(keycode == KS)
        player->key_down = false;
    if(keycode == A)
        player->key_left = false;
    if(keycode == D)
        player->key_right = false;
    if(keycode == LEFT)
        player->left_rotate = false;
    if(keycode == RIGHT)
        player->right_rotate = false;
    return 0;
}

void move_player(t_player *player)
{
    int speed = 3;
    float angle_speed = 0.03;
    float cos_angle = cos(player->angle);
    float sin_angle = sin(player->angle);

    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;

    if (player->key_up)
    {
        player->pos_x += cos_angle * speed;
        player->pos_y += sin_angle * speed;
    }
    if (player->key_down)
    {
        player->pos_x -= cos_angle * speed;
        player->pos_y -= sin_angle * speed;
    }
    if (player->key_left)
    {
        player->pos_x += sin_angle * speed;
        player->pos_y -= cos_angle * speed;
    }
    if (player->key_right)
    {
        player->pos_x -= sin_angle * speed;
        player->pos_y += cos_angle * speed;
    }
}

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

int close_window(t_cube *cube) {
    free_cube(cube);
    exit(0);
    return 0;
}

int main(int argc, char **argv) {
    t_cube cube;

    check_errors(argc, argv);
    init_cube(&cube, argv[1]);
    mlx_hook(cube.win, 2, 1L<<0, key_press, &cube.player);
    mlx_hook(cube.win, 3, 1L<<1, key_release, &cube.player);
    mlx_loop_hook(cube.mlx, draw_minimap, &cube);
    mlx_hook(cube.win, 17, 0, close_window, &cube);
    mlx_loop(cube.mlx);
    free_cube(&cube);
    return 0;
}
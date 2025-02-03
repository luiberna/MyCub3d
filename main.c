#include "../Includes/cub3d.h"

void init_ray(t_data *data, t_player *player, t_ray *ray, int x) 
{
    ray->camera_x = 2.0 * (double)x / (double)SCREEN_W - 1.0;
    ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
    ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
    ray->map_x = player->pos_x;
    ray->map_y = player->pos_y;
    ray->delta_dist_x = fabs(1.0 / (ray->ray_dir_x + (ray->ray_dir_x == 0) * EPSILON));
    ray->delta_dist_y = fabs(1.0 / (ray->ray_dir_y + (ray->ray_dir_y == 0) * EPSILON));
    ray->side_dist_x = 0;
    ray->side_dist_y = 0;
    ray->step_x = 0;
    ray->step_y = 0;
    ray->side = 0;
}

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
//Versao OG
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

//Pode estar errado
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

//Pode estar errado
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
    if (pos < 0) pos = 0;

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
//Pode estar errado
void img_to_texture_buff(t_data *data, t_image *img, int dir)
{
    int *pixels;
    int i;
    int j;

    pixels = ft_calloc(img->width * img->height, sizeof(int));
    if (!pixels)
        print_error("Error: Could not allocate pixels\n");
    i = 0;
    while (i < img->height)
    {
        j = 0;
        while (j < img->width)
        {
            pixels[i * img->width + j] = ((int *)img->addr)[i * img->width + j];
            j++;
        }
        i++;
    }
    if (data->texture_buffer[dir])
        free(data->texture_buffer[dir]);
    data->texture_buffer[dir] = pixels;
}
//Pode estar errado
void	load_textures(t_cube *cube, t_data *data)
{
	t_image 	tmp;
	int		i;

	i = -1;
	while(++i < 4)
	{	
		tmp.img = mlx_xpm_file_to_image(cube->mlx, data->textures[i], &tmp.width, &tmp.height);
		if(!tmp.img)
			print_error("Error on file to image\n");
		tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.size_line, &tmp.endian);
		if(!tmp.addr)
			printf("Error on get data Addr\n");
		img_to_texture_buff(data, &tmp, i);
		mlx_destroy_image(cube->mlx, tmp.img);
	}
}

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

int	get_hex_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void get_rgb(char *line, int *color)
{
    char **color_parts;
    int i = 0;

    color_parts = ft_split(line, ',');
    if (!color_parts)
        return;
    color[0] = ft_atoi(color_parts[0]);
    color[1] = ft_atoi(color_parts[1]);
    color[2] = ft_atoi(color_parts[2]);
    if (color[0] > 255 || color[1] > 255 || color[2] > 255)
    {
        printf("Some color didn't get a correct value\n");
        exit(1);
    }
    while (color_parts[i])
    {
        free(color_parts[i]);
        i++;
    }
    free(color_parts);
}

int *get_color(char *file, char *type)
{
    int fd;
    char *row;
    int *color;

    color = ft_calloc(3, sizeof(int));
    fd = open(file, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return NULL;
    }
    row = get_next_line(fd);
    while (row) {
        if (strncmp(row, type, 1) == 0)
            get_rgb(row + 2, color);
        free(row);
        row = get_next_line(fd);
    }
    free(row);
    close(fd);
    return color;
}

//Pode estar errado
void draw_pixel_map(t_cube *cube, t_data *data)
{
    int x, y;
    int ceiling_color = (data->ceiling_color[0] << 16) | (data->ceiling_color[1] << 8) | data->ceiling_color[2];
    int floor_color = (data->floor_color[0] << 16) | (data->floor_color[1] << 8) | data->floor_color[2];
    for (y = 0; y < SCREEN_H / 2; y++) {
        for (x = 0; x < SCREEN_W; x++) {
            put_pixel(x, y, ceiling_color, cube);
        }
    }
    for (y = SCREEN_H / 2; y < SCREEN_H; y++) {
        for (x = 0; x < SCREEN_W; x++) {
            put_pixel(x, y, floor_color, cube);
        }
    }
    for (y = 0; y < SCREEN_H; y++) {
        for (x = 0; x < SCREEN_W; x++) {
            if (data->pixel_map[y][x] > 0)
                put_pixel(x, y, data->pixel_map[y][x], cube);
        }
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
    free_cube(&cube);
    return 0;
}

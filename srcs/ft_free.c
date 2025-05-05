
#include "../incs/cub3d.h"

void	ft_free_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
}

void	ft_free_tex(t_data *data)
{
	if (data->tex_north)
	{
		if (data->tex_north->img)
			mlx_destroy_image(data->mlx, data->tex_north->img);
		free(data->tex_north);
	}
	if (data->tex_south)
	{
		if (data->tex_south->img)
			mlx_destroy_image(data->mlx, data->tex_south->img);
		free(data->tex_south);
	}
	if (data->tex_east)
	{
		if (data->tex_east->img)
			mlx_destroy_image(data->mlx, data->tex_east->img);
		free(data->tex_east);
	}
	if (data->tex_west)
	{
		if (data->tex_west->img)
			mlx_destroy_image(data->mlx, data->tex_west->img);
		free(data->tex_west);
	}
}

void	ft_free(int exit_flag, t_data *data)
{
	if (data)
	{
		if (data->img)
		{
			if (data->img->img)
				mlx_destroy_image(data->mlx, data->img->img);
			free(data->img);
		}
		ft_free_tex(data);
		if (data->player)
			free(data->player);
		if (data->ray)
			free(data->ray);
		if (data->mov)
			free(data->mov);
		if (data->map)
			ft_free_map(data->map);
		if (data->win && data->mlx)
			mlx_destroy_window(data->mlx, data->win);
		if (data->mlx)
		{
			mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
		free(data);
	}
	if (exit_flag != 30 && exit_flag >= 0)
		exit (exit_flag);
	ft_printf("Fatal error: failed to malloc\n");
	if (exit_flag != -1)
		exit (1);
}

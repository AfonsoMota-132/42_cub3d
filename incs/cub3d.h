#ifndef CUB3D_H
#define CUB3D_H

//---------------------------------------------------------------------------
// Includes
// ---------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>
#include "../libs/libft/libft.h"
#include "../libs/mlx/mlx.h"
#include <stdbool.h>

// -------------------------------------------------------------------------
// Macros
// -------------------------------------------------------------------------
#define TRUE 1
#define FALSE 0

//---------------------------------------------------------------------------
// Structures
// ---------------------------------------------------------------------------

typedef struct s_map
{
	int		max_width;
	int		max_height;
	char	**map;
	char	**matrix;
}	t_map;

typedef struct s_map_data
{
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	char *F;
	char *C;
	int color_f;
	int color_c;
	int	line_position;
}	t_map_data;


typedef struct s_player
{
	int		x;
	int		y;
	double	dir_x;
	double	dir_y;
}	t_player;

typedef struct s_data
{
	int	player_count;
	char	*file;
	int		fd;
	t_map	map;
	t_player	player;
	t_map_data	map_data;
}
	t_data;


//---------------------------------------------------------------------------
// Function Prototypes
// ---------------------------------------------------------------------------
void	init_data(t_data *data, char *file);
bool	parse_map(char **map);
bool	copy_map(t_data *data, char *file);
bool	parse_textures(t_data *data);
void	rgb_int(t_data *data);
void	parse_cub_file(char *extension, char *file);
void	trim_and_check(t_data *data);
void	flood_fill(t_data *data, int x, int y);
void	find_player(t_data *data);
bool	check_flood(t_data *data);
int	size_map(char *file, t_data *data);
void	free_data(t_data *data);
void	free_rgb(char **rgb);

#endif

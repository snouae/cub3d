#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "mlx.h"

typedef struct	s_data {
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_map
{
    char    **m;
    int     leng_map;
    int     rows;
    int     big_width;
    int     top;
    int     flags;
    int     check;
    int     f[3];
    int     c[3];
    void	*mlx_ptr;
	void	*win_ptr;
    void    *image;
    t_data   data;
}	t_map;
char                *ft_strrchr(char *s, int c);
int                 ft_strcmp(char *s1, char *s2);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strchr(const char *s, int c);
int                 ft_strlen(char *s);
char				*get_next_line(int fd);
char                *ft_strdup(char *s);
char                **ft_split(char const *s, char c);
int                 ft_atoi(char *str);
void                ft_read(char *path, t_map *map);
int                 ft_check_path(t_map *map);
int                 ft_handle_map(t_map *map, int i, int *j);
int                 skip_lines(t_map *map, int i);
int                 search_way(t_map *map, char *way, int *i, int *j);
int                 skip_spaces(char *str);
int                 cherche_symbol(char c, char *str);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif 
#endif
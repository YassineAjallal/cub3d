/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:17:54 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/23 18:34:37 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	init_direction(t_cub *game, char a)
{
	if (a == 'N')
	{

	}
	else if (a == 'S')
	{

	}
	else if (a == 'E')
	{

	}
	else if (a == 'W')
	{

	}
}

void find_player(t_cub *game)
{
	int i = 0;
	int j;

	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->p_coord.x = j;
				game->p_coord.y = i;
				return;
			}
			j++;
		}
		i++;
	}
}

int rgba(int r, int g, int b, float t)
{
	int hex = (r << 24) | (g << 16) | (b << 8) | (int)(t * 255);
	return hex;
}

void parseImage(mlx_texture_t *img, int arr[512 * 512])
{
	unsigned int i = 0;
	unsigned int j = 0;
	while (i < (img->width * img->height) * img->bytes_per_pixel)
	{
		arr[j] = rgba(img->pixels[i], img->pixels[i + 1], img->pixels[i + 2], 1);
		j++;
		i += img->bytes_per_pixel;
	}
}

int alloc_textures(t_cub *game)
{
	game->textures->color_arrayE = malloc(sizeof(int) * (game->wallE->height * game->wallE->width));
	game->textures->color_arrayN = malloc(sizeof(int) * (game->wallN->height * game->wallN->width));
	game->textures->color_arrayW = malloc(sizeof(int) * (game->wallW->height * game->wallW->width));
	game->textures->color_arrayS = malloc(sizeof(int) * (game->wallS->height * game->wallS->width));
	if (!game->textures->color_arrayE || !game->textures->color_arrayN
			|| !game->textures->color_arrayW || !game->textures->color_arrayS)
		return (0);
	return (1);
}

int init_game(t_cub *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", 0);
	game->wallN = mlx_load_png(game->textures_img[NO]);
	game->wallS = mlx_load_png(game->textures_img[SO]);
	game->wallW = mlx_load_png(game->textures_img[WE]);
	game->wallE = mlx_load_png(game->textures_img[EA]);
	game->map_img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx, game->map_img, 0, 0);
	if (!alloc_textures(game))
		return (0);
	parseImage(game->wallN, game->textures->color_arrayN);
	parseImage(game->wallS, game->textures->color_arrayS);
	parseImage(game->wallW, game->textures->color_arrayW);
	parseImage(game->wallE, game->textures->color_arrayE);
	find_player(game);
	return (1);
}


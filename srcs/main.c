/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:48:49 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/01 15:48:05 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include "libft.h"
#include <limits.h>
#include <errno.h>
#include <stdio.h>


typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void draw_vline(t_data *img, int x_start, int y_start, int y_end, int color)
{
	while (y_start < y_end)
	{
		my_mlx_pixel_put(img, x_start, y_start, color);
		y_start += 1;
	}
}
void draw_hline(t_data *img, int y_start, int x_start, int x_end, int color)
{
	while (x_start < x_end)
	{
		my_mlx_pixel_put(img, x_start, y_start, color);
		x_start += 1;
	}
}


int cal_abs(int x,int y)
{
	if(y > x) return y - x;
	else return x - y;
}

int cal_max(int x,int y)
{
	if(x > y) return x;
	else return y;
}

int cal_min(int x,int y)
{
	if(x < y) return x;
	else return y;
}

// for dx > dy 
void draw_algorithm(int x0, int y0, int xn, int yn, t_data *img, int color)
{
	
	
	int xk = x0;
	int yk = y0;
	int	dx = cal_abs(x0,xn);
	int dy = cal_abs(y0,yn);
	int step;
	if(yn > y0) {
		step = 1;
	}
	else {
		step = -1;
	}
	int decision_parameter = 2*dy - dx;

	while(xk <= xn) {
		my_mlx_pixel_put(img, xk, yk, color);
		xk += 1;
		if(decision_parameter < 0){
			decision_parameter = decision_parameter + (2*dy);
		} else {
			decision_parameter = decision_parameter + (2*dy) - (2*dx);
			yk += step;
		}
	}
}

// for dy > dx
void draw_algorithm_2(int x0, int y0, int xn, int yn, t_data *img, int color)
{
	
	
	int xk = x0;
	int yk = y0;
	int	dx; // cal dx -> not cal dx 
	int dy = cal_abs(y0,yn); //not cal dx -> calc dy 
	int step;
	if(xn > x0) { // yn > xn
		dx = xn-x0; // swap dy-dx
		step = 1;
	}
	else {
		dx = x0-xn; // swap dy->dx
		step = -1;
	}
	int decision_parameter = 2*dx - dy;
	
	while(yk <= yn) { 
		//xk <= xn
		my_mlx_pixel_put(img, xk, yk, color); // same
		yk += 1;
		if(decision_parameter < 0){
			decision_parameter = decision_parameter + (2*dx); // swap dy -> dx
		} else {
			decision_parameter = decision_parameter + (2*dx) - (2*dy); // swap dy->dx and dx->dy
			xk += step;
		}
	}
}

// Generalize Draw line Algorithm 


void draw_algorithm_3(int x0, int y0, int xn, int yn, t_data *img, int color)
{
	int	dx = cal_abs(x0,xn);
	int dy = cal_abs(y0,yn);
	int step = 1;

	// #2 Calc step
	int primary_k;
	int primary_n;
	int secondary_k;
	int dp = cal_max(dx,dy);
	int ds = cal_min(dx,dy);
	if(dx >= dy) {
		primary_k = x0;
		secondary_k=y0;
		primary_n = xn;
		if(yn < y0) step = -1;
	} else {
		primary_k = y0;
		primary_n = yn;
		secondary_k = x0;
		if(xn < x0) step = -1;
	}

	int decision_parameter = 2*ds - dp;
	while(primary_k <= primary_n) { // change** yk <= yn
		if(dx >= dy)
			my_mlx_pixel_put(img, primary_k, secondary_k, color);
		else 
			my_mlx_pixel_put(img, secondary_k, primary_k, color);
		primary_k += 1; // ***change
		if(decision_parameter < 0){
			decision_parameter = decision_parameter + (2*ds);
		} else {
			decision_parameter = decision_parameter + (2*ds) - (2*dp);
			secondary_k += step; // ***change
		}
	}
}

void draw_algorithm_4(int *start, int *end, t_data *img, int color)
{
	int	dx = cal_abs(start[0],end[0]);
	int dy = cal_abs(start[1],end[1]);
	int step = 1;

	// #2 Calc step
	int primary_k;
	int primary_n;
	int secondary_k;
	int dp = cal_max(dx,dy);
	int ds = cal_min(dx,dy);
	if(dx >= dy) {
		primary_k = start[0]; //x0
		secondary_k=start[1]; //yn
		primary_n = end[0]; // xn
		if(end[1] < start[1]) step = -1;
	} else {
		primary_k = start[1]; //y0
		primary_n = end[1]; // yn
		secondary_k = start[0]; // x0
		if(end[0] < start[0]) step = -1;
	}

	int decision_parameter = 2*ds - dp;
	while(primary_k <= primary_n) { // change** yk <= yn
		if(dx >= dy)
			my_mlx_pixel_put(img, primary_k, secondary_k, color);
		else 
			my_mlx_pixel_put(img, secondary_k, primary_k, color);
		primary_k += 1; // ***change
		if(decision_parameter < 0){
			decision_parameter = decision_parameter + (2*ds);
		} else {
			decision_parameter = decision_parameter + (2*ds) - (2*dp);
			secondary_k += step; // ***change
		}
	}
}



t_map	*map_init()
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if(!map) 
		terminate(ERR_MAP_INIT);
	ft_bzero(map, sizeof(t_map));
	map->width = WIDTH;
	map->height = HEIGHT;
	map->coords_arr = NULL;
	map->colors_arr = NULL;
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	map->z_range = 0;
	return (map);
}


int main(void)
{
	void *mlx;
	void *mlx_win;
	t_data img;

	// MAP
	// t_map	*map;
	// map = map_init();

	
	

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);

	int node_1[2] = {200,200};
	int node_2[2] = {800,200};


	draw_algorithm_4(node_1,node_2,&img,0x00FF0000);
	draw_algorithm_3(200,800,800,800,&img,0x00FF0000);

	draw_algorithm_3(200,200,200,800,&img,0x00FF0000);
	draw_algorithm_3(800,200,800,800,&img,0x00FF0000);


	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

// 	while (y_start < y_end)
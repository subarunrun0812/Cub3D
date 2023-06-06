/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:36:04 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/06 14:50:48 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

ray_2	*create_ray_2(vector_2 *start_p, vector_2 *direction)
{
	ray_2	*ray;

	ray = malloc(sizeof(ray_2));
	if (ray == NULL)
	{
		write(STDERR_FILENO, "error: failed malloc.", 21);
		exit(1);
	}
	ray->start_point = start_p;
	ray->direction = direction;
	return (ray);
}

vector_2	*point_at_ray_2(ray_2 *ray, float t)
{
	vector_2	*point;
	
	point = add_vector_2(ray->start_point, multi_scalar_vector_2(ray->direction, t));
	return (point);
}

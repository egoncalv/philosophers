/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoncalv <egoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:33:26 by egoncalv          #+#    #+#             */
/*   Updated: 2023/01/11 16:33:29 by egoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time_ms()
{
	static struct timeval	start_time;
	struct timeval			current_time;
	static int				start_ms;
	int						current_ms;
	if (!start_ms)
	{
		gettimeofday(&start_time, NULL);
		start_ms = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	}
	gettimeofday(&current_time, NULL);
	current_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (current_ms - start_ms);
}

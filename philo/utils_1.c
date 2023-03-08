/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoncalv <egoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:35:26 by egoncalv          #+#    #+#             */
/*   Updated: 2023/03/08 19:26:54 by egoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	drop_forks(t_phi *phi)
{
	pthread_mutex_lock(&phi->l_fork->mutex);
	phi->l_fork->taken = 0;
	pthread_mutex_unlock(&phi->l_fork->mutex);
	pthread_mutex_lock(&phi->r_fork->mutex);
	phi->r_fork->taken = 0;
	pthread_mutex_unlock(&phi->r_fork->mutex);
}

void	take_fork(t_phi *phi, t_fork *fork)
{
	while (!is_dead(phi))
	{
		pthread_mutex_lock(&fork->mutex);
		if (!fork->taken)
		{
			fork->taken = 1;
			pthread_mutex_unlock(&fork->mutex);
			break ;
		}
		pthread_mutex_unlock(&fork->mutex);
	}
	print_action(phi, "has taken a fork");
}

void	print_action(t_phi *philosopher, char *action)
{
	pthread_mutex_lock(&philosopher->info->print_lock);
	if (!is_dead(philosopher))
		printf("%lld\t%d %s\n", get_time_ms(), philosopher->id, action);
	pthread_mutex_unlock(&philosopher->info->print_lock);
}

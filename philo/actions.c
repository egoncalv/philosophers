/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoncalv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:47:58 by egoncalv          #+#    #+#             */
/*   Updated: 2023/02/13 14:48:00 by egoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*choose_action(void *philosopher)
{
	t_phi	*phi;

	phi = (t_phi *)philosopher;
	while (!is_dead(phi))
	{
		if (phi->id % 2)
			usleep(15000);
		eat_action(philosopher);
		sleep_action(philosopher);
		printf("%d\t%d is thinking\n", get_time_ms(), phi->id);
	}
	printf("%d\t%d is dead\n", get_time_ms(), phi->id);
	return (NULL);
}

int	is_dead(t_phi *phi)
{
	if ((get_time_ms() - phi->last_meal) > phi->info->t_die)
		return (1);
	return (0);
}

void	sleep_action(t_phi *phi)
{
	int	time_sleeping;

	time_sleeping = 0;
	printf("%d\t%d is sleeping\n", get_time_ms(), phi->id);
	while (!is_dead(phi) && time_sleeping < phi->info->t_sleep)
	{
		usleep(1000);
		time_sleeping++;
	}
	if (is_dead(phi))
		printf("%d\t%d is dead\n", get_time_ms(), phi->id);
}

void	eat_action(t_phi *phi)
{
	pthread_mutex_lock(&phi->r_fork->mutex);
	printf("%d\t%d has taken a fork\n", get_time_ms(), phi->id);
	pthread_mutex_lock(&phi->l_fork->mutex);
	printf("%d\t%d has taken a fork\n", get_time_ms(), phi->id);
	printf("%d\t%d is eating\n", get_time_ms(), phi->id);
	usleep(phi->info->t_eat * 1000);
	phi->last_meal = get_time_ms();
	phi->x_ate++;
	pthread_mutex_unlock(&phi->r_fork->mutex);
	pthread_mutex_unlock(&phi->l_fork->mutex);
}

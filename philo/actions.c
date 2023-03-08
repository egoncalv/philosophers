/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoncalv <egoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:47:58 by egoncalv          #+#    #+#             */
/*   Updated: 2023/03/08 20:43:16 by egoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*choose_action(void *philosopher)
{
	t_phi	*phi;

	phi = (t_phi *)philosopher;
	if (phi->id % 2)
		usleep(15000);
	while (!is_dead(phi))
	{
		eat_action(philosopher);
		pthread_mutex_lock(&phi->info->print_lock);
		if (phi->info->all_completed || phi->death->is_dead == 1)
		{
			pthread_mutex_unlock(&phi->info->print_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&phi->info->print_lock);
		sleep_action(philosopher);
		print_action(philosopher, "is thinking");
	}
	return (NULL);
}

int	is_dead(t_phi *phi)
{
	pthread_mutex_lock(&phi->death->d_lock);
	if (phi->death->is_dead == 1)
	{
		pthread_mutex_unlock(&phi->death->d_lock);
		return (1);
	}
	else if ((get_time_ms() - phi->last_meal) >= phi->info->t_die)
	{
		phi->death->is_dead = 1;
		printf("%lld\t%d died\n", get_time_ms(), phi->id);
		pthread_mutex_unlock(&phi->death->d_lock);
		return (1);
	}
	pthread_mutex_unlock(&phi->death->d_lock);
	return (0);
}

void	sleep_action(t_phi *phi)
{
	int	start_time;

	print_action(phi, "is sleeping");
	start_time = get_time_ms();
	while (!is_dead(phi))
	{
		if (get_time_ms() - start_time > phi->info->t_sleep)
			break ;
		usleep(100);
	}
}

int	eat_action(t_phi *phi)
{
	int	start_time;

	take_fork(phi, phi->r_fork);
	take_fork(phi, phi->l_fork);
	print_action(phi, "is eating");
	phi->last_meal = get_time_ms();
	start_time = get_time_ms();
	while (!is_dead(phi))
	{
		if (get_time_ms() - start_time > phi->info->t_eat)
			break ;
		usleep(100);
	}
	pthread_mutex_lock(&phi->info->print_lock);
	phi->x_ate++;
	if (phi->x_ate == phi->info->x_eat)
		phi->info->x_completed++;
	if (phi->info->x_completed == phi->info->p_num)
		phi->info->all_completed = 1;
	pthread_mutex_unlock(&phi->info->print_lock);
	drop_forks(phi);
	return (0);
}

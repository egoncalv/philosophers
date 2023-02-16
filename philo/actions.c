/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoncalv <egoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:47:58 by egoncalv          #+#    #+#             */
/*   Updated: 2023/02/16 17:56:55 by egoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*choose_action(void *philosopher)
{
	t_phi	*phi;

	phi = (t_phi *)philosopher;
	while (!is_dead(phi))
	{
		if (!phi->id % 2)
			usleep(15000);
		eat_action(philosopher);
		sleep_action(philosopher);
		print_action(philosopher, "is thinking");
		pthread_mutex_lock(&phi->info->print_lock);
		if (phi->info->all_completed)
		{
			pthread_mutex_unlock(&phi->info->print_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&phi->info->print_lock);
	}
	return (NULL);
}

int	is_dead(t_phi *phi)
{
	pthread_mutex_lock(&phi->info->print_lock);
	if (phi->info->dead == 1)
		return (1);
	if ((get_time_ms() - phi->last_meal) >= phi->info->t_die)
	{
		phi->info->dead = 1;
		printf("%d\t%d died\n", get_time_ms(), phi->id);
		return (1);
	}
	pthread_mutex_unlock(&phi->info->print_lock);
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
	}
}

int	eat_action(t_phi *phi)
{
	int	start_time;

	take_fork(phi, phi->l_fork);
	take_fork(phi, phi->r_fork);
	print_action(phi, "is eating");
	phi->last_meal = get_time_ms();
	start_time = get_time_ms();
	while (get_time_ms() - start_time < phi->info->t_eat)
		;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoncalv <egoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:47:58 by egoncalv          #+#    #+#             */
/*   Updated: 2023/02/15 18:36:53 by egoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_phi *philosopher, char *action)
{
	if (philosopher->info->dead == 1)
	{
		pthread_mutex_lock(&philosopher->info->print_lock);
		printf("%d\t%d %s\n", get_time_ms(), philosopher->id, action);
	}
	else
		printf("%d\t%d %s\n", get_time_ms(), philosopher->id, action);
}

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
		print_action(philosopher, "is thinking");
	}
	return (NULL);
}

int	is_dead(t_phi *phi)
{
	if ((get_time_ms() - phi->last_meal) > phi->info->t_die)
	{
		phi->info->dead = 1;
		print_action(phi, "died");
		return (1);
	}
	return (0);
}

void	sleep_action(t_phi *phi)
{
	int	start_time;
		
	print_action(phi, "is sleeping");
	start_time = get_time_ms();
	while (!is_dead(phi))
	{
		if (get_time_ms() - start_time >= phi->info->t_sleep)
			break ;
	}
}

void	eat_action(t_phi *phi)
{
	int	start_time;

	while (!is_dead(phi))
	{
			pthread_mutex_lock(&phi->r_fork->mutex);
			if (!phi->r_fork->taken)
			{
				phi->r_fork->taken = 1;
				pthread_mutex_unlock(&phi->r_fork->mutex);
				break ;
			}
			pthread_mutex_unlock(&phi->r_fork->mutex);
	}
	print_action(phi, "has taken a fork");
	while (!is_dead(phi))
	{
			pthread_mutex_lock(&phi->l_fork->mutex);
			if (!phi->l_fork->taken)
			{
				phi->l_fork->taken = 1;
				pthread_mutex_unlock(&phi->l_fork->mutex);
				break ;
			}
			pthread_mutex_unlock(&phi->l_fork->mutex);
	}
	print_action(phi, "has taken a fork");
	print_action(phi, "is eating");
	start_time = get_time_ms();
	while (get_time_ms() - start_time < phi->info->t_eat)
		;
	phi->last_meal = get_time_ms();
	phi->x_ate++;
	pthread_mutex_lock(&phi->l_fork->mutex);
	phi->l_fork->taken = 0;
	pthread_mutex_unlock(&phi->l_fork->mutex);
	pthread_mutex_lock(&phi->r_fork->mutex);
	phi->r_fork->taken = 0;
	pthread_mutex_unlock(&phi->r_fork->mutex);
}

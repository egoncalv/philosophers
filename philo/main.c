/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoncalv <egoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:33:40 by egoncalv          #+#    #+#             */
/*   Updated: 2023/01/26 10:42:36 by egoncalv         ###   ########.fr       */
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

int		is_dead(t_phi *phi)
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

t_fork	*create_fork(void)
{
	t_fork				*fork;
	static int			i;

	fork = malloc(sizeof(t_fork));
	fork->id = i;
	fork->taken = 0;
	pthread_mutex_init(&fork->mutex, NULL);
	i++;
	return (fork);
}

//Remember to specify if there is only one philosopher, create only one fork
t_phi	**create_phi(t_info *info)
{
	t_phi		**philosophers;
	t_fork		*right_fork;
	t_fork		*left_fork;
	int			i;

	i = 0;
	philosophers = malloc(sizeof(t_phi) * info->p_num + 1);
	left_fork = 0;
	while (i < info->p_num)
	{
		philosophers[i] = malloc(sizeof(t_phi));
		philosophers[i]->id = i;
		philosophers[i]->last_meal = 0;
		philosophers[i]->x_ate = 0;
		philosophers[i]->info = info;
		right_fork = create_fork();
		philosophers[i]->r_fork = right_fork;
		philosophers[i]->l_fork = left_fork;
		left_fork = right_fork;
		i++;
	}
	philosophers[0]->l_fork = right_fork;
	i = -1;
	while (++i < info->p_num)
		pthread_create(&philosophers[i]->tid, NULL, choose_action, philosophers[i]);
	return (philosophers);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_phi		**philosophers;

	get_time_ms();
	if (check_args(argc, argv))
	{
		set_info(&info, argv);
		philosophers = create_phi(&info);
	}
	for (int i = 0; i < info.p_num; i++)
		pthread_join(philosophers[i]->tid, NULL);
	return (1);
}

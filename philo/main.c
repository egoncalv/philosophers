/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoncalv <egoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:33:40 by egoncalv          #+#    #+#             */
/*   Updated: 2023/01/21 17:14:02 by egoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*choose_action(void *philosopher)
{
	t_phi	*phi;

	phi = (t_phi *)philosopher;
	if (phi->id % 2)
		usleep(10000);
	eat_action(philosopher);
	printf("%d\t", get_time_ms());
	printf("%d is sleeping\n", phi->id);
	usleep(1000000);
	return (philosopher);
}

void	eat_action(t_phi *phi)
{
	pthread_mutex_lock(&phi->r_fork->mutex);
	printf("%d\t", get_time_ms());
	printf("%d has taken a fork\n", phi->id);
	pthread_mutex_lock(&phi->l_fork->mutex);
	printf("%d\t", get_time_ms());
	printf("%d has taken a fork\n", phi->id);
	printf("%d\t", get_time_ms());
	printf("%d is eating\n", phi->id);
	usleep(phi->info->t_eat * 1000);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoncalv <egoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:37:32 by egoncalv          #+#    #+#             */
/*   Updated: 2023/02/13 15:05:19 by egoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	thread_create_join(info, philosophers);
	return (philosophers);
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

void	thread_create_join(t_info *info, t_phi **phi)
{
	int	i;

	i = -1;
	while (++i < info->p_num)
		pthread_create(&phi[i]->tid, NULL, choose_action, phi[i]);
	i = -1;
	while (++i < info->p_num)
		pthread_join(phi[i]->tid, NULL);
}

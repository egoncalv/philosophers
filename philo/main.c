/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoncalv <egoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:33:40 by egoncalv          #+#    #+#             */
/*   Updated: 2023/01/13 18:38:25 by egoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	*thread_function(void *i)
{
	int	*idx;

	idx = (int *)i;
	idx++;
	i = idx;
	return (i);
}

t_fork	*create_fork()
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

t_phi	**create_phi(int p_num)
{
	t_phi		**philosophers;
	t_fork		*right_fork;
	t_fork		*left_fork;
	int			i;

	i = 0;
	philosophers = malloc(sizeof(t_phi *) * p_num + 1);
	left_fork = 0;
	while (i < p_num)
	{
		philosophers[i] = malloc(sizeof(t_phi));
		pthread_create(&philosophers[i]->tid, NULL, thread_function, &i);
		right_fork = create_fork();
		philosophers[i]->r_fork = right_fork;
		philosophers[i]->l_fork = left_fork;
		left_fork = right_fork;
		i++;
	}
	philosophers[0]->l_fork = right_fork;
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
		philosophers = create_phi(info.p_num);
	}
	for(int i = 0; i < info.p_num; i++)
	{
		printf("Philosopher %d ", i);
		printf("has left fork %d", philosophers[i]->l_fork->id);
		printf("and right fork %d\n", philosophers[i]->r_fork->id);
	}
	return (1);
}

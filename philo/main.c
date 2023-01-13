/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoncalv <egoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:33:40 by egoncalv          #+#    #+#             */
/*   Updated: 2023/01/13 14:51:37 by egoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	*thread_function(void * i)
{
	
	int				*idx;
	
	idx = (int *)i;
	printf("%d\tThis is thread %d\n", get_time_ms(), *idx);
	idx++;
	i = idx;
	return (i);
}

t_fork	*create_fork(void)
{
	t_fork		*fork;
	static int	i;

	fork = malloc(sizeof(t_fork));
	fork->id = i;
	pthread_mutex_init(&fork->mutex, NULL);
	return (fork);
}

t_phi	*create_phi(void)
{
	t_phi		*phi;
	static int	i;

	phi = malloc(sizeof(t_phi));
	phi->tid = 0;
	pthread_create(&phi->tid, NULL, thread_function, &i);
	i++;
	return (phi);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_phi		**philosophers;
	t_fork		**forks;
	int			i;

	get_time_ms();
	if (check_args(argc, argv))
	{
		set_info(&info, argv);
		
		philosophers = malloc(sizeof(t_phi *) * info.p_num + 1);
		forks =  malloc(sizeof(t_fork *) * info.p_num + 1);
		i = 0;
		while (i < info.p_num)
		{
			forks[i] = create_fork();
			philosophers[i] = create_phi();
			i++;
		}
		//pthread_exit(NULL);
	}
	return (1);
}

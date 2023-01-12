/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoncalv <egoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:33:40 by egoncalv          #+#    #+#             */
/*   Updated: 2023/01/12 23:52:33 by egoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_function(void * i)
{
	pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
	int				*idx;
	
	idx = (int *)i;
	pthread_mutex_lock(&mutex1);
	printf("%dms\tThis is thread %d\n", get_time_ms(), *idx);
	idx++;
	i = idx;
	pthread_mutex_unlock(&mutex1);
	return (i);
}

t_phi	create_phi(void)
{
	t_phi		phi;
	static int	i;

	phi.tid = 0;
	pthread_create(&phi.tid, NULL, thread_function, &i);
	i++;
	return (phi);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_phi		*philosophers;
	int			i;

	i = 0;
	get_time_ms();
	if (check_args(argc, argv))
	{
		set_info(&info, argv);
		
		philosophers = malloc(sizeof(t_phi *) * info.p_num);
		while (i < info.p_num)
		{
			philosophers[i] = create_phi();
			i++;
		}
	}
	pthread_exit(NULL);
	return (1);
}

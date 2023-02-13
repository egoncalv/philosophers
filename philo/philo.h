/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoncalv <egoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:22:51 by egoncalv          #+#    #+#             */
/*   Updated: 2023/02/13 14:58:27 by egoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>

typedef struct s_info
{
	int	p_num;
	int	f_num;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	x_eat;
	int	dead;
}				t_info;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				id;
	int				taken;
}				t_fork;

typedef struct s_phi
{
	t_info		*info;
	pthread_t	tid;
	int			id;
	int			last_meal;
	int			x_ate;
	t_fork		*l_fork;
	t_fork		*r_fork;
}				t_phi;

void	free_all(t_info *info, t_phi **philosophers);
int		get_time_ms(void);
int		ft_atoi(const char *str);
int		is_nbr(char	*argv);
int		check_args(int argc, char **argv);
void	set_info(t_info *info, char	**argv);
void	eat_action(t_phi *phi);
void	sleep_action(t_phi *phi);
int		is_dead(t_phi *phi);
t_phi	**create_phi(t_info *info);
t_fork	*create_fork(void);
void	thread_create_join(t_info *info, t_phi **phi);
void	*choose_action(void *philosopher);
int		is_dead(t_phi *phi);
void	sleep_action(t_phi *phi);
void	eat_action(t_phi *phi);

#endif

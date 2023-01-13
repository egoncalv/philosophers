/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoncalv <egoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:22:51 by egoncalv          #+#    #+#             */
/*   Updated: 2023/01/13 18:24:35 by egoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>

typedef struct s_info
{
	int	p_num;
	int	f_num;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	x_eat;
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
	t_fork		*l_fork;
	t_fork		*r_fork;
}				t_phi;

int		get_time_ms(void);
int		ft_atoi(const char *str);
int		is_nbr(char	*argv);
int		check_args(int argc, char **argv);
void	set_info(t_info *info, char	**argv);

#endif

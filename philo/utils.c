/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoncalv <egoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:33:26 by egoncalv          #+#    #+#             */
/*   Updated: 2023/01/12 16:44:21 by egoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time_ms(void)
{
	static struct timeval	start_time;
	struct timeval			current_time;
	static int				start_ms;
	int						current_ms;

	if (!start_ms)
	{
		gettimeofday(&start_time, NULL);
		start_ms = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	}
	gettimeofday(&current_time, NULL);
	current_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (current_ms - start_ms);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	return (res * sign);
}

int	is_nbr(char	*argv)
{
	int	i;

	i = -1;
	if (argv[0] == '-' || argv[0] == '+')
		i++;
	while (argv[++i])
		if (argv[i] < 48 || argv[i] > 57)
			return (0);
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (!(argc == 5 || argc == 6))
	{
		printf("Wrong Number of Arguments\n");
		return (0);
	}
	while (i < argc)
	{
		if (!ft_atoi(argv[i]))
		{
			printf("Arguments must be numeric and higher than 0\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	set_info(t_info *info, char	**argv)
{	
	info->p_num = ft_atoi(argv[1]);
	info->f_num = info->p_num;
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		info->x_eat = ft_atoi(argv[5]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoncalv <egoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:33:40 by egoncalv          #+#    #+#             */
/*   Updated: 2023/02/15 14:05:32 by egoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info		info;
	t_phi		**philosophers;

	
	if (check_args(argc, argv))
	{
		set_info(&info, argv);
		philosophers = create_phi(&info);
		free_all(&info, philosophers);
	}
	return (1);
}

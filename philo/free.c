/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoncalv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:36:00 by egoncalv          #+#    #+#             */
/*   Updated: 2023/02/13 14:36:01 by egoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_info *info, t_phi **philosophers)
{
	int	i;

	i = 0;
	while (i < info->p_num)
	{
		free(philosophers[i]->r_fork);
		free(philosophers[i]);
		i++;
	}
	free(philosophers);
}

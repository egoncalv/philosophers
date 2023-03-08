/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoncalv <egoncalv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:36:00 by egoncalv          #+#    #+#             */
/*   Updated: 2023/03/08 20:41:01 by egoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_info *info, t_phi **philosophers)
{
	int	i;

	i = 0;
	free(info->death);
	while (i < info->p_num)
	{
		free(philosophers[i]->r_fork);
		free(philosophers[i]);
		i++;
	}
	free(philosophers);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 19:20:21 by cfargere          #+#    #+#             */
/*   Updated: 2019/08/20 16:17:49 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @desc			2nd part of the sort function
*/

static void		comb_sort2(int *order, float *dist, int i[2], int *swapped)
{
	int		tmp;

	if (dist[i[0]] < dist[i[1]])
	{
		tmp = dist[i[0]];
		dist[i[0]] = dist[i[1]];
		dist[i[1]] = tmp;
		tmp = (float)order[i[0]];
		order[i[0]] = order[i[1]];
		order[i[1]] = (int)tmp;
		*swapped = 1;
	}
}

/*
** @desc			sort function (used to sort sprites by distance)
*/

void			comb_sort(int *order, float *dist, int amount)
{
	int		i[2];
	int		gap;
	int		swapped;

	gap = amount;
	swapped = 0;
	while (gap > 1 || swapped)
	{
		gap = (gap * 10) / 13;
		if (gap == 9 || gap == 10)
			gap = 11;
		if (gap < 1)
			gap = 1;
		swapped = 0;
		i[0] = 0;
		while (i[0] < amount - gap)
		{
			i[1] = i[0] + gap;
			comb_sort2(order, dist, i, &swapped);
			i[0]++;
		}
	}
}

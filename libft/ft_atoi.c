/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amecani <amecani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:20:18 by amecani           #+#    #+#             */
/*   Updated: 2023/10/30 12:31:28 by amecani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *bomba)
{
	int	i;
	int	charge;
	int	result;

	i = 0;
	charge = 1;
	result = 0;
	while (bomba[i] && (bomba[i] == ' ' || bomba[i] == '\t'
			|| bomba[i] == '\n' || bomba[i] == '\r'
			|| bomba[i] == '\f' || bomba[i] == '\v'))
		i++;
	if (bomba[i] && (bomba[i] == '-' || bomba[i] == '+'))
	{
		if (bomba[i] == '-')
		{
			charge *= -1;
		}
		i++;
	}
	while (bomba[i] && (bomba[i] <= '9' && bomba[i] >= '0'))
	{
		result = result * 10 + (bomba[i] - 48);
		i++;
	}
	return (result * charge);
}

// #include <stdio.h>
// int main()
// {
//     const char bomba[] = "---123";
//     printf("%d",ft_atoi(bomba));
//     return (0);
// }
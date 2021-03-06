/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnila <mnila@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 21:47:12 by mnila             #+#    #+#             */
/*   Updated: 2019/12/06 22:26:55 by mnila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memset(char *s, char c, int n)
{
	int i;

	i = 0;
	while (n--)
	{
		s[i++] = c;
	}
	return (s);
}

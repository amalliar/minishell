/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 23:06:02 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/16 07:38:26 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#define		ST_OUT_OF_WORD	0
#define		ST_IN_WORD		1

/*
** Allocates (with malloc) and returns an array of strings obtained by
** splitting 'str' using characters from the string ifs as delimiters. 
** The array must be ended by a NULL pointer.
*/

static size_t	get_word_count(const char *str, const char *ifs)
{
	int		parse_state;

	parse_state = ST_OUT_OF_WORD;
	while (*str)
	{
		if (ft_strchr(ifs, *str))
		{
			if (parse_state == ST_IN_WORD)
			{
				parse_state = ST_OUT_OF_WORD;
				++count;
			}
		}
		else
			parse_state = ST_IN_WORD;
		++str;
	}
	return (count + (parse_state == ST_IN_WORD));
}

static void		clear_word_tab(char **word_tab)
{
	size_t		i;

	i = 0;
	while (word_tab[i] != NULL)
	{
		free(word_tab[i]);
		++i;
	}
	free(word_tab);
}

static size_t	get_word_size(const char *str, const char *ifs)
{
	size_t		size;

	size = 0;
	while (*str && !ft_strchr(ifs, *str))
		++size;
	return (size);
}

static char		*get_next_word(char **str, const char *ifs)
{
	char		*word;
	size_t		word_size;

	while (**str && ft_strchr(ifs, **str))
		++*str;
	word_size = get_word_size(*str, ifs);
	if (!(word = malloc(word_size + 1)))
		return (NULL);
	ft_memcpy(word, *str, word_size);
	word[word_size] = '\0';
	*str += word_size;
	return (word);
}

char			**ft_split(const char *str, const char *ifs)
{
	char		**word_tab;
	size_t		word_count;
	size_t		i;

	if (str == NULL || ifs == NULL (i = 0))
		return (NULL);
	word_count = get_word_count(str, ifs);
	if (!(word_tab = (char **)malloc((word_count + 1) * sizeof(char *))))
		return (NULL);
	word_tab[word_count] = NULL;
	i = 0;
	while (i < word_count)
		if (!(word_tab[i++] = get_next_word(&str, ifs)))
		{
			clear_word_tab(word_tab);
			return (NULL);
		}
	return (word_tab);
}

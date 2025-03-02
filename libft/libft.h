/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 02:55:46 by yhadhadi          #+#    #+#             */
/*   Updated: 2025/03/02 01:04:31 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdalign.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdint.h>
# include <limits.h>
# include <math.h>

typedef unsigned char	t_byte;

# define NIL			0

# define FLOW_CONTINUE	-1
# define FLOW_BREAK		0
# define FLOW_ITERATE	1

int		ft_abs(int nbr);
int		ft_atoi(const char *str)
		__attribute__((nonnull(1)));
long	ft_atol(const char *str)
		__attribute__((nonnull(1)));
void	ft_bzero(void *mem, size_t n)
		__attribute__((nonnull(1)));
void	*ft_calloc(size_t n, size_t siz)
		__attribute__((malloc));
int		ft_isalnum(int chr);
int		ft_isalpha(int chr);
int		ft_isascii(int chr);
int		ft_isdigit(int chr);
int		ft_isgraph(int chr);
int		ft_isprint(int chr);
int		ft_ispunct(int chr);
int		ft_isspace(int chr);
char	*ft_itoa_base(int nbr, char *base)
		__attribute__((nonnull(2), malloc));
char	*ft_itoa(int nbr)
		__attribute__((malloc));
long	ft_labs(long nbr);
void	*ft_memchr(const void *mem, int val, size_t n)
		__attribute__((nonnull(1)));
int		ft_memcmp(const void *s1, const void *s2, size_t n)
		__attribute__((nonnull(1, 2)));
void	*ft_memcpy(void *dst, const void *src, size_t n)
		__attribute__((nonnull(1, 2)));
void	*ft_memmove(void *dst, const void *src, size_t n)
		__attribute__((nonnull(1, 2)));
void	*ft_memset(void *mem, int val, size_t n)
		__attribute__((nonnull(1)));
int		ft_memswap(void *m1, void *m2, size_t n)
		__attribute__((nonnull(1, 2)));
int		ft_putchar_fd(char chr, int fd);
int		ft_putendl_fd(char *str, int fd)
		__attribute__((nonnull(1)));
int		ft_putnbr_fd(int nbr, int fd);
int		ft_putstr_fd(char *str, int fd)
		__attribute__((nonnull(1)));
int		ft_radix(char *base)
		__attribute__((nonnull(1)));
void	*ft_realloc(void *mem, size_t n, size_t siz)
		__attribute__((malloc));
char	**ft_split(const char *str, char sep)
		__attribute__((nonnull(1), malloc));
char	*ft_strchr(const char *str, int chr)
		__attribute__((nonnull(1)));
int		ft_strcmp(const char *s1, const char *s2)
		__attribute__((nonnull(1, 2)));
size_t	ft_strcspn(const char *str, const char *reject)
		__attribute__((nonnull(1, 2)));
char	*ft_strdup(const char *str)
		__attribute__((nonnull(1), malloc));
void	ft_striteri(char *str, int (*apply)(size_t *, char **, void *),
			void *yld)
		__attribute__((nonnull(1, 2)));
char	*ft_strjoin(const char *s1, const char *s2)
		__attribute__((nonnull(1, 2), malloc));
size_t	ft_strlcat(char *dst, const char *src, size_t siz)
		__attribute__((nonnull(1, 2)));
size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
		__attribute__((nonnull(1, 2)));
size_t	ft_strlen(const char *str)
		__attribute__((nonnull(1)));
char	*ft_strmapi(const char *str, char (*apply)(size_t, char))
		__attribute__((nonnull(1, 2), malloc));
int		ft_strncmp(const char *s1, const char *s2, size_t n)
		__attribute__((nonnull(1, 2)));
char	*ft_strnstr(const char *str, const char *pat, size_t n)
		__attribute__((nonnull(1, 2)));
char	*ft_strpbrk(const char *str, const char *accept)
		__attribute__((nonnull(1, 2)));
char	*ft_strrchr(const char *str, int chr)
		__attribute__((nonnull(1)));
char	*ft_strrev(char *str)
		__attribute__((nonnull(1)));
size_t	ft_strcspn(const char *str, const char *reject)
		__attribute__((nonnull(1, 2)));
char	*ft_strtrim(const char *str, const char *set)
		__attribute__((nonnull(1, 2), malloc));
char	*ft_substr(const char *str, size_t idx, size_t sub_len)
		__attribute__((nonnull(1), malloc));
int		ft_tolower(int chr);
int		ft_toupper(int chr);
char	*ft_ultoa_base(unsigned long nbr, char *base)
		__attribute__((nonnull(2), malloc));
char	*ft_utoa_base(unsigned int nbr, char *base)
		__attribute__((nonnull(2), malloc));
char	*ft_utoa(unsigned int nbr)
		__attribute__((malloc));
void	ft_vstriteri(char *str, int (*apply)(size_t *, char **, va_list *,
				void *), void *yld, ...)
		__attribute__((nonnull(1, 2)));

# ifndef NO_LIBFT_BONUS

typedef struct s_node
{
	void			*data;
	struct s_node	*prev;
	struct s_node	*next;
}	t_list;

typedef struct s_stack
{
	void	**cntnr;
	size_t	cap;
	size_t	siz;
	size_t	top;
	size_t	bot;
}	t_stack;

void	ft_lstadd_back(t_list **lst, t_list *node)
		__attribute__((nonnull(2)));
void	ft_lstadd_front(t_list **lst, t_list *node)
		__attribute__((nonnull(2)));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *node, void (*del)(void*))
		__attribute__((nonnull(1)));
void	ft_lstiter(t_list *lst, void (*apply)(void *))
		__attribute__((nonnull(1, 2)));
t_list	*ft_lstlast(t_list *lst)
		__attribute__((nonnull(1)));
t_list	*ft_lstmap(t_list *lst, void *(*apply)(void *), void (*del)(void *))
		__attribute__((nonnull(2)));
t_list	*ft_lstnew(void *data)
		__attribute__((malloc));
int		ft_lstsize(t_list *lst);
void	ft_stackclear(t_stack *stack, void (*del)(void*))
		__attribute__((nonnull(1)));
t_stack	*ft_stacknew(size_t cap)
		__attribute__((malloc));
void	*ft_stackpeek(t_stack *stack)
		__attribute__((nonnull(1)));
int		ft_stackpop(void **data, t_stack *stack)
		__attribute__((nonnull(2)));
int		ft_stackpop_first(void **data, t_stack *stack)
		__attribute__((nonnull(2)));
int		ft_stackpush(t_stack *stack, void *data)
		__attribute__((nonnull(1, 2)));
int		ft_stackpush_back(t_stack *stack, void *data)
		__attribute__((nonnull(1, 2)));
int		ft_stackrot(t_stack *stack)
		__attribute__((nonnull(1)));
int		ft_stackrrot(t_stack *stack)
		__attribute__((nonnull(1)));
int		ft_stackswap(t_stack *stack)
		__attribute__((nonnull(1)));
# endif

# ifndef NO_LIBFT_ADDONS

int		ft_printf(const char *fmt, ...)
		__attribute__((format(printf, 1, 2)));
int		ft_vasprintf(char **buf, const char *fmt, va_list *vargs)
		__attribute__((format(printf, 2, 0)));
int		ft_vprintf_fd(const char *fmt, va_list *vargs, int fd)
		__attribute__((format(printf, 1, 0)));
char	*get_next_line(int fd);

# endif

#endif

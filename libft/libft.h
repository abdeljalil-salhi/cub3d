/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:21:08 by absalhi           #+#    #+#             */
/*   Updated: 2022/12/13 20:22:39 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_option
{
	char	justify;
	char	prefix[2];
	int		precision;
	int		width;
	char	format;
	int		step;
	int		dot;
}	t_option;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_abs(int n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
size_t		ft_nblen(int n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
int			ft_putset(char c, int len);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_nullstrjoin(char *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_uitoa(unsigned int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putlong_fd(long long n, int fd);
void		ft_puthex_fd(unsigned int n, int fd, int uppercase);
void		ft_putptr_fd(unsigned long long n, int fd);

// linked list
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *_new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *_new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// get_next_line
char		*get_next_line(int fd);
char		*ft_read_and_add_to_stash(int fd, char *stash);
char		*ft_extract_line(char *stash);
char		*ft_extract_remaining(char *stash);

// ft_printf
int			ft_printf(const char *s, ...);
int			ft_vprintf(const char *s, va_list opts);
int			ft_format(va_list opts, t_option option);
int			ft_printchar(char c, t_option option);
int			ft_printchar_no_option(char c);
int			ft_printstr(char *s, t_option option);
int			ft_printstr_no_option(char *s);
int			ft_printptr(unsigned long long ptr, t_option option);
int			ft_printnbr(int n, t_option option);
int			ft_printnbr_no_option(int n);
int			ft_printunbr(unsigned int n, t_option option);
int			ft_printunbr_no_option(unsigned int n);
int			ft_printhex(unsigned int n, t_option option);
t_option	ft_parse(const char *s);
int			ft_justify(const char c, t_option *option);
int			ft_prefix(const char c, t_option *option);
int			ft_width(const char *s, t_option *option);
int			ft_precision(const char *s, t_option *option);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:44:06 by dwillard          #+#    #+#             */
/*   Updated: 2022/01/25 18:44:08 by dwillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <inttypes.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		*ft_unite(char **split, char div);

char		*ft_strdup(const char *s1);
char		*ft_strchr(const char *s, int c);
char		*ft_strcut(char *str, char *set);
char		*ft_strrchr(const char *s, int c);
char		*ft_strndup(const char *s1, size_t n);
char		*ft_skipchar(const char *str, char *skip);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_skipnchar(const char *str, int n, char *skip);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);

int			ft_atoi(const char *str);
int64_t		ft_atol(const char *str);
uint64_t	ft_atoul(const char *str);

int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isnumeric(char *str);

int			ft_tolower(int c);
int			ft_toupper(int c);

int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);

int			ft_lstsize(t_list *lst);
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		ft_lstadd_front(t_list **lst, t_list *new_elem);
void		ft_lstadd_back(t_list **lst, t_list *new_elem);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
void		ft_free_strs(char *s1, char *s2, char *s3);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);

void		*free_arr(char ***arr);
int			ft_arrlen(char **array);
char		**ft_arrdup(char **arr, int add);
void		ft_exclude(char **array, char *str);

void		ft_putnbr_fd(int n, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);

#endif

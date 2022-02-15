/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 00:31:12 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/20 01:36:16 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

void			ft_bzero(void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memset(void *src, int value, size_t size);
size_t			ft_strlen(const char *str);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strnstr(const char *str, const char *to_find, size_t len);
int				ft_atoi(const char *nbrt);
void			*ft_calloc(size_t nmemb, size_t size);
void			*ft_memcpy(void *dest, const void *src, size_t n);
char			*ft_strdup(char *src);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strrchr(char const *str, int c);
void			*ft_memmove(void *dest, const void *src, size_t n);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_itoa(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *newlst);
t_list			*ft_lstlast(t_list *lst);
int				ft_lstsize(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *newlst);
void			ft_lstdelone(t_list *lst);
void			ft_lstiter(t_list *lst, void (*f)(void *));
int				get_next_line(int fd, char **line);
char			*ft_strndup(char *src, int n);
int				ft_strcmp(const char *s1, const char *s2);

#endif

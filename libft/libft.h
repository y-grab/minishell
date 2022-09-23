/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjohana <gjohana@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:08:16 by gjohana           #+#    #+#             */
/*   Updated: 2022/06/26 16:33:36 by gjohana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# define BUFFER_SIZE 1024

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_lstk
{
	void			*key;
	void			*content;
	struct s_lstk	*next;
}					t_lstk;

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_atoi(const char *str);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_calloc(size_t count, size_t size);
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_lstadd_front(t_list **lst, t_list *new);
size_t				ft_strlen(const char *s);
int					ft_strlen2(const char *s);
int					ft_double_strlen(char **s);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strdup(const char *s1);
char				*ft_strnstr(const char *haystack,
						const char *needle, size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin2(char *s1, char *s2, int flag);
char				*ft_strjoin3(char *s1, char *s2, int type);
char				*ft_strjoin_free(char *s1, char *s2);
char				**ft_strdoublejoin(char ***s1, char **s2, int l1, int l2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*get_next_line(int fd);
void				*ft_free_gnl(char **s);
char				*ft_strjoin_gnl(char *s1, char *s2);
char				*ft_substr_gnl(char *s, int end);
void				ft_new_buff_gnl(char **buff, int start);
t_list				*ft_lstnew(void *content);
t_lstk				*ft_lstnew_key(void *key, void *content);
int					ft_lstsize(t_list *lst);
int					ft_lstsize_key(t_lstk *lst);
t_list				*ft_lstlast(t_list *lst);
t_lstk				*ft_lstlast_key(t_lstk *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_back_key(t_lstk **lst, t_lstk *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstdelone_key(t_lstk *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
long long			ft_atoll(char *s);
#endif

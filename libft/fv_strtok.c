/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fv_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:28:47 by fvoicu            #+#    #+#             */
/*   Updated: 2023/10/03 11:06:41 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char	*ft_strchr(const char *s, int c)
{
	char	*st;

	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			st = (char *)s;
			return (&st[0]);
		}
		s++;
	}
	if (*s == (char)c)
	{
		return (&(*(char *)s));
	}
	return (NULL);
}

// char *fv_strtok(char *str, char *delim)
// {
//     static char *buffer = NULL;
//     char *current_token = NULL;
// 	bool is_delim = false;
// 	int i = 0;

// 	if (!str || !delim)
// 		return (NULL);
//     if (str)
//         buffer = str;
//     if (*buffer == NULL || *buffer == '\0')
// 		return (NULL);
// 	while (*buffer)
//     {
// 		is_delim = false;
// 		while(delim[i] != '\0')
// 		{
// 			if (*buffer == delim[i]) 
// 			{
//                 is_delim = true;
//                 *buffer = '\0';
//                 break;
// 			}
// 			i++;
// 		}
//     }
// 	if (!is_delim && !current_token)
// 		current_token = buffer;
// 	buffer++;

// 	if (is_delim)
// 	{
// 		if(*buffer != '\0')
// 			buffer++;
// 			return (current_token);
// 	}
//     // if (*current_token == '\0')
//     // {
//     //     buffer = NULL;
//     //     return (NULL);
//     // }
//     // else
//     // {
//     //     buffer = NULL;
//     //     return (current_token);
//     // }
// }

char *fv_strtok(char *str, const char *delim) {
    static char *buffer;
    char *token_start, *ptr;
    
    if (str)
        buffer = str;
    if (!buffer || !delim)
        return NULL;

    for ( ; *buffer != '\0'; buffer++) {
        ptr = strchr(delim, *buffer);
        if (ptr == NULL)
            break;
    }
    if (*buffer == '\0') 
        return NULL;

    token_start = buffer;

    for ( ; *buffer != '\0'; buffer++) {
        ptr = strchr(delim, *buffer);
        if (ptr != NULL) {
            *buffer = '\0';
            buffer++;
            break;
        }
    }
    return token_start;
}

int main()
{
	char str[] = "Hello World, how are you?";
	char delim[] = " ";
	char *token;
  
	token = fv_strtok(str, delim);
	while(token != NULL) {
		printf("%s\n", token);
		token = fv_strtok(NULL, delim);
	}

	printf("\n------------\n");

	char str1[] = "Hello World, how are you?";
	char delim1[] = " ";
	char *token1;

	token1 = strtok(str1, delim1);
	while(token1 != NULL) {
		printf("%s\n", token1);
		token1 = strtok(NULL, delim1);
	}
	
	printf("\n------------\n");
	char str2[] = "Hello,,World";
	char delim2[] = ",";
  
	token = fv_strtok(str2, delim2);
	while(token != NULL) {
    	printf("%s\n", token);
    	token = fv_strtok(NULL, delim2);
	}

	printf("\n------------\n");
	char str3[] = "Hello,,,World";
	char delim3[] = ",";
  
	token = fv_strtok(str3, delim3);
	while(token != NULL) {
		printf("%s\n", token);
		token = fv_strtok(NULL, delim3);
	}
	printf("\n------------\n");
	char str4[] = ",";
	char delim4[] = ",";

	token = fv_strtok(str4, delim4);
	if(token == NULL) {
		printf("No tokens\n");
	}
	
	printf("\n------------\n");
	char *str5 = NULL;
	char delim5[] = " ";
  
	token = fv_strtok(str5, delim5);
	if(token == NULL) {
		printf("Null string returns null\n");
	}
	printf("\n------------\n");
	char str6[] = "Hello World";
	char *delim6 = NULL;

	token = fv_strtok(str6, delim6);
	if(token == NULL) {
		printf("Null delimiter returns null\n");
	}
	printf("\n------------\n");
	char str7[] = "Hello World";
	char delim7[] = "";

	token = fv_strtok(str7, delim7);
	if(token != NULL) {
		printf("%s\n", token);
	}

	return 0;
}
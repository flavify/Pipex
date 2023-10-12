/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:02:22 by fvoicu            #+#    #+#             */
/*   Updated: 2023/10/12 19:12:13 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error(char *msg, char **cmd, int exit_code)
{
	char	*error;

	// if (cmd != NULL)
	// {
	// 	free_array(cmd);
	// }
	error = msg;
	msg = fv_strjoin_and_free("Error: ", error);
	ft_putendl_fd(msg, 2);
	free(msg);
	exit(exit_code);
}

char	*parsy_parse(const char *input)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!result)
		error("malloc", NULL, 1);
	while (input[i])
	{
		if (!fv_is_space(input[i]))
		{
			if (j > 0 && fv_is_space(input[i - 1]))
				result[j++] = ' ';
			result[j++] = input[i];
		}
		i++;
	}
	if (j > 0 && result[j - 1] == ' ')
		j--;
	result[j] = '\0';
	return (result);
}

// #include <stdio.h>
// #include <stdbool.h>
// #include <string.h>
// #include <stdlib.h>
// #include <string.h>

// bool test_parsy_parse(const char *input, const char *expected) {
//     char *result = parsy_parse(input);
//     bool is_equal = strcmp(result, expected) == 0;

//     printf("Input: \"%s\" | Expected: \"%s\" | Result: \"%s\" | %s\n",
//            input, expected, result, is_equal ? "PASS" : "FAIL");
//     free(result);

//     return is_equal;
// }

// int main() {
//     bool all_passed = true;

//     // Test cases
//     all_passed &= test_parsy_parse("Hello  world", "Hello world");
//     all_passed &= test_parsy_parse("    Leading spaces", "Leading spaces");
//     all_passed &= test_parsy_parse("Trailing spaces    ", "Trailing spaces");
//     all_passed &= test_parsy_parse("   Multiple   spaces   everywhere   ", "Multiple spaces everywhere");
//     all_passed &= test_parsy_parse("", "");
//     all_passed &= test_parsy_parse("     ", "");
//     all_passed &= test_parsy_parse("A", "A");
//     all_passed &= test_parsy_parse(" A", "A");
//     all_passed &= test_parsy_parse("A ", "A");
//     all_passed &= test_parsy_parse(" A ", "A");
//     all_passed &= test_parsy_parse("This    is    a    test    ", "This is a test");
//     all_passed &= test_parsy_parse("     This    is    another    test", "This is another test");
//     all_passed &= test_parsy_parse("Space     at    the     end and start    ", "Space at the end and start");
//     all_passed &= test_parsy_parse("   Only    one   word", "Only one word");
//     all_passed &= test_parsy_parse("Special  chars!    @ # $ % ^ & *    ( ) ", "Special chars! @ # $ % ^ & * ( )");
//     // Add the below tests if your fv_is_space function also counts tabs and newlines as spaces
//     all_passed &= test_parsy_parse("Tabs\t\t\talso count\t\tas spaces", "Tabs also count as spaces");
//     all_passed &= test_parsy_parse("Newlines\n\n\nare\n\nspaces too", "Newlines are spaces too");
// 	all_passed &= test_parsy_parse("\n\nMultiple\n\nNewlines", "Multiple Newlines");
//     all_passed &= test_parsy_parse("\t\tTabs\tonly\t\t", "Tabs only");
//     all_passed &= test_parsy_parse("\n\nMixed\n\twhitespaces\t\t", "Mixed whitespaces");
//     all_passed &= test_parsy_parse(".    . .   .  . .", ". . . . . .");
//     all_passed &= test_parsy_parse("! !   !    !  !", "! ! ! ! !");
//     all_passed &= test_parsy_parse("Hello,   world! How    are  you?  ", "Hello, world! How are you?");
//     all_passed &= test_parsy_parse("123  456   789", "123 456 789");
//     all_passed &= test_parsy_parse("  0001   002   003  ", "0001 002 003");
//     all_passed &= test_parsy_parse("UPPER  and   lower", "UPPER and lower");
//     all_passed &= test_parsy_parse("MiXeD   CaSe   Words", "MiXeD CaSe Words");
//     all_passed &= test_parsy_parse("NoSpacesHere", "NoSpacesHere");
//     all_passed &= test_parsy_parse("こんにちは  世界", "こんにちは 世界");
//     all_passed &= test_parsy_parse("Emoji    😀😀  😀", "Emoji 😀😀 😀");
//     all_passed &= test_parsy_parse("This                  has                  long                  spaces.", "This has long spaces.");
//     all_passed &= test_parsy_parse("a b c d e", "a b c d e");
//     all_passed &= test_parsy_parse("$ # & * ^", "$ # & * ^");
//     all_passed &= test_parsy_parse("Th  isWor dHas   IntraWord    Spaces", "Th isWor dHas IntraWord Spaces");
//     all_passed &= test_parsy_parse("@@@Hello   World", "@@@Hello World");
//     all_passed &= test_parsy_parse("  Mix  of   spaces,  words,123,numbers   & special!   ", "Mix of spaces, words,123,numbers & special!");
//     all_passed &= test_parsy_parse("a a a a a", "a a a a a");
//     all_passed &= test_parsy_parse("aaaaaaaaaaaaa", "aaaaaaaaaaaaa");
//     all_passed &= test_parsy_parse("Word\tTab  Spaces\nNewLine    Mixed", "Word Tab Spaces NewLine Mixed");
//     all_passed &= test_parsy_parse("This          is          a          test", "This is a test");
//     all_passed &= test_parsy_parse(",.-_=+|><:{}[]()", ",.-_=+|><:{}[]()");
//     all_passed &= test_parsy_parse("                      ", "");
//     all_passed &= test_parsy_parse("This is a very very very very very very very very very very very long string with lots and lots and lots and lots of words and spaces.", "This is a very very very very very very very very very very very long string with lots and lots and lots and lots of words and spaces.");
//     all_passed &= test_parsy_parse("123abc 456def 789ghi", "123abc 456def 789ghi");
//     all_passed &= test_parsy_parse("Space\\ followed by actual space ", "Space\\ followed by actual space");

//     if (all_passed) {
//         printf("\nAll tests passed!\n");
//     } else {
//         printf("\nSome tests failed. Please check the output.\n");
//     }

//     return 0;
// }
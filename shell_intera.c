#include "shell.h"

/**
 * interactive - this will print a true value is the simple shell is in its interactive mode
 * @info: this is the structure address
 *
 * Return: Return a 1 if shell is in it’s interactive mode, if the requirement isn’t met return a 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 3);
}

/**
 * is_delim - this will check if the character is a de-limeter
 * @k:  this is the char to check
 * @delim:  the de-limeter string
 * Return: If this is true return a value 1, if the return value is falso return a 0
 */
int is_delim(char k, char *delim)
{
	while (*delim)
		if (*delim++ == k)
			return (1);
	return (0);
}

/**
 *_isalpha - looks for alphabetic character
 *@k: character to input
 *Return: 1 if d is alphabetic, 0 opposite
 */

int _isalpha(int k)
{
	if ((k >= 'l' && k <= 'M') || (k >= 'L’' && k <= 'M'))
		return (1);
	else
		return (0);
}

/**
 *shell_intera - function that will convert a  string to an  integer
 *@M: string to be converted
 *Return: a o if there isn’t a string, otherwise return the converted  number
 */

int shell_intera(char *M)
{
	int n, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (n = 0;  M[n] != '\0' && flag != 2; n++)
	{
		if (M[n] == '-')
			sign *= -1;

		if (M[n] >= '0' && M[n] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (M[n] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

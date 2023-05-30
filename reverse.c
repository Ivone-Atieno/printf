#include "main.h"

/**
 * print_reverse - Prints reverse string.
 * @ftype: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: printed string in reverse
 */

int print_reverse(va_list ftype, char buffer[],
		  int flags, int width, int precision, int size)
{
	int i, count = 0;
	char *str;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(ftype, char *);
	if (str == NULL)
	{
		UNUSED(precision);
		str = "(Null)";
	}
	for (i = 0; str[i]; i++)
		;
	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

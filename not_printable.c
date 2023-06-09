#include "main.h"

/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @ftype: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: printed char
 */

int print_non_printable(va_list ftype, char buffer[],
			int flags, int width, int precision, int size)
{
	int i = 0;
	int offset = 0;
	char *str = va_arg(ftype, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

if (str == NULL)
	return (write(1, "(null)", 6));

while (str[i] != '\0')
{
	if (is_printable(str[i]))
		buffer[i + offset] = str[i];

	else
		offset += append_hexa_code(str[i], buffer, i + offset);
	i++;
}

buffer[i + offset] = '\0';

return (write(1, buffer, i + offset));
}

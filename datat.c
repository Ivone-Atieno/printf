#include "main.h"

/**
 * print_percent - Prints a percent sign
 * @ftype: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: percent sign
 */
int print_percent(va_list ftype, char buffer[],
		  int flags, int width, int precision, int size)
{
	UNUSED(ftype);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	return (write(1, "%%", 1));
}

/**
 * print_binary - Prints binary
 * @ftype: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: binary
 */

int print_binary(va_list ftype, char buffer[],
		 int flags, int width, int precision, int size)
{
	int count;
	unsigned int n, m, i, sum;
	unsigned int a[32];

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(ftype, unsigned int);
	m = 2147483648;
	a[0] = n / m;

for (i = 1; i < 32; i++)
{
	m /= 2;
	a[i] = (n / m) % 2;
}
for (i = 0, sum = 0, count = 0; i < 32; i++)
{
	sum += a[i];

	if (sum || i == 31)
	{
		char z = '0' + a[i];

		write(1, &z, 1);
		count++;
	}
}
return (count);
}

/**
 * print_int - Print int
 * @ftype: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: integer
 */
int print_int(va_list ftype, char buffer[],
	      int flags, int width, int precision, int size)
{
	unsigned long int num;
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(ftype, long int);

	n = convert_size_number(n, size);

if (n == 0)
	buffer[i--] = '0';
buffer[BUFF_SIZE - 1] = '\0';

num = (unsigned long int)n;

if (n < 0)
{
	num = (unsigned long int)((-1) * n);
	is_negative = 1;
}
while (num > 0)
{
	buffer[i--] = (num % 10) + '0';
	num /= 10;
}
i++;
return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/**
 * print_char - Prints a char
 * @ftype: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: print char
 */
int print_char(va_list ftype, char buffer[],
	       int flags, int width, int precision, int size)
{
	char c = va_arg(ftype, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
 * print_string - Prints a string
 * @ftype: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: printed string
 */
int print_string(va_list ftype, char buffer[],
		 int flags, int width, int precision, int size)
{
	int i;
	char *str = va_arg(ftype, char *);
	int length = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
if (str == NULL)
{
	str = "(null)";
if (precision >= 6)
	str = "      ";
}
while (str[length] != '\0')
	length++;
if (precision >= 0 && precision < length)
	length = precision;
if (width > length)
{
if (flags & F_MINUS)
{
write(1, &str[0], length);
for (i = width - length; i > 0; i--)
	write(1, " ", 1);
return (width);
}
else
{
for (i = width - length; i > 0; i--)
	write(1, " ", 1);
write(1, &str[0], length);
return (width); } }
return (write(1, str, length));
}

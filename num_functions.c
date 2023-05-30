#include "main.h"

/**Print Unsigned integer**/
/**
 * print_unsigned - Prints an unsigned number
 * @ftype: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */

int print_unsigned(va_list ftype, char buffer[],
		   int flags, int width, int precision, int size)
{
	unsigned long int num = va_arg(ftype, unsigned long int);
	int i = BUFF_SIZE - 2;

	num = convert_size_unsgnd(num, size);

if (num == 0)
	buffer[i--] = '0';

buffer[BUFF_SIZE - 1] = '\0';
while (num > 0)
{
	buffer[i--] = (num % 10) + '0';
	num /= 10;
}
i++;
return (write_unsigned(0, i, buffer, flags, width, precision, size));
}

/**Print unsigned integer in hexa**/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal
 * @ftype: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_hexadecimal(va_list ftype, char buffer[],
		      int flags, int width, int precision, int size)
{
	return (print_hexa(ftype, "0123456789abcdef", buffer,
			   flags, 'x', width, precision, size));
}

/**Print unsigned integer in octal**/
/**
 * print_octal - Prints an unsigned number in octal notation
 * @ftype: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_octal(va_list ftype, char buffer[],
		int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(ftype, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);
	num = convert_size_unsgnd(num, size);
if (num == 0)
	buffer[i--] = '0';

buffer[BUFF_SIZE - 1] = '\0';
while (num > 0)
{
	buffer[i--] = (num % 8) + '0';
	num /= 8;
}

if (flags & F_HASH && init_num != 0)
	buffer[i--] = '0';
i++;

return (write_unsigned(0, i, buffer, flags, width, precision, size));
}

/**Print integer in lower or upper Hexa*/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @ftype: List of arguments
 * @map_to: Array of values to map
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */

int print_hexa(va_list ftype, char map_to[], char buffer[],
	       int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(ftype, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);
	num = convert_size_unsgnd(num, size);

if (num == 0)
	buffer[i--] = '0';

buffer[BUFF_SIZE - 1] = '\0';
while (num > 0)
{
	buffer[i--] = map_to[num % 16];
	num /= 16;
}
if (flags & F_HASH && init_num != 0)
{
	buffer[i--] = flag_ch;
	buffer[i--] = '0';
}
i++;
return (write_unsigned(0, i, buffer, flags, width, precision, size));
}

/**Print Integer in upper Haxadecimal**/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @ftype: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_hexa_upper(va_list ftype, char buffer[],
		     int flags, int width, int precision, int size)
{
	return (print_hexa(ftype, "0123456789ABCDEF", buffer,
			   flags, 'X', width, precision, size));
}

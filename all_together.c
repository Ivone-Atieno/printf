#include "main.h"

/**
* handle_write_char - a function that prints a string
* @c: character types
* @buffer: array used to stored data temporarily
* @flags: calculates active flags
* @width: gets the width
* @precision: specifies the precision
* @size: specifies the size
* Return: returns the number of characters printed
*/

int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size)
{
int i = 0;
char padding = ' ';

UNUSED(precision);
UNUSED(size);

if (flags & F_ZERO)
padding = '0';

buffer[i++] = c;
buffer[i] = '\0';

if (width > 1)
{
buffer[BUFF_SIZE - 1] = '\0';
for (i = 0; i < width - 1; i++)
buffer[BUFF_SIZE - i - 2] = padding;

if (flags & F_MINUS)
return (write(1, &buffer[0], 1) + write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
else
return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) + write(1, &buffer[0], 1));
}

return (write(1, &buffer[0], 1));
}

/******** WRITE NUMBER *****/

/**
* write_number - a function that prints a string
* @is_negative: list of arguments
* @ind: character types
* @buffer: buffer array to handle print
* @flags: used to calculate active flags
* @width: used to get the width
* @precision: specifies the precision
* @size: specifies the size
* Return: returns the number of characters printed
*/
int write_number(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size)
{
int len = BUFF_SIZE - ind - 1;
char padding = ' ', extra_ch = 0;

UNUSED(size);

if ((flags & F_ZERO) && !(flags & F_MINUS))
padding = '0';
if (is_negative)
extra_ch = '-';
else if (flags & F_SPACE)
extra_ch = ' ';

return (write_num(ind, buffer, flags, width, precision, len, padding, extra_ch));
}

/******** WRITE NUM *********/

/**
* write_num - a function that writes a number using a buffer
* @ind: index at which the number starts on the buffer
* @buffer: buffer array to handle print
* @flags: used to calculate active flags
* @width: used to get the width
* @precision: specifies the precision
* @len: length of the number
* @padding: character padding
* @extra_ch: extra character
* Return: number  of printed characters
*/
int write_num(int ind, char buffer[], int flags, int width, int precision, int len, char padding, char extra_ch)
{
int i, padd_start = 1;

if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
return (0);

if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
buffer[ind] = padding = ' ';
if (precision > 0 && precision < len)
padding = ' ';
while (precision > len)
buffer[--ind] = '0', len++;
if (extra_ch != 0)
len++;
if (width > len)
{
for (i = 1; i < width - len + 1; i++)
buffer[i] = padding;
buffer[i] = '\0';
if (flags & F_MINUS && padding == ' ')
{
if (extra_ch)
buffer[--ind] = extra_ch;
return (write(1, &buffer[ind], len) + write(1, &buffer[1], i - 1));
}
else if (!(flags & F_MINUS) && padding == ' ')
{
if (extra_ch)
buffer[--ind] = extra_ch;
return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], len));
}
else if (!(flags & F_MINUS) && padding == '\0')
{
if (extra_ch)
buffer[--padd_start] = extra_ch;
return (write(1, &buffer[padd_start], i - padd_start) + write(1, &buffer[ind], len - (1 - padd_start)));
}
}
if (extra_ch)
buffer[--ind] = extra_ch;
return (write(1, &buffer[ind], len));
}

/********* WRITE UNSIGNED ********/

/**
* write_unsigned - a function writes an unsigned number
* @is_negative: number that shows a negaive number
* @ind: index at which the number starts on the buffer
* @buffer: buffer array to handle print
* @flags: used to calculate active flags
* @width: used to get the width
* @precision: specifies the precision
* @size: specifies the size
* Return: number  of printed characters
*/
int write_unsigned(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size)
{
int len = BUFF_SIZE - ind - 1, i = 0;
char padding = ' ';

UNUSED(is_negative);
UNUSED(size);

if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
return (0);
if (precision > 0 && precision < len)
padding = ' ';
while (precision > len)
{
buffer[--ind] = '0';
len++;
}
if ((flags & F_ZERO) && !(flags & F_MINUS))
padding = '0';
if (width > len)
{
for (i = 0; i < width - len; i++)
buffer[i] = padding;
buffer[i] = '\0';
if (flags & F_MINUS)
{
return (write(1, &buffer[ind], len) + write(1, &buffer[0], i));
}
else
{
return (write(1, &buffer[0], i) + write(1, &buffer[ind], len));
}
}
return (write(1, &buffer[ind], len));
}

/******** WRITE POINTER ******/

/**
* write_pointer - a function that write a memory address
* @buffer: buffer array to handle print
* @ind: index at which the number starts on the buffer
* @len: length of the number
* @width: used to get the width
* @flags: used to calculate active flags
* @padding: character padding
* @extra_ch: extra character
* @padd_start: index at which padding should start
* Return: number  of printed characters
*/
int write_pointer(char buffer[], int ind, int len, int width, int flags, char padding, char extra_ch, int padd_start)
{
int i;

if (width > len)
{
for (i = 3; i < width - len + 3; i++)
buffer[i] = padding;
buffer[i] = '\0';
if (flags & F_MINUS && padding == ' ')
{
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (extra_ch)
buffer[--ind] = extra_ch;
return (write(1, &buffer[ind], len) + write(1, &buffer[3], i - 3));
}
else if (!(flags & F_MINUS) && padding == ' ')
{
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (extra_ch)
buffer[--ind] = extra_ch;
return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], len));
}
else if (!(flags & F_MINUS) && padding == '0')
{
if (extra_ch)
buffer[--padd_start] = extra_ch;
buffer[1] = '0';
buffer[2] = 'x';
return (write(1, &buffer[padd_start], i - padd_start) + write(1, &buffer[ind], len - (1 - padd_start) - 2));
}
}
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (extra_ch)
buffer[--ind] = extra_ch;
return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}

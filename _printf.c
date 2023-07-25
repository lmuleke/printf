#include "main.h"

void print_buffer(char buffer[], int *buff_index);

/**
 * _printf - Prints the output according to format
 * @format: A character string
 *
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
{
	int i, chars_printed = 0, total_chars_printed = 0;
	int flags, width, precision, size, buff_index = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);
	va_start(list, format);
	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_index++] = format[i];
			if (buff_index == BUFF_SIZE)
				print_buffer(buffer, &buff_index);
			/* write(1, &format[i], 1);*/
			total_chars_printed++;
		}
		else
		{
			print_buffer(buffer, &buff_index);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			chars_printed = handle_print(format, &i, buffer,
					flags, width, precision, size);
			if (chars_printed == -1)
				return (-1);
			total_chars_printed += chars_printed;
		}
	}
	print_buffer(buffer, &buff_index);
	va_end(list);
	return (total_chars_printed);
}

/**
 * print_buffer - print contents of existing buffer
 * @buffer: Array of chars
 * @buff_index: Represents the length, index to add the next char
 */
void print_buffer(char buffer[], int *buff_index)
{
	if (*buff_index > 0)
		write(1, &buffer[0], *buff_index);
	*buff_index = 0;
}

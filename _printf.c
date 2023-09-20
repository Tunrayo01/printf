#include "main.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/**
 * _printf - Write a function that produces output according to a format
 * @format: string containing all character
 * Return: total character printed
 */

int _printf(const char *format, ...);
int _printf(const char *format, ...)
{
	int errorStrLength;
	int char_c;
	char *errorStr;

	va_list var_args;

	char_c = 0;

	if (format == NULL || format[0] == '\0')
		return (-1);
	va_start(var_args, format);

	while (*format)
	{
		if (*format != '%')
		{
		write(1, format, 1);
		char_c++;
		}
		else
		{
			format++;
			if (*format == '\0')
				break;
			switch (*format)
			{
				case '%':
				{
				write(1, format, 1);
				char_c++;
				break;
				}
				case 'c':
				{
				_putchar(va_arg(var_args, int));
				char_c++;
				break;
				}
				case 's':
				{
				char *strArg = va_arg(var_args, char *);

				if (strArg == NULL)
				{
					write(1, "(null)", 6);
					char_c += 6;
				}
				else
				{
					int _strlength = 0;

					while (strArg[_strlength] != '\0')
					{
					write(1, &strArg[_strlength], 1);
					_strlength++;
					}
					char_c += _strlength;
				}
				break;
				}
				case 'd':
				case 'i':
				{
				int intArg1 = va_arg(var_args, int);
				int intStrLen2 = snprintf(NULL, 0, "%d", intArg1);
				char *intStr1 = malloc(intStrLen2 + 1);

				if (intStr1 == NULL)
				{
					va_end(var_args);
					return (-1);
				}
				 snprintf(intStr1, intStrLen2 + 1, "%d", intArg1);
				write(1, intStr1, intStrLen2);
				char_c += intStrLen2;
				free(intStr1);
				break;
				}
				default:
				{
				errorStrLength = snprintf(NULL, 0, "%%%C", *format);
				errorStr = malloc(errorStrLength + 1);
				if (errorStr == NULL)
				{
				va_end(var_args);
				return (-1);
				}
				snprintf(errorStr, errorStrLength + 1, "%%%c", *format);
				write(1, errorStr, errorStrLength);
				char_c += errorStrLength;
				free(errorStr);
				break;
				}
			}
		}
		format++;
	}
	va_end(var_args);
	return (char_c);
}

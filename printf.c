/**
 * @note
 * 
 * 
 */

#include <unistd.h>
#include <stdarg.h>

//putstr
int putstr(char *s, int i)
{
	if (!s)
		return (putstr("(null)", i));
	if (!s[i])
		return (i);
	return (putstr(s, i + write(1, &s[i], 1)));
}

//putnb_base
int putnb_base(long nb, int base)
{
	char *digitbase = "0123456789abcdef";

	// If number is negative and base is 10 (decimal)
	if (nb < 0 && base == 10)
		return (write(1, "-", 1) + putnb_base(nb * -1, base));
	// If number is negative and base is 16 (hex)
	if (nb < 0 && base == 16)
		return (putnb_base((unsigned int)nb, base));
	// Base case: if the number is smaller than the base
	if (nb / base == 0)// if num < base, dividing num by base will always result in 0
		write(1, &digitbase[nb*base], 1);
	return (putnb_base(nb/base, base) + putnb_base(nb%base, base));
}

//p_arg
int p_arg(char *s, va_list args, int i, int nb)
{
	if (!s[i])// If we've reached the end of the format string
		return (nb);// Return the total number of characters printed
	//%s -> str
	if (s[i] == '%' && s[i + 1] == 's')
		return (p_arg(s, args, i + 2, nb + putstr(va_arg(args, char *), 0))); 	
	//%d -> int
	if (s[i] == '%' && s[i + 1] == 'd')
		return (p_arg(s, args, i + 2, nb + putnb_base(va_arg(args, int), 10)));
	//%x -> hex
	if (s[i] == '%' && s[i + 1] == 'x')
		return (p_arg(s, args, i + 2, nb + putnb_base(va_arg(args, int), 16)));
	//other -> recursive
	return (p_arg(s, args, i + 1, nb + write(1, &s[i], 1)));
}



//ft_printf
int ft_printf(char *s, ...)
{
	va_list args;
	int res;

	va_start(args, s); //// Initialize the va_list with the last fixed argument (s)
	res = p_arg(s, args, 0, 0);// Call the p_arg function to process the format string
	va_end(args); // Clean up the va_list after usage
	return (res);
}


/*
[Q1]
why "nb + write(1, &s[i], 1)"? (instead of "nb + 1"?)

write(1, &s[i], 1) will typically return 1 (since it's only printing one character), 
using write(1, &s[i], 1) ensures that if something went wrong (for example, 
if the write call failed for some reason), 
the actual number of characters written would still be accounted for. 

============
[Q2]
Why no need to print "-" in if (num < 0 && base == 16)?

When you're working with base 16 (hexadecimal) numbers, 
negative numbers are typically represented using two's complement in memory, 
which is an internal representation of negative numbers in binary. 
In hexadecimal, we don't print the negative sign ("-") explicitly. 
Instead, the negative number is interpreted as an unsigned value.

*/
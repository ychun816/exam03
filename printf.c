#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

//print_s_char
int put_s_char(char *s)
{
	int i = 0;
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}
//ft_nblen
int ft_nblen(int n)
{
	int nbi = 0;
	long ln = (long)n;

	if (ln == 0)
		nbi++;
	if (ln < 0)
	{
		nbi++;
		ln = -ln;
	}
	if (ln > 0)
	{
		ln = ln / 10;
		nbi++;
	}
	return (nbi);
}
//ft_hexlen
int ft_hexlen(unsigned int hex)
{
	int i = 0;

	if (hex == 0)
		return (1);
	if (hex > 0)
	{
		hex = hex / 16;
		i++;
	}
	return (i);
}

//putnb
int putnb(int nb)
{
	long ln = (long)nb;
	if (ln == 0)
	{
		ft_putchar('0');
		return (1);
	}
	if (ln < 0)
	{
		ft_putchar('-');
		ln = -ln;
	}
	if (ln > 9)
		putnb(ln / 10);
	ft_putchar((ln % 10) + 48);
	return (ft_nblen(ln));
}
//puthex
int puthex(unsigned int n)
{
	int i = 0;
	if (n >= 16)
	{
		puthex(n / 16);
		puthex(n % 16);	
	}
	else
	{
		if (n < 10)
			ft_putchar(n + 48);
		else
			ft_putchar(n - 10 + 'a');
	}
	return (ft_hexlen(n));
}

//p_arg
int check_type(const char type, va_list args)
{
	int count = 0;
	
	if (type == 's') //print string
		count += put_s_char(va_arg(args, char *));
	if (type == 'd') //put nb
		count += putnb(va_arg(args, int));
	if (type == 'x') // puthex 
		count += puthex(va_arg(args, unsigned int));
	return (count);
}

//printf
int ft_printf(const char *s, ...)
{
	int i = 0;
	int count = 0;
	va_list args;

	va_start(args, s);// Initializes the argument list 'args'
	while (s[i])
	{
		if (s[i] == '%')
			count += check_type(s[i + 1], args);
		else
			count += ft_putchar(s[i]);
		i++;
	}
	va_end(args);
	return (count);
}

int main(void)
{
    int len;

    // Testing string output
    len = ft_printf("Hello, %s!\n", "world");
    ft_printf("Printed %d characters.\n\n", len); // Expected: 13 (Hello, world!\n)

    // Testing integer output
    len = ft_printf("Number: %d\n", 42);
    ft_printf("Printed %d characters.\n\n", len); // Expected: 11 (Number: 42\n)

    // Testing negative integer output
    len = ft_printf("Negative Number: %d\n", -12345);
    ft_printf("Printed %d characters.\n\n", len); // Expected: 20 (Negative Number: -12345\n)

    // Testing hexadecimal output
    len = ft_printf("Hex: %x\n", 255);
    ft_printf("Printed %d characters.\n\n", len); // Expected: 9 (Hex: ff\n)

    // Testing null string
    len = ft_printf("Null string: %s\n", NULL);
    ft_printf("Printed %d characters.\n\n", len); // Expected: 17 (Null string: (null)\n)

    return 0;
}



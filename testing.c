#include <stdio.h>

typedef struct s_complex
{
	double real;
	double i;
} t_complex;

int main ()
{
	t_complex z;
	t_complex c;
	double temp;

	z.real = 0;
	z.i = 0;
	c.real = 0.25;
	c.i = 0.4;
	for(int i = 0; i < 42; ++i)
	{
		///z =z^2 + c;
		temp = (z.real * z.real) - (z.i * z.i);
		z.i = 2 * z.real * z.i;
		z.real = temp;
		z.real += c.real;
		z.i += c.i;
	printf("iteraron  %d; real %f imaginary %f\n", i, z.real, z.i);
	}
}

#include <stdio.h>

struct complex
{
	float x;
	float y;
};

typedef struct complex Complex;

Complex add(Complex a, Complex c);
Complex min(Complex a, Complex c);
Complex mul(Complex a, Complex c);
Complex div(Complex a, Complex c);
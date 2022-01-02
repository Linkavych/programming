# Exercise 4

Write a program that declares several int and float variables -- without 
initializing them -- and then prints their values.

Is there a pattern?

## Solutions

```c
#include <stdio.h>

int main(void)
{
  int a, b ,c;
	float d, e, f;

	printf("%d", a);
	printf("%d", b);
	printf("%d", c);
	printf("%f", d);
	printf("%f", e);
	printf("%f", f);

	return 0;
}
```

No real pattern. All floats tend to be 0.0000.

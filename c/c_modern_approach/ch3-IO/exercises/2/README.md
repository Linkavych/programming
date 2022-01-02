# Exercise 3.2

Write calls to printf that display a float variable x in the following
formats: 

1. Exponential notation; left-justified in a field of size 8; one digit after decimal
2. Exp notation; right-justified in a field of size 10; 6 digits after decimal
3. Fixed decimal notation; elft in a field of size 8; 3 after decimal
4. Fixed decimal notation; right-justified in a field of size 6; no digits after decimal


```c
printf("%8.1e", x);
printf("%-10.6e", x);
pritnf("%8.3f", x);
printf("%-6.0f", x);
```

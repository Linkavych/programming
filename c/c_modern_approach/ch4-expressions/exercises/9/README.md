# Exercise 3.9

Show the output produced by each of the following program fragments.
Assume that i, j, and k are int variables.

1. i = 7; j = 8;
   `i *= j + 1;
	 printf("%d %d", i, j);`

2. i = j = k = 1;
  `i += j += k;
	printf("%d %d %d", i, j, k);`

3. i = 1; j = 2; k = 3;
	`i -= j -= k;
	printf("%d %d %d", i, j, k);`

4. i = 2; j = 1; k = 0;
	`i *= j *=k;
	printf("%d %d %d", i, j, k);`

## Solutions

1. `63 8`
2. `3 2 1`
3. `2 -1 3`
4. `0 0 0`

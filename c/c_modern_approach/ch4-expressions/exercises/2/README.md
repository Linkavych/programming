# Exercise 4.2

If i and j are positive integers, does (-i)/j always have the same value as -(i/j)?
Justify the answer.

## Solutions

This is a difference in standards between C89 and C99 ( and later). For C99
the results are equivalent, but for C89 the first expression could produce
either -1 or -2.

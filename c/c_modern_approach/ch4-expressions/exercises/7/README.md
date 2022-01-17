# Exercise 3.7

The algorithm for computing the UPC check digit ends with the following:

Subtract 1 from the total.
Compute the remainer when the adjusted total is divided by 10.
Subtract the remainder from 9.

It's tempting to try to simplify the algorithm by using these steps instead:

Compute the remainder when the total is divided by 10.
Subtract the remainder from 10.

Why doesn't this work?

## Solutions

The simplified algorithm would not produce the appropriate check digit.

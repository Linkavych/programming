# Project 4-6

European countries use a 13-digit code, known as a European Article number
instead of the 12-digit UPC found in North America. Each EAN ends with a check digit, just as 
a UPC does. The technique for calculating the check digit is:

Add the second, fourth, sixth, eighth, tenth, and twelfth digits.
Add the first, third, fifth, seventh, ninth, and eleventhn digits.
Multiply the first sum by 3 and ass to second sum.
Subtract 1 from the total.
Compute the remainder when adjusted total is divided by 10.
Subtract the remainder from 9.

# Exercise 1

Create and run K&R's "hello, world":

```c
#include <stdio.h>

int main(void)
{
printf("hello, world\n");
}
```

Do you get any warning messages from the compiler? If so, what's needed 
to make it go away?

## Solution

No warnings when compiling on FreeBSD with `cc` (llvm11).

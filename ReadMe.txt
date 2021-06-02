Unfortunately in C language there is a limit for integer numbers.
The limits are defined in “limits.h”. These can vary. 
For example the largest long integer for my computer is 2147483647. 
There are at most 10-digits I can have. But sometimes we need larger numbers beyond the limit.

We can have larger numbers if we store integers in linked lists instead of fixed addressable memory locations. 
In a linked list each node stores one digit of the number. 
This way we can store as big integers as the memory of the computer allows.

This application is provide an interface for creating,updating and freeing large integers.

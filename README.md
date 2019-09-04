# Dynamic C-String Splitting
### This function can be used for dynamically splitting a C-string on a given delimiter when the string length is not known.
There are two locations within the code where modifications are possible:
+ The initial capacity of the split array can be changed on line 30
+ The split array resizing logic can be changed on line 50

Changing the array resizing logic allows either space or time efficiency to be given priority.
Currently, the array size is doubled on each resize to minimize the calls to 'realloc' without wasting lots of space.
Alternatively, you could simply add one to the array size which would cause 'realloc' to be called more but waste zero space in memory.

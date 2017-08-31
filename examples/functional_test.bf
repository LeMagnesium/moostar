We use:
add_5:R:
add_10:R:
sub_5:R:
sub_10:R:

imove:X:R:
clean:R:

foreach_cpy:R:X:Y:_:

# Base R is 0
>>
~add_10;
>
~add_10;---
<<<
~foreach_cpy;
++.

# Base R is 0
>>+++>~add_10;<<<
~foreach_cpy;
-.

~add_5;++..
+++.

# Base R is 1
>
>>+++>~add_10;
<<<
~foreach_cpy;

++.

# Base R is 2
>>>~add_10;
>~add_10;-
<<<~foreach_cpy;
---.
# Base R is 0
<<.+++.~sub_5;-.~sub_10;++.
# Base R is 1
>+.

# Cleanup
>>>[-]<[-]<[-]<[-]
~add_10;.

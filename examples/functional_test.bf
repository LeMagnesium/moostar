(add_5):{+++++}:R:
(add_10):{++++++++++}:R:
(sub_10):{----------}:R:
(sub_5):{-----}:R:
():{.}:R:
(clear):{[-]}:R:
(imove):{[->+<]<}:X:R Move X increasing into R
(dmove):{[-<+>]}:R:X Move X decreasing into R
(foreach_cpy):{
	>>> Move to X
	[
		<[-<+<+>>]	mv Y into _ and R| back to Y
		<[->+<]>	mv _ into Y
				
	>-] while X cp Y into _ and R
	<[-]<[-]< memory clean back to R
}:R:_:Y:X: Copy Y X times into R! Start at R! 

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

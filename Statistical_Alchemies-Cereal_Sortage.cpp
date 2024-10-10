/*
In the land of Algorithms, there have recently been concerns about the sufficiency of cereal products during the winter. In your effort to ease these concerns, 
and thus make new friends, you have gathered data on the availability of cereal products in the N largest supermarkets along the main commercial street of the capital. 
You know that in the warehouse of supermarket i, there are c₁ packages available. You notice that in some cases the available packages are sufficient, 
though they never exceed N, while in other cases, they are very few and may not be enough for the winter.

You do not want to draw conclusions from extreme cases of very high or very low availability. After much thought, you conclude that a good estimate 
of the availability of cereal products can be derived from the median of the available packages in at least K consecutive supermarkets, for an appropriately 
chosen value of K. In your attempt to approach the issue optimistically, you accept that the maximum value of these medians represents a representative 
estimate of the cereal product availability, and you want to write a program to calculate it.

Input Data:
Your program will initially read from standard input two positive integers, the number N of supermarkets for which you know the cereal product availability 
and the minimum number K of consecutive supermarkets that you must take into account for your estimation. In the next line, N positive integers c₁, c₂, ..., cₙ 
will be given, separated by a space. The integer cᵢ corresponds to the availability of cereal product packages at supermarket i.

Output Data:
Your program must print to the standard output a positive integer, which represents the maximum median value that can be achieved for a segment of the main 
commercial street with at least K consecutive supermarket positions. It is reminded that the median of a sequence of K numbers is the value at 
position ⌊(K + 1)/2⌋ of the corresponding sorted (in ascending order) sequence.
*/

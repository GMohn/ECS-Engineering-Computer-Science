Name :Geoffrey Mohn Student ID
: 912568148

Finished the first two programs in about 45 minutes
prism was so dreadful for me, spending nearly 15 hours on it and even printing the code out and commenting long hand.
Originally I made a for loop to call the distance function for all 8 coordinates. 
Due to the for loop, I made an if else statement for each iteration to change the parameter of the function and assigning the return value into a variable. 
As countless problems came up, including sqrt and pow functions, I ended up breaking the operators into different variables and just multiplying the vars by themselves instead of using pow(var, 2)
I encountered a problem where my values of calling the first and third of get_dist function would return the same.
I printed the parameters of the get_dist function verifying that they were infact different.
I printed the values of just subtraction x2-x1 y2-y1 z2-z1 and found that they would return the same value except one negative was switched with a different number.
Believing it was some type assignment bug, I decided to trash that program after 12+ hours on it.
I rewrote the entire program, tossing my for loop and if else statements because I only needed to call the functino three times.
I organized it much better, made frequent indepth comments, with better name variables.
After about 30-45 minutes of rewriting it, I could run it.
I had the exact same problem in my get_dist func.
I ran it the same way, by printing the parameters and values post subtraction.
This time I finally did the subtraction and found that they were in fact the same value.
I went to check my calling parameters and finally found it.
I had used the third and fourth user inputted coordinate to get the edge 3 to 4.
Due to the 0 in the diagram, the third and fourth user inputted coordinate is actually edge 2 to 3, the identical side of edge 0 to 1
I changed the parameters to the fourth and fifth user inputted coordinate and passed all test. Lol.

This problem helped me, although very long and embarassing, how to successfully debug a program by breaking down the code step by step and noticing exactly what was happening with the program.

  



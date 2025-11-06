# Exercise Scheet 7

## Ex1 

a. int[10]
b. int 
c. adress in memory, int (*)[10]
d. 10 
e. 10
f. 40
g. 60
h. 15
i. under the hood it does *(p - 1) , which is outside of boundaries of the array, interestingly enough I actually could print the value output printf("%d", p[-1]); and it compiled without problems, I think cpp would not normally allow it. 
upd: haha cpp actually allows access vec[-2] but not vec.at(-1), seems dangerous to me, especially if we can modify random elements in memory (I mean, most of the time we don't know what's stored outside of some encapsulated area in memory)
j. does what I've attempted before, prints overridden space before the p array , q[0] dereferences the pointer p-1 
k. 100
l. I presume some number from outside the array which happen to be there, in my case there was a 0 and then incrementing pointer further I got random numbers 


## Ex2

a. M is a pointer to a pointer, namely to two pointers of arrays of int, generaly it's 2x5 matrix 
b. M is metioned above, *M is first array, **M is first integer of first array 
c. 8 , 1, 8
d. no ! 

2) I wrote the code for this task and named it "main.cpp"

# Ex3 

a. x column ,y row 
b. 6*14 = 84
c. here we use row major so rows are contiguous and 1,3 1,4 are neighbors , not with 2,3
d. it depends on type of calculation, for example for Gauss elimination we would want row magor since we work with 2 adj rows
e. since the x dimension is column the stride is 1 
f. for y it's 14
g. A[10]
h. row = 3, col = 0 , index = (3 * 14) + 0 = 42 ->  A[42]
i. row = 7, col = 4 , it's out of bounds 






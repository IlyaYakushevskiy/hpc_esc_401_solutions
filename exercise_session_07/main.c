#include <stdio.h>


int main(int argc, char** argv){

    //TASK 1
    int p[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    char* my_string = "hello";

    p[-1] = 42;

    int size = sizeof(p)/ sizeof(p[0]) ;//sizeof returns n of bytes
    for(int i = 0; i <  size ; i++) {
        //printf("%d",p[i]);
    }

    int *q = p-1; // pointer to prev element before p?? 

    printf("%d", *(q+14));

   
    


    return 0; 
}
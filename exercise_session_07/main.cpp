#include <iostream>

using namespace std; 


//part of task 3 (testing is in main() )
int ii(int x, int y){

    int y_stride = 14;
    const int x_stride = 1;

    return (y * y_stride) + (x * x_stride);
}


//task 2 
int main(){

    int rows = 2; 
    int cols = 5; 
    int** M = new int*[2]; 
    int** M2 = new int*[2]; 
    M[0] = new int[5]; 
    M[1] = new int[5]; 

    M2[0] = new int[5]; 
    M2[1] = new int[5]; 

    for(int i = 0; i<5; i++){
        M[0][i] = i; 
        M[1][i] = 5+i; 
    }

    //cout << "size of M : "<< sizeof(M[0][0]); 
    for(int i = 0; i < rows;i++ ){

        for(int j = 0; j<cols; j++ ){

            *(*(M2+i)+j) = *(*(M+i)+(cols -j-1)); 
            //cout << M2[i][j];
        }
    }
    for(int i = 0; i < rows;i++ ){
        for(int j = 0; j<cols; j++ ){

            cout << *(*(M2+i)+j);
        }
    }


    //part of task 3 
    int x, y;
    for(x = 0; x < 14; ++x)
    {
        for(y = 0; y < 6; ++y)
        {
            printf("(x=%2d, y=%d) -> index %d\n", x, y, ii(x, y));
        }
    }
    
    return 0; 
}
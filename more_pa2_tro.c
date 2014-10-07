/* According to Slides
Just do it trivially if the board is 2x2, else:
Divide the board into four smaller boards (introduce holes at the corners of the three smaller boards to make them look like original problems)
Conquer using the same algorithm recursively
Combine by placing a single tromino_tiling in the center to cover the three introduced holes

Representation as

UL * * LL *   UR * *  LR   *
   *	  * *	   *     * *
   
*/

#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include <time.h>  

int **tromino_matrix;     
int j,k,flag=1;

/*allocate2DArray according to no of ROWS and COLS provided, this will return the 2D array after allocating the memory */
int **allocate2DArray(int row, int col) 
{  
    int** arr;
    int* temp;

	/*NO of rows memory allocated*/
    arr = (int**)malloc(row * sizeof(int*));
    /*NO of rows * cols memory allocated*/
	temp = (int*)malloc(row * col * sizeof(int));
	int i = 0;
    for (i = 0; i < row; i++) {
        arr[i] = temp + (i * col);
    }
	/*return the 2D array after allocating the memory*/
    return arr;

}
/*PRINT 2DArray according to no of ROWS and COLS same provided*/
void printTromino(int **tromino_matrix_temp, int row_col) {
	printf("\n\n Sequence of Operation Each tile is represented as 'O' number and 'X' represent Missing cell \n\n");
		for( j=0;j<row_col;j++)  
		{  
		   for( k=0;k<row_col;k++)  
		   if(tromino_matrix_temp[j][k] == 0)
			   printf("|X	");
		   else 
				printf("|O	");
		printf("|\n");
		}
	printf("\n\n Sequence of Operation Each tile is represented as unique number and Zero represent Missing cell \n\n");
	
	for( j=0;j<row_col;j++)  
		{  
		   for( k=0;k<row_col;k++)  
			   printf("|%d	",tromino_matrix_temp[j][k]);  
			   printf("|\n");
		}
}


/*INITIALIZE 2DArray according to no of ROWS and COLS same provided*/
void initialize2DArray(int row_col) {
	for( j=0;j<row_col;j++)            //   
	   for( k=0;k<row_col;k++)  
		  tromino_matrix[j][k]=0;  
}
/*The problem is Tromino divide-and-conquer algorithm*/
void tromino(int **a,int x1,int y1,int length,int x,int y)   
    {                                                            
        int i=length/2;              
        if(i-1==0)  
        {  
            if(x<=x1+i-1&&y>y1+i-1)
                a[x1+i-1][y1+i-1]=a[x1+i][y1+i-1]=a[x1+i][y1+i]=flag++;  //2,3,4   
			else if(x<=x1+i-1&&y<=y1+i-1)   //  
			    a[x1+i-1][y1+i]=a[x1+i][y1+i]=a[x1+i][y1+i-1]=flag++;    //1,4,3   
			else if(x>x1+i-1&&y<=y1+i-1)  
	            a[x1+i-1][y1+i-1]=a[x1+i-1][y1+i]=a[x1+i][y1+i]=flag++;  //2,1,4   
	        else  
                a[x1+i-1][y1+i-1]=a[x1+i-1][y1+i]=a[x1+i][y1+i-1]=flag++;//2,1,3   
        }  
        else  
        {  
            if(x<=x1+i-1&&y>y1+i-1)   
            {     
                a[x1+i-1][y1+i-1]=a[x1+i][y1+i-1]=a[x1+i][y1+i]=flag++;  
                tromino(a,x1,y1+i,i,x,y);            
                tromino(a,x1,y1,i,x1+i-1,y1+i-1);     
                tromino(a,x1+i,y1,i,x1+i,y1+i-1);    
                tromino(a,x1+i,y1+i,i,x1+i,y1+i);     
            }  
            else if(x<=x1+i-1&&y<=y1+i-1)  
            {  
                a[x1+i-1][y1+i]=a[x1+i][y1+i]=a[x1+i][y1+i-1]=flag++;  
                tromino(a,x1,y1+i,i,x1+i-1,y1+i);  
                tromino(a,x1,y1,i,x,y);           	
                tromino(a,x1+i,y1,i,x1+i,y1+i-1);  
                tromino(a,x1+i,y1+i,i,x1+i,y1+i);  
            }  
            else if(x>x1+i-1&&y<=y1+i-1)  
            {  
                a[x1+i-1][y1+i-1]=a[x1+i-1][y1+i]=a[x1+i][y1+i]=flag++;  
                tromino(a,x1,y1+i,i,x1+i-1,y1+i);  
                tromino(a,x1,y1,i,x1+i-1,y1+i-1);  
                tromino(a,x1+i,y1,i,x,y);          
                tromino(a,x1+i,y1+i,i,x1+i,y1+i);  
            }  
            else  
            {  
                a[x1+i-1][y1+i-1]=a[x1+i-1][y1+i]=a[x1+i][y1+i-1]=flag++;//2,1,3   
                tromino(a,x1,y1+i,i,x1+i-1,y1+i);    
                tromino(a,x1,y1,i,x1+i-1,y1+i-1);  
                tromino(a,x1+i,y1,i,x1+i,y1+i-1);   
                tromino(a,x1+i,y1+i,i,x,y);        
            }  
        }  
    }   
int main()  
    {
	while(1){
	flag = 1;
	int i = 1;
	int n;
					printf("To Exit press 0 or Enter value for 2^k x 2^k (1<=k<=6):: ");  
					scanf("%d",&n);  
					
					if(n == 0)
					exit(0);
					
					if(n < 1  || n > 6){
						printf("\n\n\nPlease only enter valid 2^k x 2^k (1<=k<=6):\n");
						exit(0);
					}
					
					for( j=0;j<n;j++) {
						i = i * 2;
					}
					printf("Max Row and Col Value ::%d",i);
					tromino_matrix = allocate2DArray(i,i);     //?   
      
					initialize2DArray(i);
					
					int X_Coordinate_Missing,Y_Coordinate_Missing;
					
					X_Coordinate_Missing = rand() % i;
					
					Y_Coordinate_Missing = rand() % i;
					
					printf( "\nX Coordinate of Missing Square Means X ROW POSITION of 2D matrix [X][Y]: %d ",X_Coordinate_Missing );
					printf( "\nY Coordinate of Missing Square: Means Y COLUMN POSITION of 2D matrix [X][Y]: %d",Y_Coordinate_Missing );
						
					if( X_Coordinate_Missing >= i  || Y_Coordinate_Missing >= i){
						printf("\n\n\nCOLUMN AND ROW COORDINATE IS GRAETER THAN SIZE OF MATRIX:\n");
						exit(0);
					}						
						tromino_matrix[X_Coordinate_Missing][Y_Coordinate_Missing]=0;           
						
					    tromino(tromino_matrix,0,0,i,X_Coordinate_Missing,Y_Coordinate_Missing);  
					  
						printf( "\n\n Tromino Tiling:: \n\n" );
						printTromino(tromino_matrix,i);
		}
 
      return EXIT_SUCCESS;
}  
   
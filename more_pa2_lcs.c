/*
According to slides

Initialize the first row and the first column   of the matrix LenLCS to 0
Calculate LenLCS (1, j) for j = 1,…, n
Then the LenLCS (2, j) for j = 1,…, n, etc.
Store also in a table an arrow pointing to the array element that was used in the computation.
Hence, the computation is O(mn)

*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* To find an LCS follow the arrows, for each  diagonal arrow there is a member of the LCS 
If Xi and Yj end with the same character xi=yj, the LCS must include the character. If it did not, we could get a longer LCS by adding the common character.
*/
void showlcs(char b[][101],char x[],int i,int j)
{
     if(i==0 || j==0)//if both seq. has zero length
      return;       //return null
	 /* To find an LCS follow the arrows, for each  diagonal arrow there is a member of the LCS */
     if(b[i][j]=='D')
     {
     showlcs(b,x,i-1,j-1);
     printf(" %c",x[i-1]);
     }
     else if(b[i][j]=='U')
     showlcs(b,x,i-1,j);
     else
     showlcs(b,x,i,j-1);
}


void lcs(char x[],char y[])
{
     int m,n,i,j,c[101][101];
     char b[101][101];
     m=strlen(x);//find length of 1st sequence
     n=strlen(y);//find lenght of 2nd sequence
	 /*Initialize the first row and the first column   of the matrix LenLCS to 0*/
     for(i=0;i<=m;i++)
		c[i][0]=0;//set first column to zero
     for(i=1;i<=n;i++)
		c[0][i]=0;//set first row to zero
		
	/*
	Calculate LenLCS (1, j) for j = 1,…, n
	Then the LenLCS (2, j) for j = 1,…, n, etc.
	Store also in a table an arrow pointing to the array element that was used in the computation.
	*/
     for(i=1;i<=m;i++)
     {
		for(j=1;j<=n;j++)
		{
			if(x[i-1]==y[j-1])
			{
				c[i][j]=c[i-1][j-1]+1;
				b[i][j]='D';//'\ ' is north-west direction
			}
			else if(c[i-1][j]>=c[i][j-1])
			{
				c[i][j]=c[i-1][j];
				b[i][j]='U';//'^' is north direction
			}
			else
			{
				c[i][j]=c[i][j-1];
				b[i][j]='L';//'<-' is west direction
			}
		}
    }
    showlcs(b,x,m,n);//print the result
}

int main(int argc, char* const argv [])
{

     if(argc !=3 || argc <3)
     {
        printf("Please enter in the format '.slash lcs string1 string2'\n\n");
        exit(0);
     }
     int len1, len2;
	 /*Length of first String*/
	 len1 = strlen(argv[1]);
	 /*Length of Second String*/
	 len2 = strlen(argv[2]);

     printf("\n\nlen1 = %d, len2 = %d \n\n",len1,len2);
     if(len1>100 || len2>100)
     {
		printf("\n\n\nPlease only enter string's with less than 100 character's:\n");
		exit(0);
     }

     char a[103],b[103];
	 /*Copy string One from input argument to a*/
     strcpy(a, argv[1]);
	 /*Copy string Second from input argument to b*/
     strcpy(b, argv[2]);

     printf("String 1 =%s \nString 2 =%s\n\n",a,b);

     printf("\nLCS is :");
	//recursive formula for computing lcs
     lcs(a,b);

     printf("\n");
}


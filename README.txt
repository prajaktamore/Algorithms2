Name: Prajakta More
BNumner: B00417755
BMail: pmore2@binghamton.edu


1) LCS

COMPILE:

$ cc -c more_pa2_lcs.c

$ cc -o lcs more_pa2_lcs.c

RUN:

$ ./lcs ABCD ABCD

len1 = 4, len2 = 4

String 1 =ABCD
String 2 =ABCD


LCS is : A B C D


$ ./lcs ABCD ADBC


len1 = 4, len2 = 4

String 1 =ABCD
String 2 =ADBC


LCS is : A B C

*****************************************************************************************************************
2)STRASSEN'S

COMPILE:

$ cc -c more_pa2_strassen.c

$ cc -o str more_pa2_strassen.c

RUN: Note : Input Parameter should be power of 2 and should not be greater than 100 as it can throw STACK OVERFLOW

$ ./str 2

First Matrix
81      27

12      62

Second Matrix
32      7

100     29

Normal Matrix Multiplication
5292    1350

6584    1882

Strassen Multiplication
5292    1350

6584    1882

$ ./str 4

First Matrix
47      65      31      23

29      30      58      69

98      6       4       55

35      66      19      20

Second Matrix
87      92      55      42

36      38      4       46

98      62      47      100

5       31      44      24

Normal Matrix Multiplication
9582    9429    5314    8616

9632    9543    7477    10054

9409    11197   8022    6112

7383    7526    3962    6886

Strassen Multiplication
9582    9429    5314    8616

9632    9543    7477    10054

9409    11197   8022    6112

7383    7526    3962    6886

*****************************************************************************************************************
3)Tromino Tiling
To Compile:
$ cc -c more_pa2_tro.c

$ cc -o tro more_pa2_tro.c

RUN:((1<=k<=6 and row=col and COLUMN AND ROW COORDINATE are Max Row and Col Value)
$ ./tro
To Exit press 0 or Enter value for 2^k x 2^k (1<=k<=6):: 1
Max Row and Col Value ::2
X Coordinate of Missing Square Means X ROW POSITION of 2D matrix [X][Y]: 1
Y Coordinate of Missing Square: Means Y COLUMN POSITION of 2D matrix [X][Y]: 1

 Tromino Tiling::



 Sequence of Operation Each tile is represented as 'O' number and 'X' represent
Missing cell

|O      |O      |
|O      |X      |


 Sequence of Operation Each tile is represented as unique number and Zero repres
ent Missing cell

|1      |1      |
|1      |0      |
To Exit press 0 or Enter value for 2^k x 2^k (1<=k<=6):: 2
Max Row and Col Value ::4
X Coordinate of Missing Square Means X ROW POSITION of 2D matrix [X][Y]: 2
Y Coordinate of Missing Square: Means Y COLUMN POSITION of 2D matrix [X][Y]: 1

 Tromino Tiling::



 Sequence of Operation Each tile is represented as 'O' number and 'X' represent
Missing cell

|O      |O      |O      |O      |
|O      |O      |O      |O      |
|O      |X      |O      |O      |
|O      |O      |O      |O      |


 Sequence of Operation Each tile is represented as unique number and Zero repres
ent Missing cell

|3      |3      |2      |2      |
|3      |1      |1      |2      |
|4      |0      |1      |5      |
|4      |4      |5      |5      |
To Exit press 0 or Enter value for 2^k x 2^k (1<=k<=6)::

*****************************************************************************************************************
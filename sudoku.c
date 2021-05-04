#include <stdio.h>
#include <stdlib.h>

#define N 9

void print(int arr[N][N]);
int isSafe(int grid[N][N], int row,int col, int num);
int solveSuduko(int grid[N][N], int row, int col);

int main(void) {
    FILE *fp;
    fp = fopen("sudoku.csv", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error reading file\n");
        return 1;
    }
    
    char array[9][9];
    int sudoku[9][9];
    for (int count = 0; count < 9; count++)
    {
           fscanf(fp, " %c,%c,%c,%c,%c,%c,%c,%c,%c", &array[count][0], &array[count][1],&array[count][2],&array[count][3],&array[count][4],&array[count][5],&array[count][6],&array[count][7],&array[count][8]);
    }
    
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9 ; j++)
        {
            if ((array[i][j]>'9')||(array[i][j]<'1'))
            {
                array[i][j]='0';
            }
            sudoku[i][j]=array[i][j]-'0';
        }
    }

    if (solveSuduko(sudoku, 0, 0)==1)
        print(sudoku);
    else
        printf("No solution exists");
    
    fclose(fp);

    return 0;
}

void print(int arr[N][N])
{
     for (int i = 0; i < N; i++)
      {
         for (int j = 0; j < N; j++)
            printf("%d ",arr[i][j]);
         printf("\n");
       }
}

int isSafe(int grid[N][N], int row,int col, int num)
{
     
    // 檢查同一列同一行有沒有相同的數字
    for (int x = 0; x <= 8; x++)
        if (grid[row][x] == num)
            return 0;
    for (int x = 0; x <= 8; x++)
        if (grid[x][col] == num)
            return 0;
 
    // 確認3*3框框中沒有相同的數字
    int startRow = row - row % 3,
                 startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j +
                          startCol] == num)
                return 0;
 
    return 1;
}

int solveSuduko(int grid[N][N], int row, int col)
{
    // 全部確認過後回傳1
    if (row == N - 1 && col == N)
        return 1;
 
    //  確認完一整列後，從下一列的第一個開始檢查
    if (col == N)
    {
        row++;
        col = 0;
    }
   
    // 查看所在的直列是否有給定的值，假如有的話，就再找下一格
    if (grid[row][col] > 0)
        return solveSuduko(grid, row, col + 1);
 
    for (int num = 1; num <= N; num++)
    {
        // 檢查目前可不可以放那個數字
        if (isSafe(grid, row, col, num)==1)
        {
            grid[row][col] = num;
            if (solveSuduko(grid, row, col + 1)==1)
                return 1;
        }
        //檢查到後來發現假設錯數字
        grid[row][col] = 0;
    }
    return 0;
}
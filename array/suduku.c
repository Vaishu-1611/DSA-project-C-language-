#include<stdio.h>
#include<stdbool.h>
#include<string.h>

bool validRow(int mat[9][9],int row)
{
    int vis[10]={0};
    for(int j=0;j<9;j++)
    {
        if(mat[row][j]!=0)
        {
            if(vis[mat[row][j]]==1)
                return false;
            vis[mat[row][j]]=1;
        }
    }
    return true;
}

bool validCol(int mat[9][9],int col)
{
    int vis[10]={0};
    for(int i=0;i<9;i++)
    {
        if(mat[i][col]!=0)
        {
            if(vis[mat[i][col]]==1)
                return false;
            vis[mat[i][col]]=1;
        }
    }
    return true;
}

bool submatValid(int mat[9][9],int startRow,int startCol)
{
    int vis[10]={0};
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(mat[i+startRow][j+startCol]!=0)
            {
                if(vis[mat[i+startRow][j+startCol]]==1)
                    return false;
                vis[mat[i+startRow][j+startCol]]=1;
            }
        }
    }
    return true;
}

bool isValidSudoku(int mat[9][9])
{
    for(int i=0;i<9;i++)
    {
        if(!validRow(mat,i) || !validCol(mat,i))
            return false;
    }
    for(int i=0;i<9;i+=3)
    {
        for(int j=0;j<9;j+=3)
        {
            if(!submatValid(mat,i,j))
                return false;
        }
    }
    return true;
}

int main()
{
    int mat[9][9]={{0,3,0,0,7,0,0,0,0},
                   {6,0,0,1,9,5,0,0,0},
                   {0,9,8,0,0,0,0,6,0},
                   {8,0,0,0,6,0,0,0,3},
                   {4,0,0,8,0,3,0,0,1},
                   {7,0,0,0,2,0,0,0,6},
                   {0,6,0,0,0,0,2,8,0},
                   {0,0,0,4,1,9,0,0,5},
                   {6,0,0,0,8,0,0,7,9}};
    
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
    if(isValidSudoku(mat))
        printf("The Sudoku board is valid.\n");
    else
        printf("The Sudoku board is not valid.\n");
    return 0;
}
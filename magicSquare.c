#include <stdio.h>
#include <stdlib.h>
int main()
{
	int size,i,j,row,col,count;
	int **square;
	printf("Input size : ");
	scanf("%d",&size);
	square =(int**)malloc(sizeof(int*)*size);
	for(i=0;i<size;i++)
	{
		square[i]=(int*)malloc(sizeof(int)*size);
	}

	for(i=0;i<size;i++)
	{	
		for(j=0;j<size;j++)
		{
			square[i][j]=0;
		}
	}
	square[0][(size-1)/2]=1;
	i=0;
	j=(size-1)/2;
    for(count=2;count<=size*size;count++)
	{
		row=(i-1<0)?(size-1):(i-1);
		col=(j-1<0)?(size-1):(j-1);

		if(square[row][col])
		{
			i=(++i)%size;
		}else
		{
			i=row;
			j=(j-1<0)?(size-1):(j-1);
		}
		square[i][j]=count;
	}

	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			printf("%5d", square[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

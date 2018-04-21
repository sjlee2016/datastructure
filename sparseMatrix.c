#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101
#define MAX_COL 101
#define COMPARE(x,y) ((x<y)?-1:((x==y)?0:1))
typedef struct {
    int col;
    int row;
    int value;
}term;

void printTerm(term d[], int );
void fast_transpose(term a[], term b[]);
void mmult(term a[], term b[], term d[]);
int main()
{

    term a[MAX_TERMS];
    term b[MAX_TERMS];
    term c[MAX_TERMS];
    int i, row, column, value,k1,k2;
    FILE* in1, *in2;
    in1 = fopen("A.txt", "r");
    in2 = fopen("B.txt", "r");
    if (in1 == NULL || in2 == NULL)
    {
	printf("error!\n");
	return 0;
    }
    fscanf(in1, "%d %d %d", &row, &column, &k1);
    a[0].row = row;
    a[0].col = column;
    a[0].value = k1;
    for (i = 1; i <= k1; i++)
    {
	fscanf(in1,"%d %d %d", &row, &column, &value);
	a[i].row = row;
	a[i].col= column;
	a[i].value = value;

//	printf("%d %d %d \n", a[i].row, a[i].col, a[i].value);
    }
 //   printf("\n");
   
    fast_transpose(a,b);

	/*
	fscanf(in2, "%d %d %d", &row, &column, &k2);
    b[0].row = row;
    b[0].col = column;
    b[0].value = k2;
//	printf("%d %d %d\n",row,column,k2);
    for (i = 1; i <= k2; i++)
    {
	fscanf(in2, "%d %d %d", &row, &column, &value);
	b[i].row = row;
	b[i].col = column;
	b[i].value = value;

//	printf("%d %d %d \n", b[i].row, b[i].col, b[i].value);
    }
   // printf("\n");

 //   mmult(a, b, c);
 
	//  printTerm(c,c[0].value);
 //   printf("%d\n",c[0].value);
    return 0;
*/
}
void printTerm(term d[], int a)
{
    int k, i;
    for (i = 1; i <= a; i++)
    {
	printf("%d %d %d \n", d[i].row, d[i].col, d[i].value);
    }
}
void storesum(term d[], int * totalD, int row, int column, int *sum)
{
    if(*sum)
	if (*totalD < MAX_TERMS) {
//	printf("%d ",*totalD);
	    d[++(*totalD)].row = row;
	    d[*totalD].col = column;
	    d[*totalD].value = *sum;
	    *sum = 0;
	}
	else {
	    fprintf(stderr, "Numbers of terms in product exceeds %d \n", MAX_TERMS);
	    exit(EXIT_FAILURE);
	}
}



void fast_transpose(term a[], term b[])
{ /* the transpose of a is placed in b */
    int row_terms[MAX_COL], starting_pos[MAX_COL];
    int i, j, num_cols = a[0].col, num_terms = a[0].value;
    b[0].row = num_cols; b[0].col = a[0].row;
    b[0].value = num_terms;

    if (num_terms > 0) { /* nonzero matrix */
	for (i = 0; i < num_cols; i++)
	    row_terms[i] = 0;

	for (i = 1; i <= num_terms; i++) 
	    row_terms[a[i].col]++;

	starting_pos[0] = 1;

	for (i = 1; i < num_cols; i++)
	    starting_pos[i] = starting_pos[i-1] + row_terms[i-1];

	for (i = 1; i <= num_terms; i++) {
	    j = starting_pos[a[i].col]++;
	    b[j].row = a[i].col; b[j].col = a[i].row;
	    b[j].value = a[i].value;
	}
    }

	for(i=0;i<num_cols;i++)
		printf("row_terms[%d] = %d\n", i, row_terms[i]);
	for(i=0;i<=num_terms;i++)
	{
			printf("starting pos [%d]: %d\n",i, starting_pos[i]);
	}
}
void mmult( term a[], term b[], term c[])
    /* multiply two sparse matrices */
{
    int i, j, column, totalb = b[0].value, totald = 0;
    int rows_a = a[0].row, cols_a = a[0].col, totala = a[0].value;
    int cols_b = b[0].col;
    int row_begin = 1, row = a[1].row, sum = 0;

    term new_b[MAX_TERMS];

    if (cols_a != b[0].row) {
	fprintf(stdout, "Incompatible matrices\n");
	exit(1);
    }

    fast_transpose(b, new_b);
    /* set boundary condition */

    a[totala+1].row = rows_a;
    new_b[totalb+1].row = cols_b; new_b[totalb+1].col = -1;

    for (i = 1; i <= totala; ) {
	column = new_b[1].row;
	for (j = 1; j <= totalb+1; ) {
	    /* multiply row of a by column of b */
	    if (a[i].row != row) {
		storesum(c, &totald, row, column, &sum);
		i = row_begin;
		for ( ; new_b[j].row == column; j++);
		column = new_b[j].row;
	    }
	    else if (new_b[j].row != column) {
		storesum(c, &totald, row, column, &sum);
		i = row_begin;
		column = new_b[j].row;
		}
		else {
		switch (COMPARE(a[i].col, new_b[j].col)) {
		case -1: i++; break;
		case 0 : sum += (a[i++].value * new_b[j++].value); break;
		case 1 : j++;
		}
		}} /* end of for j <= totalb+1 */
	for ( ; a[i].row == row; i++);
	row_begin = i; row = a[i].row;
	} /* end of for i <= totala */
c[0].row = rows_a; c[0].col = cols_b;
c[0].value = totald;
//printf("%d",totald);
}

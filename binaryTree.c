/*
   prac8.c
   이름: 이세진
   학번: 20161619
*/

#include <stdio.h>
#define N 10
typedef struct node * ptr;
typedef struct node{

	ptr left;
	int data;
	ptr right;
}node;


void printList(node** head, int version);

void insert(node ** head, int data)
{
	int flag = 0;
	node* temp;
	node* newNode = (node*)malloc(sizeof(node));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = data;
	if ((*head)->left == (*head) && (*head)->right == (*head)) {  // empty
		// first element inserted
		newNode->left=(*head);
		(*head)->left = newNode;
		(*head)->right = newNode;
		newNode->right=(*head);

	}
	else if (((*head)->right->data > data))
	{
		// element inserted in the first position
        	temp=(*head)->right;
		temp->left=newNode;
		newNode->right=temp;
		newNode->left=(*head);
		(*head)->right=newNode;
	}
	else if((*head)->left->data<data)
        {
               newNode->left=(*head)->left;
               newNode->right=(*head);
	       (*head)->left->right=newNode;
               (*head)->left=newNode;
       }
       else
       {

		for (temp = (*head)->right; temp!= (*head); temp = temp->right)
		{


			if (temp->data > data)
			{
				temp->left->right = newNode;
				newNode->left=temp->left;
				newNode->right=temp;
				temp->left=newNode;
				flag = 1;
				break;
			}
		}

	}

	printList(head,0);
        printList(head,1);

}

void printList(node** head, int version)
{
	node* temp;
 if(version==0)
{
   printf("Left to Right : ");

	for (temp = (*head)->right; temp!= (*head); temp = temp->right)
	{
		printf("%d ", temp->data);
	}
	printf("\n");
}
else
{
   printf("Right to Left : ");
     for(temp=(*head)->left;temp!=(*head);temp=temp->left)
      {
                printf("%d ", temp->data);
      }
     printf("\n");
     printf("-------------------------------\n");
}
}
int delete(node ** head,  int num)
{
   int i;
   node * temp, *temp2;

   if((*head)->right->data==num)
   {
	temp=(*head)->right;
	(*head)->right=temp->right;
	temp->right->left=(*head);
	free(temp);
   }else if((*head)->left->data==num)
   {
      temp=(*head)->left;
      (*head)->left->left->right=(*head);
      (*head)->left=temp->left;
      free(temp);
   }else
   {
   for(temp=(*head)->right;temp!=(*head);temp=temp->right){
       if(temp->data==num)
		break;
   }
        temp2=temp->left;
	temp->left->right=temp->right;
	temp->right->left=temp2;
    }
    printList(head,0);
    printList(head,1);
}
int search(node * head, int data)
{
	node * temp;
	int pos=1;
	for(temp=(head)->right;temp!=(head);temp=temp->right)
	{
		if(temp->data==data)
		{
			return pos;
		}
		pos++;
	}
	return -1;
}

int main()
{
	int i,pos, data;
	node* head = (node*)malloc(sizeof(node));
	head->left = head;
	head->right = head;
	int A[N] = { 10, 6, 2, 9, 12, 1, 7 , 8 , 13 , 5 };
	for (i = 0; i < N; i++)
	{
		insert(&head, A[i]);
		//printList(&head);

	}
	printf("\nEnter data to search : ");
	scanf("%d",&data);
	pos=search(head,data);
	if(pos==-1)
	{
		printf("There is no %d in the list\n\n",data);
	}else
	{
		printf("%d is in %d position from left to right and %d from right to left.\n\n", data,pos, N-pos+1);
	}

	printf("Enter data to delete : ");
	scanf("%d",&data);
	pos=search(head,data);
	if(pos==-1)
	{
		printf("Cannot delete!! There is no %d in the list.\n",data);
	}else
	{
                printf("%d deleted!!\n\n", data);
		delete(&head,data);
	}

}

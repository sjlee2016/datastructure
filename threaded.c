
		temp = insucc(r);
		temp->leftChild = r;
	}

}
void insert(threadedPointer s, char data)
{
	threadedPointer newNode = (threadedPointer)malloc(sizeof(threadedTree));
	newNode->data = data;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;
	newNode->leftThread = TRUE;
	newNode->rightThread = TRUE;
	insertRight(s, newNode);

}
void tinorder(threadedPointer tree) {
	threadedPointer temp = tree;
	for (;;)
	{

		temp = insucc(temp);
		if (temp == tree) break;
		printf("%3c", temp->data);
	}
	printf("\n");
}
threadedPointer insucc(threadedPointer tree) {
	threadedPointer temp;
	temp = tree->rightChild;
	if (!tree->rightThread)
	{

		while (!(temp->leftThread))
		{

			temp = temp->leftChild;
		}
	}
		return temp;
}
void construct_tree(threadedPointer tree) {
	int i = 0;
	threadedPointer *node = (threadedPointer**)malloc(sizeof(threadedPointer*)*10);
	// initialize nodes
	for (i = 0; i < 10; i++) {
		node[i] = (threadedPointer)malloc(sizeof(threadedTree));
		node[i]->data = 'A' + i;
		node[i]->leftThread = node[i]->rightThread = FALSE;
	}

	// root -> A
	tree->leftChild = node[0];
	// A -> B, A -> C
	node[0]->leftChild = node[1];
	node[0]->rightChild = node[2];
	// B -> D, B -> E
	node[1]->leftChild = node[3];
	node[1]->rightChild = node[4];
	// C -> F, C -> G
	node[2]->leftChild = node[5];
	node[2]->rightChild = node[6];
	// D -> H, D -> I
	node[3]->leftChild = node[7];
	node[3]->rightChild = node[8];

	// E --> B, E --> A
	node[4]->leftThread = node[4]->rightThread = TRUE;
	node[4]->leftChild = node[1];
	node[4]->rightChild = node[0];
	// F --> A, F --> C
	node[5]->leftThread = node[5]->rightThread = TRUE;
	node[5]->leftChild = node[0];
	node[5]->rightChild = node[2];
	// G --> C, G --> root
	node[6]->leftThread = node[6]->rightThread = TRUE;
	node[6]->leftChild = node[2];
	node[6]->rightChild = tree;
	// H --> root, H --> D
	node[7]->leftThread = node[7]->rightThread = TRUE;
	node[7]->leftChild = tree;
	node[7]->rightChild = node[3];
	// I --> D, I --> B
	node[8]->leftThread = node[8]->rightThread = TRUE;
	node[8]->leftChild = node[3];
	node[8]->rightChild = node[1];
}

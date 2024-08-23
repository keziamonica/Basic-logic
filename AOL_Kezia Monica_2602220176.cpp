#include <stdio.h>
#include <stdlib.h>

struct data
{
	int value;
	int height; 
	struct data *left, *right;
};

struct data *createNode (int value)
{
	struct data*newNode = (struct data*)malloc(sizeof(struct data));
//	struct data*newnode=(struct data*)malloc(sizeof(struct data));
	newNode->value = value; //enter value
	newNode->height = 1;
	newNode->left = NULL; //assign child
	newNode->right = NULL;
	return newNode;
}

int height (struct data *tree)
{
	if (tree == NULL)
	{
		return 0;
	}
	return tree->height;
}

int max(int left,int right) //buat apa yh
{
	if(left>right)
	{
		return left;
	}
	else
	{
		return right;
	}
}

int getBalance(struct data*tree) //masih bingung konsep nya yh
{
	if(tree==NULL)
	{
		return 0;
	}
	return height(tree->left)-height(tree->right);
}

struct data *RRrotation(struct data *tree) 
{
	struct data *mid = tree->right;
	struct data *bottom = mid->left;
	
	mid->left = tree;
	tree->right = bottom;
	
	tree->height = 1 + max(height(tree->left), height(tree->right));
	mid->height = 1 + max(height(mid->left), height(mid->right));
	
	return mid;
}

struct data *LLrotation(struct data *tree) 
{
	struct data *mid = tree->left;
	struct data *bottom = mid->right;
	
	mid->right = tree;
	tree->left = bottom;
	
	tree->height = 1 + max(height(tree->left), height(tree->right));
	mid->height = 1 + max(height(mid->left), height(mid->right));
	
	return mid;
}

struct data *insert(struct data *tree, int value) 
{
	if(tree == NULL)
	{
		return createNode(value);
	}
	
	if(value < tree->value) 
	{
		tree->left = insert(tree->left, value);
	} 
	else if(value > tree->value) 
	{
		tree->right = insert(tree->right, value);
	} 
	else 
	{
		return tree;
	}
	
	tree->height = 1 + max(height(tree->left), height(tree->right));
	int balance = getBalance(tree);
	
	//Left rotate
	if(balance < -1 && value > tree->right->value) 
	{
		return RRrotation(tree);
	}
	//Right rotate
	if(balance > 1 && value < tree->left->value) 
	{
		return LLrotation(tree);
	}
	//Left Right rotate
	if(balance > 1 && value > tree->left->value) 
	{
		tree->left = RRrotation(tree->left);
		return LLrotation(tree);
	}
	
	//Right Left rotate
	if(balance < -1 && value < tree->right->value) 
	{
		tree->right = LLrotation(tree->right);
		return RRrotation(tree);
	}
	
	return tree;
}

struct data *cari(struct data *tree, int value)
{  
    if(tree == NULL)
    {
    	return NULL;
	}
    
	if(value < tree->value)
	{
		return cari(tree->left, value);
	}
    else if (value > tree->value)
    {
    	return cari(tree->right, value);
	}
        
    return tree;
}


struct data *minValueNode (struct data *tree)
{
	struct data *temp = tree;
	while (temp->left != NULL)
	{
		temp = temp->left;
	}
	return temp;
}

struct data *deleteTree (struct data *tree, int value)
{
	if(tree == NULL)
	{
		printf ("The tree is still empty\n");
		return tree;
	}
	
	if(value < tree->value) //ngisi node left / yang lebih kecil
	{
		tree->left = deleteTree(tree->left, value);
	}
	else if(value > tree->value) //ngisi node right / yang lebih besar
	{
		tree->right = deleteTree(tree->right, value);
	}
	else //kalau ketemu
	{
		if (tree->left == NULL) //mau hapus yang punya anak di kanan aja
		{
			struct data *temp = tree;
			tree = tree->right;
			free (temp);
		}
		else if (tree->right == NULL) //mau hapus yang punya anak di kiri aja
		{
			struct data *temp = tree;
			tree = tree->left;
			free (temp);
		}
		else
		{
			struct data *minValue = minValueNode(tree->right); //successor, nilai terkecil di node right
			tree->value = minValue->value;
			tree->right = deleteTree(tree->right, minValue->value);
		}
		
	}
	
	if (tree == NULL)
	{
		return tree;
	} 
	
	tree -> height = 1 + max(height(tree -> left), height(tree -> right));
	int balance = getBalance(tree);
	
	//Kalo kiri ne kosong, berat ke kanan
	if (balance < -1 && getBalance(tree -> right) <= 0)
	{
		return RRrotation(tree);
	} 
	
	//Kalo kanan ne kosong, berat ke kiri
	else if (balance > 1 && getBalance(tree -> left) >= 0)
	{
		return LLrotation(tree);
	} 
	
	//RL rotation
	else if (balance < -1 && getBalance(tree -> right) > 0)
	{
		tree -> right = LLrotation(tree -> right);
		return RRrotation(tree);
	}
	
	//LR Rotation
	else if (balance > 1 && getBalance(tree -> left) < 0)
	{
		tree -> left = RRrotation(tree -> left);
		return LLrotation(tree);
	}
	
	return tree;
}




void displayPreorder(struct data *tree)
{
	if (tree != NULL)
	{
		printf ("%d ", tree->value);
		displayPreorder(tree->left);
		displayPreorder(tree->right);
	}
}

void displayInorder(struct data *tree)
{
	if (tree != NULL)
	{
		displayInorder(tree->left);
		printf ("%d ", tree->value);
		displayInorder(tree->right);
	}
}

void displayPostorder(struct data *tree)
{
	if (tree != NULL)
	{
		displayPostorder(tree->left);
		displayPostorder(tree->right);
		printf ("%d ", tree->value);
	}
}

void hapusAll(struct data *tree)
{
	if(tree != NULL)
	{
		hapusAll (tree->left);
		hapusAll (tree->right);
		free(tree);
	}
}

int main ()
{
	struct data *tree = NULL;
	int option;
	int value;
	int value2;
	
	do
	{
		do 
		{
			printf ("1. Insertion\n");
			printf ("2. Deletion\n");
			printf ("3. Traversal\n");
			printf ("4. Exit\n");
			printf ("Choose: ");
			scanf ("%d", &option);
		}
		while (option < 1 || option > 4);
		
		switch (option)
		{
			case 1: 
				{
					//insertion
					printf ("Insert: ");
					scanf ("%d", &value);
					
					tree = insert(tree, value);
					break;
				}
			case 2:
				{
					//deletion
					printf("Delete: ");
					scanf ("%d", &value2);
					if (!(cari(tree,value2)))
					{
						printf ("Data Not Found\n");
					}
					else
					{
						printf ("Data Found\n");
						tree = deleteTree(tree, value2);
						printf ("Value %d was deleted\n", value2);
					}
					break;
				}
			case 3:
				{
					//traversal
					printf ("Preorder: ");
					displayPreorder(tree);
					printf ("\nInorder: ");
					displayInorder(tree);
					printf ("\nPostorder: ");
					displayPostorder(tree);
					printf ("\n");
					break;
				}
			case 4:
				{
					hapusAll(tree);
					break;
				}
		}	
	}
	while (option != 4);
	
	return 0;
}

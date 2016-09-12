/*********************************************
 * Name: Moesaeah King
 *
 * ID: 16150318
 *
 * Description: Pre-Lab / Lab 9
 *********************************************/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
typedef struct node_ {
		int data;
			struct node_* left;
				struct node_* right;
} Node;

Node* buildBalancedTree(int array[], int low, int high);
Node* newNode(int data);
void quicksort(int a[], int low, int high);
void printTree(Node* root, int depth);
void swap(int a[], int left, int right);
void freeTree(Node* root);
void padding(int depth);
void postOrder(Node* root);
void preOrder(Node* root);
void inOrder(Node* root);
int height(Node* root);
int partition( int a[], int low, int high);
int main(int argc, char* argv[]) {
		srand(time(NULL));
		int array[10];
		int i = 0;
		for( i = 0; i < 10; i++){
			array[i] = rand() % (20-10) + 10;
		}
		quicksort(array, 0, 9);
		Node* root = buildBalancedTree(array, 0, 9);
		printTree(root, 0);
		printf("postOrder is: \n");
		postOrder(root);
		printf("\n");
		printf("preOrder is: \n");
		preOrder(root);
		printf("\n");
		printf("InOrder is: \n");
		inOrder(root);
		printf("\n");
		int length = height(root);
		printf("The height of the tree is: %d\n", length);
		freeTree(root);
		return 0;
}
void swap (int a[], int left, int right)
{
 int temp;
 temp=a[left];
 a[left]=a[right];
 a[right]=temp;
}

void quicksort( int a[], int low, int high )
{
 int pivot;

 if ( high > low )
 {
  pivot = partition( a, low, high );
  quicksort( a, low, pivot-1 );
  quicksort( a, pivot+1, high );
 }
}

int partition( int a[], int low, int high )
{
 int left, right;
 int pivot_item;
 left = low;
 pivot_item = a[low];
 right = high;
 while ( left < right )
 {
  // Move left while item < pivot
  while( a[left] <= pivot_item )
   left++;
  // Move right while item > pivot
  while( a[right] > pivot_item )
   right--;
  if ( left < right )
   swap(a,left,right);
 }
 // right is final position for the pivot
 a[low] = a[right];
 a[right] = pivot_item;
 return right;
}

void postOrder(Node* root){
	if(root != NULL) {
        postOrder(root->right);
        postOrder(root->left);
        printf(" %d ", root->data);
    }
}
void inOrder(Node* root){
	if(root != NULL){
		inOrder(root->left);
		printf(" %d ", root->data);
		inOrder(root->right);
	}
}

void preOrder(Node* root){
	if( root != NULL){
		printf(" %d ", root->data);
		preOrder(root->left);
		preOrder(root->right);
	}
}
int height(Node* root){
	 if (root==NULL)
       return 0;
   else
   {
       /* compute the depth of each subtree */
       int leftsidesDepth = height(root->left);
       int rightsidesDepth = height(root->right);

       /* use the larger one */
       if (leftsidesDepth > rightsidesDepth){
           return(leftsidesDepth+1);
	   }
       else{

	   return(rightsidesDepth+1);
	   }
   }
}
Node* buildBalancedTree( int array [], int low, int high){
	    /* Base Case */
	    if (low > high)
	      return NULL;
	    /* Get the middle element and make it root */
	    int mid = (low + high)/2;
	    Node *root = newNode(array[mid]);

	    root->left =  buildBalancedTree(array, low, mid-1);

	    root->right = buildBalancedTree(array, mid+1,high);

	    return root;
}
Node* newNode(int data){
	    Node* node = (Node*)malloc(sizeof(Node));

	    node->data = data;
	    node->left = NULL;
	    node->right = NULL;

	    return node;
}
void printTree(Node* root, int depth) {
		if (root == NULL) {
			padding(depth);
			printf("~\n");
		}
		else{
			printTree(root->right, depth + 1);
			padding(depth);
			printf("%d\n", root->data);
			printTree(root->left, depth + 1);
		}
}
void freeTree(Node* root){
	if (root == NULL){
		return;
	}
	freeTree(root->left);
	freeTree(root->right);

	free(root);
}

void padding(int depth) {
		int i;
		for (i = 0; i < depth; i++){
			putchar('\t');
		}
}

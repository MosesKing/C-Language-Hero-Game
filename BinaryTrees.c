#include <stdlib.h>
#include <stdio.h>

typedef struct node_ {
		int data;
			struct node_* left;
				struct node_* right;
} Node;


void printTree(Node* root, int depth);
Node* insert(Node* root, int data);
Node* delete(Node* root, int data);
void freeTree(Node* root);
int min(Node* root);
Node* buildTree(char* filename);
Node* flipTree(Node* root);
//void preOrder(Node* root);
//void inOrder(Node* root);
int main(int argc, char** argv){
	if(argc != 2){
		printf("insufficient arguments");
	}

	Node* root = buildTree(argv[1]);
	printf("The initial tree");
	printTree(root, 0);;
	printf("What number would you to delete?\n");
	int data;
	scanf("%d", &data);
	delete(root, data);
	printf("The tree without %d", data);
	printTree(root, 0);
	//bonus
	printf("Your Tree Mirrored\n");
	Node* mirror = flipTree(root);
	printTree(mirror, 0);
	freeTree(root);
	return 0;
}
/*void inOrder(Node* root){
	if(root != NULL){
		inOrder(root->left);
		printf("%d\n", root->data);
		inOrder(root->right);
	}
}
*/
/*void preOrder(Node* root){
	if( root != NULL){
		printf("%d\n", root->data);
		preOrder(root->left);
		preOrder(root->right);
	}
}
*/
void freeTree(Node* root){
	if (root == NULL){
		return;
	}
	freeTree(root->left);
	freeTree(root->right);

	free(root);
}
Node* insert(Node* root, int data) {
	if(root == NULL){
		root = ((Node*)(malloc(sizeof(Node))));
		root->data = data;
		root->left = NULL;
		root->right = NULL;
	}
	else if(data < root->data){
		root->left = insert(root->left, data);
	}
	else if(data > root->data){
		root->right = insert(root->right, data);
	}
	return root;
}
		//
Node* delete(Node* root, int data){
	if( root == NULL){
		return root;
	}

	if(data < root->data){
		root->left = delete(root->left, data);
	}

	else if( data > root->data){
		root->right = delete(root->right, data);
	}

	else{

		if(root->left == NULL){
			Node* temp = root->right;
			free(root);
			return temp;
		}
		else if(root->right == NULL){
		       Node* temp = root->left;
		       free(root);
                       return temp;
		}
		int temp = min(root->right);

		root->data = temp;

		root->right = delete(root->right, temp);

	}
	return root;
}
//extra credit
Node* flipTree( Node* root){
 Node* temp;
 if (root==NULL){
	 return NULL;
 }
 else{
    temp = malloc(sizeof(Node));
    temp->data   = root->data;
    temp->left  = flipTree(root->right);
    temp->right = flipTree(root->left);
 }


 return temp;

}


int min(Node* root){
	if (root == NULL){
		printf("List is empty there is no minimum value");
		return 0;
	}
	while(root->left != NULL){
		root = root->left;
	}
	return root->data;
}
Node* buildTree(char* filename){
	FILE *cfptr = fopen(filename, "r");
	if( cfptr == NULL){
		printf("No file to be open");
	}
	int data;
	Node* Tree = NULL;
	while(!feof(cfptr)){
		fscanf(cfptr, "%d\n", &data);
		Tree = insert(Tree, data);
	}
	fclose(cfptr);
	return Tree;
}

void padding(int depth) {
	int i;
	for (i = 0; i < depth; i++) {
		putchar('\t');
	}
}
void printTree(Node* root, int depth) {
	if (root == NULL) {
		padding(depth);
		printf("~\n");
	}
	else {
		printTree(root->right, depth + 1);
		padding(depth);
		printf("%d\n", root->data);
		printTree(root->left, depth + 1);
		}
}

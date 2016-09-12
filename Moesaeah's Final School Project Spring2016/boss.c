#include "game.h"



Boss* loadBoss(){
/*	typedef struct boss_
{
	char name[40];
	int health;
	int maxHealth;
	int baseDefense;
	int baseAttack;
	int baseSpeed;
	DecisionTreeNode* root;
} Boss;
*/
/*   this is the structure of DecisionTreeNode
typedef struct dTree_
{
	int healthFloor;
	int healthCeiling;
	struct dTree_* left;
	struct dTree_* right;
	ActionNode* FirstAction;
} DecisionTreeNode;
*/

	FILE *cfptr = fopen("Boss.txt", "r");
	if( cfptr == NULL){
		printf("The File could not be open\n");
		return 0;
	}
	// intializing the boss so we can set the name
	Boss* boss;
	boss = malloc(sizeof(Boss));
	 //we want to assign the first line of the file to the boss characteristics
	fscanf(cfptr,"%s | %d | %d | %d | %d", boss->name, &boss->health, &boss->baseDefense, &boss->baseAttack,&boss->baseSpeed);
	// setting the boss's max health to the health we just scanned in
	boss->maxHealth = boss->health;
	// our variables for making the tree!
	DecisionTreeNode* Tree;
	// Gunna set equal to null because if not it's gunna be some strange things happening and no aha
	DecisionTreeNode* Current = NULL;
	int Decision = 0;
	int i;
	ActionNode* newNode = NULL;

	while(!feof(cfptr)){
			Tree = malloc(sizeof(DecisionTreeNode));
			Tree->left = NULL;
			Tree->right = NULL;
			Tree->FirstAction = NULL;
			fscanf(cfptr, "%d | %d | %d", &Tree->healthFloor, &Tree->healthCeiling, &Decision);
			for(i = 0; i < Decision; i++){
				newNode = malloc(sizeof(ActionNode));
				newNode->next = NULL;
				fscanf(cfptr, "%d", (int*)&newNode->decision);
				Tree->FirstAction = addActionToList(Tree->FirstAction, newNode);
			}
			Current = addNodeToTree(Current, Tree);
	}
		boss->root = Current;
		fclose(cfptr);
    		return boss;
/*
Input: None
Return: a fully imported boss
This will be the controller for all the boss loading.
The boss will have all the basic stats as if its a hero,
but it will have a decision tree for its AI. This tree will have nodes that
have a health floor and health ceiling. Having the bosss current health lie
in between those two values will determine if that node will be selected.
Once the appropriate node is found, a pointer inside the node will lead to a
linked list of decisions that the boss will take in order. See the sample
output for a picture of this. Use the functions below to
help complete the loading process for this function.
*/
}

ActionNode* addActionToList(ActionNode* front, ActionNode* newAction)
{
	/* to help me see the ActionNode Struct
	typedef struct aNode_
	{
		Decision decision;
		struct aNode_* next;
	} ActionNode;
	*/
	ActionNode *current;
	current = front;
	// wanna make sure that if the list has nothing in it then we can
	// just add the newAction and start the beginning of our list
	if(!front){
		return newAction;
	}
	// otherwise we wanna get to the bottom of the list and then add the new
	// action
	while(current->next != NULL){
		current = current->next;
	}
	// we're at the bottom and now let's add the new action
	current->next = newAction;
	// return the head of the list back up to whereever it's called
	return front;



/*
Input: the head of the linked list and the node to be added to the linked list
Return: the head of the linked list
This function is for the linked list
that is connected to its corresponding tree node.
Starting from the head of the list, it will tack on the new node at the
end of the list each time it is called.
*/

}

DecisionTreeNode* addNodeToTree(DecisionTreeNode* root, DecisionTreeNode* newNode){
	/*   this is the structure of DecisionTreeNode
	typedef struct dTree_
	{
		int healthFloor;
		int healthCeiling;
		struct dTree_* left;
		struct dTree_* right;
		ActionNode* FirstAction;
	} DecisionTreeNode;
	*/
/*
	typedef struct aNode_
	{
		Decision decision;
		struct aNode_* next;
	} ActionNode;
*/
// if there is nothing in the root

if(root == NULL){
	return newNode;
}
// if there root's healthCeiling is > than the newNodes health ceiling recursive call the but go left
else if(root->healthCeiling > newNode->healthCeiling){
	root->left = addNodeToTree(root->left, newNode);
}
// if the root's healthCeiling < than the NewNodes health ceiling recursive call of the funcition but go right
else if(root->healthCeiling < newNode->healthCeiling){
	root->right = addNodeToTree(root->right, newNode);
}
return root;




/*
Input: the root of the BST described above, and the node to be added to this tree
Return: the root of the BST
ofunction is for dealing with each of the nodes once the linked list
is built for it and attached. Add the node to the tree as the same way you
have built BSTs before. Keep in mind that each node covers a range of values:
if the nodes range is lower than the range of the root, put it on the left
side of the tree. If the range is above the range of the root, put it on the
right.
*/
}

ActionNode* fetchNewList(Boss* boss, DecisionTreeNode* root)
{


	/*   this is the structure of DecisionTreeNode so i can see
	typedef struct dTree_
	{
		int healthFloor;
		int healthCeiling;
		struct dTree_* left;
		struct dTree_* right;
		ActionNode* FirstAction;
	} DecisionTreeNode;
	*/

	// if root is null that means there nothing to go fetch
	if(root == NULL){
		printf("The Boss isn't fighting right now, he's too exhausted come again tomorrow! Thanks!\n");
		return 0;
	}
	if(boss->health < root->healthCeiling && boss->health > root->healthFloor){
		return root->FirstAction;
	}
	// if the boss' health is less than roots health floor we will go left and
	else if(boss->health < root->healthFloor){
		return fetchNewList(boss, root->left);
	}
	// if the boss' health is greater than roots health floor we will go right and
	else if( boss->health > root->healthCeiling){
		return fetchNewList(boss, root->right);
	}
	// if the boss' health is greater than the floor but less than the ceiling
	return root->FirstAction;

}
/*
Input: the boss and the root of its BST
Return: the LINKED LIST that is found inside the node that has the health
range that contains the current health As described, search for the node
in the BST that has the health range that contains the bosss current health.
Once found, return the head of the linked list found inside the node.
*/


void freeBossTree(DecisionTreeNode* root)
{
	// Just in case your confused Seth, ahaha if the root is NULL that would
	//  mean there nothing to delete...
	if (root == NULL){
		return;
	}
	freeBossTree(root->left);
	freeBossTree(root->right);
        freeActionListInNode(root->FirstAction);
	free(root);
}

/*
Input: the root of the bosss BST
Return: none
Free the entire tree. Remember: freeing the nodes isnt good enough.
Each node leads to a linked list, so you have to free that first!
*/

void freeActionListInNode(ActionNode* head){
	ActionNode* temp;
	while(head != NULL){
		temp = head;
		head = head->next;
		free(temp);
	}

/*
Input: the head of the linked list connected to the tree node
Return: none
Call this function in freeBossTree().
This will be used in conjunction to free the linked list connected to the node
before freeing the node itself.
*/
}

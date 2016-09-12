/*****************************************************
 * Moesaeah King
 *
 * ID: 16150318
 *
 * Description: Lab 7
 * **************************************************/
#include <stdlib.h>
#include <stdio.h>

typedef struct node_{
	int data;
	struct node_* next;
} Node;

// prototypes
Node* enqueue(Node* head, int data);
int dequeue(Node** frontptr);
void printQueue(Node* front);
void freeQueue(Node* front);
int main(void){
	printf("Enter 1 to Enqueue\n");
	printf("Enter 2 to Dequeue\n");
	printf("Enter 3 to Quit\n");
	int choice;
	scanf("%d", &choice);
	Node* head = NULL;
	int data;
	int i;
	while(choice != 4){
		switch(choice){
			case 1:
				printf("Enter a number to enqueue: ");
				scanf("%d", &data);
				head = enqueue(head, data);
				printQueue(head);
				printf("\n Whato do you want to do now?");
				scanf("%d",&choice);
				break;
			case 2:
				i = dequeue(&head);
				printf("%d was dequeued\n", i);
				printQueue(head);
				printf("What do you wanna do now?\n");
				scanf("%d", &choice);
				break;
			default:
				freeQueue(head);
				return 0;
		}
	}
	return 0;
}
Node* enqueue(Node* head, int data){
	Node *current, *p;
	current = malloc(sizeof(Node));
	current->data = data;
	current->next = NULL;

	if(!head){
		return current;
	}
	p = head;
	while(p->next){
		p = p->next;
	}
		p->next = current;
	return head;
}
int dequeue( Node** frontPtr){
	Node *current;
	current = malloc(sizeof(Node));
	if( *frontPtr == NULL){
		printf("Error, Trying to display empty list\n");
		return 0;
	}
	// *frontPtr = (*(*frontPtr)).next;
	int quantity = (*(*frontPtr)).data;
	*frontPtr = (*(*frontPtr)).next;
	return quantity;
}
void freeQueue(Node* front){
	Node *temp;
	if(front == NULL){
		printf("Nothing to delete, list is empty");
		exit(-1);
	}
	while(front != NULL){
		temp = front;
		front = front->next;
		free(temp);
	}
}
void printQueue(Node* front){
	while(front != NULL){
		printf("%d->", front->data);
		front = front->next;
	}
	if(front == NULL){
		printf("NULL\n");
	}
}

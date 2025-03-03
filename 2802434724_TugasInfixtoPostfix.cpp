#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct linkednode{
	char form;
	int priority;
	struct linkednode *next;
	struct linkednode *prev;
}*head, *tail;

int prioritycheck(char operat){
	if(operat =='^'){
		return 3;
	}
	if(operat == '/' || operat == '*'){
		return 2;
	}
	if(operat == '+' || operat == '-'){
		return 1;
	}
	else{
	return 0;		
	}
}

void push_back(char letter){
	struct linkednode *node = (struct linkednode*) malloc(sizeof(struct linkednode));
	node->form = letter;
	node->priority = prioritycheck(letter);
	
	if(head == NULL){
		node->next = NULL;
		node->prev = NULL;
		head = tail = node;
	}
	else{
		node->next = NULL;
		node->prev = tail;
		tail->next = node;
		tail = node;
	}
}

char pop(){
	char hold;
	struct linkednode *del = tail;
	hold = del->form;
	
	if(tail == NULL){
		return '/0';
	}
	
	if(head == tail){
		head = tail = NULL;
	}
	else{
		tail = tail->prev;
		tail->next = NULL;
	}
	
	free(del);
	return hold;
}

int scan(char letter){
	return (letter == '/' || letter == '+' || letter == '-'|| letter == '*' || letter == '^');
}

void push_oper(char oper, char postfix[], int *j) {
    while (tail != NULL && tail->form != '(' && prioritycheck(oper) <= tail->priority) {
        postfix[(*j)++] = pop();
    }
    push_back(oper); 
}

int main(){
	int length, identifier, j = 0;
	char infix[10000];
	char postfix[1000];
	scanf("%s", infix);getchar();
	length = strlen(infix);
	
	for(int i = 0; i < length; i++){
		
		if(infix[i] == '('){
			push_back(infix[i]);
		}
		else if(infix[i] == ')'){
			while(tail != NULL && tail->form != '('){
				postfix[j] = pop();
				j++;
			}
			if(tail != NULL) pop();
		} 	
		else if(scan(infix[i])){
			push_oper(infix[i], postfix, &j);
		}
		else{
			postfix[j++] = infix[i];
		}
	}
	while (tail != NULL){
		postfix[j++] = pop();
	}
	
	printf("Postfix string = %s\n", postfix);
	printf("stack = ");
	while(tail != NULL){
		printf("%c", head->form);
		head = head->next;
	}
	
	return 0;
}

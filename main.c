#include <stdio.h>
#include "rb.h"

int main(){
	bootstrap();
	int opt = 0, value, valueReturn;
	node* rb = ward;
	while(1){
		scanf("%d", &opt);
		switch(opt){
			case 1:
				//inserir
				scanf("%d", &value);
				insert(&rb, value);
				break;		
			case 2://preorder
				preOrder(rb);
				printf("\n");
				break;
			case 3://remover
				scanf("%d", &value);
				removeNode(&rb, value);
			break;
			case 99:
				return 0;

		}
	}
}
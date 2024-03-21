#include <stdio.h>
#include <stdlib.h>

typeof struct queue_node{
   queue_node* next;
   int tel_num;
}q_node;

void q_init(q_node* queue){
   queue = (q_node*) malloc(sizeof(q_node));
   if(queue == NULL){
      printf("Queue initialization failed");
   }
}

main(){
   q_node* queue;
   q_init(queue);

}

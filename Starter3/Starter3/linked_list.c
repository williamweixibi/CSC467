#include "linked_list.h"

listNode_t *listHead ,*listVar,*listTrav;

void insert(char * name, int val, unsigned int scope, int type, int assign)
{
     listVar=(struct listNode *)malloc(sizeof (struct listNode));
     strcpy(listVar->name, name);
 	 listVar->type = type;
 	 listVar->scope = scope;
     if(assign==1){
    	 listVar->val = val;
     }

     if(listHead==NULL)
     {
         listHead=listVar;
         listHead->next=NULL;
     }
     else
     {
         listVar->next=listHead;
         listHead=listVar;
     }
}

void insert_at_begning(int value)
{
     listVar=(struct listNode *)malloc(sizeof (struct listNode));
     listVar->data=value;
     if(listHead==NULL)
     {
         listHead=listVar;
         listHead->next=NULL;
     }
     else
     {
         listVar->next=listHead;
         listHead=listVar;
     }
}

void insert_at_end(int value)
{
      struct listNode *temp;
      temp=listHead;
      listVar=(struct listNode *)malloc(sizeof (struct listNode));
      listVar->data=value;
      if(listHead==NULL)
      {
          listHead=listVar;
          listHead->next=NULL;
      }
      else
      {
          while(temp->next!=NULL)
          {
               temp=temp->next;
          }
          listVar->next=NULL;
          temp->next=listVar;
      }
}

void insert_at_middle(int value, int loc)
{
     struct listNode *listVar2,*temp;
     listVar=(struct listNode *)malloc(sizeof (struct listNode));
     listVar->data=value;
     temp=listHead;

     if(listHead==NULL)
     {
          listHead=listVar;
          listHead->next=NULL;
     }
     else
     {
          while(temp->data!=loc)
          {
                temp=temp->next;
          }
          listVar2=temp->next;
          temp->next=listVar;
          listVar->next=listVar2;
     }
}

int delete_from_middle(int value)
{
     struct listNode *temp,*listVar;
     temp=listHead;
     while(temp!=NULL)
     {
          if(temp->data == value)
          {
                if(temp==listHead)
                {
                     listHead=temp->next;
                     free(temp);
                     return 0;
                }
                else
                {
                     listVar->next=temp->next;
                     free(temp);
                     return 0;
                }
          }
          else
          {
               listVar=temp;
               temp=temp->next;
          }
     }
printf("data deleted from list is %d",value);
}

int delete_from_end()
{
     struct listNode *temp;
     temp=listHead;
     while(temp->next != NULL)
     {
          listVar=temp;
          temp=temp->next;
     }
     if(temp ==listHead)
     {
          listHead=temp->next;
          free(temp);
          return 0;
     }
     printf("data deleted from list is %d",temp->data);
     listVar->next=NULL;
     free(temp);
     return 0;
}

void display()
{
     listTrav=listHead;
     if(listTrav==NULL)
     {
          printf("\nList is Empty");
     }
     else
     {
          printf("\nElements in the List: ");
          while(listTrav!=NULL)
          {
               printf(" -> %d ",listTrav->data);
               listTrav=listTrav->next;
          }
      printf("\n");
      }
}


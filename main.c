#include<stdio.h>
#include<stdlib.h>

typedef struct Object
{
    unsigned int id;
    char title[25];
    unsigned int quantity;
    unsigned int price;
    
}Object;

typedef struct Item
{
    Object o;
    struct Item* next;
}Item;

#include"mainFD.h"

Item* AddItem(Item* r)
{
    Item* temp=malloc(sizeof(Item));
    if(temp==NULL)
    {
        printf("Wasn't able to allocate block. try again !");
        return NULL;
    }
    r->next=temp;
    InputItemInfo(&temp->o);
    temp->next=NULL;
    return temp;
}

void InputItemInfo(Object* o)
{
    printf("Enter the Item id : ");
    scanf("%u",&o->id);
    printf("Enter the Title for Item : (Max char 24 allow) ");
    getchar();
    gets(o->title);
    printf("Enter the Item in stock : ");
    scanf("%u",&o->quantity);
    printf("Enter the price for Item : ");
    scanf("%u",&o->price);
}

void PrintItemInfo(Object* o)
{
    printf("\n===Items Information===\n");
    InfoHelperUInt("Item Id Number",&o->id);
    InfoHelperChar("Item title",o->title);
    InfoHelperUInt("Item in Stock",&o->quantity);
    InfoHelperUInt("Item Price (In RS)",&o->price);
}

void InfoHelperChar(char* t, char* c)
{
    printf("%s : %s\n",t,c);
}

void InfoHelperUInt(char* t, unsigned int* n)
{
    printf("%s : %u\n",t,*n);
}

void PrintAllItemInfo(Item* r)
{
    Item* temp=r;
    while(temp!=NULL)
    {
        PrintItemInfo(&temp->o);
        temp=temp->next;
    }
}

void DisplayMenu()
{
    printf("\n--->Welcome to the Roshan Store <---\n");
    InfoHelperChar("1","Add Item in List");
    InfoHelperChar("2","Display Item in List");
    InfoHelperChar("3","Save Item in File");
    InfoHelperChar("4","Exit");
}

void CopyChar(char* s, char* d)
{
    int index=0;
    while(*(s+index)!='\0')
    {
        *(d+index)=*(s+index);
        index++;
    }
    *(d+index)=*(s+index);
}

int GetListSize(Item* r)
{
    Item* temp=r;
    int count=0;
    while(temp!=NULL)
    {
        count++;
        temp=temp->next;
    }
    return count;
}

Object* ListToArray(Item* rn, int* s)
{
    Item* tempPtr=rn;
    int lSize=GetListSize(tempPtr);
    *s=lSize;
    Object* temp=malloc(sizeof(Object)*lSize);
    for(int i=0;i<lSize;i++)
    {
        AssignListToArrayHelper(tempPtr,(temp+i));
        tempPtr=tempPtr->next;
    }
    return temp;
}

void AssignListToArrayHelper(Item* i, Object* o)
{
    Object* temp=&i->o;
    o->id=temp->id;
    CopyChar(temp->title,o->title);
    o->quantity=temp->quantity;
    o->price=temp->price;
}

FILE* OpenFileW(FILE* f,char* fn,char* m)
{
    f=fopen(fn,m);
    return f;
}

void SaveItemInFileB(Item* r)
{
    FILE* fptr;
    fptr=OpenFileW(fptr,"ItemList.bin","wb");
    Object* temp;
    int n=0;
    temp=ListToArray(r,&n);
    fwrite(temp,sizeof(Object),n,fptr);
    fclose(fptr);
}

void SaveItemInFileTXT(Item* r)
{
    FILE* fptr;
    fptr=OpenFileW(fptr,"ItemListtemp.txt","w");
    Object* temp;
    int n=0;
    temp=ListToArray(r,&n);
    for(int i=0;i<n;i++)
    {
        fprintf(fptr,"%u %s %u %u\n",temp->id,temp->title,temp->quantity,temp->price);
        PrintItemInfo(temp);
        temp++;
    }
    fclose(fptr);
}

int main()
{
    Item Root,*itemPointer,*ArrHolder;

    int choice;

    itemPointer=&Root;

    while(1)
    {
    DisplayMenu();
    scanf("%d",&choice);

    // printf("The entered choice was : %d ",choice);

        switch(choice)
        {
            case 1:
            itemPointer=AddItem(itemPointer);
            break;
            case 2:
            PrintAllItemInfo(Root.next);
            break;
            case 3:
            SaveItemInFileB(Root.next);
            SaveItemInFileTXT(Root.next);
            break;
            default:
            printf("Wrong choice ! ");
            break;
        }
        if(choice==4)
        {
            break;
        }

    }


    return 0;
}
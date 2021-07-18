#include <stdio.h>
#include <stdlib.h>

struct node
{
    char value;
    int x;
    int y;
    struct node* next;
};
struct food
{
    char value;
    int x;
    int y;
};

struct node* createSnake(char a[20][20],struct node* head)
{
    int i;
    for(i=0;i<4;i++)
    {
     struct node* temp=(struct node*)malloc(sizeof(struct node));
        if(head==NULL)
        {
            temp->value='A';
            temp->x=3;
            temp->y=4;
            temp->next=NULL;
            head=temp;
        }
        else
        {
            struct node* temp1=head;
            while(temp1->next!=NULL)
            temp1=temp1->next;
            temp1->next=temp;

            temp->value='#';
            temp->x=temp1->x+1;
            temp->y=temp1->y;
            temp->next=NULL;
        }
    }
    return head;
}

void printSnake(char a[20][20],struct node* head)
{
    struct node* temp=head;
    while(temp!=NULL)
    {
        a[temp->x][temp->y]=temp->value;
        temp=temp->next;
    }
}
void printMatrix(char a[20][20]){
    int i,j;
       for(i=0;i<20;i++)
       {
           for(j=0;j<20;j++)
           {
               if(i==19)
               {
                   a[i][j]='$';
               }
               else if(j==19)
               {
                    a[i][j]='$';
               }
               printf("%c",a[i][j]);
           }
           printf("\n");
       }

}
struct food createFood(char a[20][20],struct node* head)
{
    int i,j,flag=1;
    struct food fhead;
    fhead.x=rand()%(20-2)+1;
    fhead.y=rand()%(20-2)+1;
    fhead.value='@';
    while (head->next!=NULL)
    {
        if(head->x==fhead.x&&head->y==fhead.y)
        {
        fhead.x=rand()%(20-2)+1;
        fhead.y=rand()%(20-2)+1;
        }
            head=head->next;
    }
    return fhead;

}
void printFood(char a[20][20],struct food fhead){
    a[fhead.x][fhead.y]=fhead.value;
}
void moveOneStep(struct node* ptr,int m, int n)
    {
        int i=ptr->x;
        int j=ptr->y;
        ptr->x=m;
        ptr->y=n;
        if(ptr->next!=NULL)
        moveOneStep(ptr->next,i,j);

    }
struct food eatFood(char a[20][20],struct node*head,struct food fhead)
{
    if(head->x==fhead.x&&head->y==fhead.y)
    {
        fhead=createFood(a,head);
        increaseLength(head);
        printFood(a,fhead);
        return fhead;
    }
    else return fhead;
}
int calculatescore(int progress,struct node*head,struct food fhead)
{
    if(head->x==fhead.x&&head->y==fhead.y)
    progress= progress+10;
    return progress;
}

void moveSnake(char a[20][20],struct node*head,struct food fhead,char v,int progress)
{
    int i,j;
    char ch;
    ch=getch();
    printf("Enter 'X' to exit");

    if(ch=='s'&&v=='w'||ch=='a'&&v=='d'||ch=='w'&&v=='s'||ch=='d'&&v=='a')
        moveSnake(a,head,fhead,v,progress);
     else if(ch=='x'||ch=='X')
    {
        store(head,progress);
        exit(1);
    }
    else{
    switch(ch)
    {
    case 'w':
        moveOneStep(head->next,head->x,head->y);
        head->x=head->x-1;
        if(head->x==0)
        {
            head->x=19;
        }
    system("cls");
        break;
    case 'd':
       moveOneStep(head->next,head->x,head->y);
       head->y=head->y+1;
       if(head->y==19)
       {
           head->y=0;
       }
       system("cls");
       break;
    case 's':
       moveOneStep(head->next,head->x,head->y);
       head->x=head->x+1;
       if(head->x==19)
       {
           head->x=0;
       }
        system("cls");
       break;
    case 'a':
        moveOneStep(head->next,head->x,head->y);
        head->y=head->y-1;
        if(head->y==0)
        {
            head->y=19;
        }
        system("cls");
        break;
    default:
        moveSnake(a,head,fhead,v,progress);
        break;

    }
    printSnake(a,head);
    printMatrix(a);
    progress=calculatescore(progress,head,fhead);
    printf("\nScore=%d\n",progress);
    for(i=0;i<20;i++)
       {
           for(j=0;j<20;j++)
           {
               a[i][j]=' ';
           }
       }
    printFood(a,fhead);
   fhead = eatFood(a,head,fhead);
   int p=cut(a,head,fhead);
   if (p==1)
   {
       system("cls");
       FILE *fptr;
       fptr=fopen("F:\\Snak.txt","w");
       printf("Game over");
   }
   else{
    moveSnake(a,head,fhead,ch,progress);
   }
    }
}
int cut(char a[20][20],struct node*head,struct food fhead)
{
    int flag=0;
  struct node*  temp1=head;
   struct node* temp=temp1->next;
   while(temp!=NULL){
    if(temp1->x==temp->x&&temp1->y==temp->y)
    {
       flag=1;
       break;
    }
    else
    {
        temp=temp->next;
    }
}
if(flag==1)
{
    return 1;
}
else
{
    return 0;
}
}

void increaseLength(struct node* head)
{
    struct node *temp=head;
    struct node* tail=(struct node*)malloc(sizeof(struct node));
    tail->value='#';
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    //printf(tail->next);
    tail->next=temp->next;
   // printf("After increasing length:");
   // printf(tail->next);
    tail->x=temp->x;
    tail->y=temp->y;

    if(temp->next==NULL)
    {
        temp->next=tail;
    }
}
void store(struct node *head,int progress)
{
    struct node *temp=head;
     FILE *fptr;
    fptr=fopen("F:\\Snak.txt","w");
    while(temp!=NULL){
    int x=temp->x;
    int y=temp->y;
    char c=temp->value;
    fprintf(fptr,"%d %d %c\n",x,y,c);
    temp=temp->next;
    }
    fprintf(fptr,"%d %d %c",progress,0,'s');
    fclose(fptr);
}
void getFromFile(char a[20][20],struct node* head,int progress)
{
    struct node* temp2;
    struct food fhead;
    int x;
    int y;
    char c;
    FILE *fptr;
    fptr=fopen("F:\\Snak.txt","r");
    int count=0;
    while(fscanf(fptr,"%d %d %c\n",&x,&y,&c)!=EOF)
    {
        if(c=='s')
        {
            progress=x;
            break;
        }
        else
        {
        struct node* temp=(struct node*)malloc(sizeof(struct node));
        temp->x=x;
        temp->y=y;
        temp->value=c;
        temp->next=NULL;
        if(count==0)
        {
            head=temp;
            count++;
            temp2=temp;
        }
        else
        {
            temp2->next=temp;
            temp2=temp;
        }
        }
    }
    PrintSavedSnake(a,head, fhead);
    fhead=createFood(a,head);
    printFood(a,fhead);
    printSnake(a,head);

    printf("\nScore=%d\n",progress);
    moveSnake(a,head,fhead,'w',progress);
}
void PrintSavedSnake(char a[20][20],struct node* head,struct food fhead)
{
    struct node* temp=head;
    int i,j;
    for(i=0;i<20;i++)
            {
                for(j=0;j<20;j++)
                    {
                        a[i][j]=' ';
                    }
            }

    while(temp->next!=NULL){
    a[temp->x][temp->y]=temp->value;
    temp=temp->next;
    }
    printMatrix(a);
}

int main()
{
    char ch;
    int i,j,progress=0;
    char a[20][20];
    struct node* head;
    struct food fhead;
    head=NULL;
    FILE *in_file  = fopen("F:\\Snak.txt","r"); // read only
    fseek(in_file, 0, SEEK_END);
    int size;
    printf("For New Game Press 'N'\nTo Load Game Press 'L'\n");
    scanf("%c",&ch);
    if(ch=='N'||ch=='n')
    {
        size=0;
    }
    else if(ch=='L'||ch=='l')
    {
        size=ftell(in_file);
    }
    else
    {
       printf("Invalid Input");
       exit(1);
    }
    if (size==0)
    {
        for(i=0;i<20;i++)
            {
                for(j=0;j<20;j++)
                    {
                        a[i][j]=' ';
                    }
            }
        head = createSnake(a,head);
        fhead=createFood(a,head);
        printFood(a,fhead);
        printSnake(a,head);
        moveSnake(a,head,fhead,'w',progress);
    }
    else getFromFile(a,head,progress);
    return 0;
}

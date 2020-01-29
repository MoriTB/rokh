#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <ctype.h>
#define max 5
#define maxx 100
struct shift_cube
{
    int x,y,type,capacity,activate;
};
struct shift_cube backend[10][10];

struct cells
{
    char name[max];
    int x ,y,energy;
};
struct node
{
    struct cells cell;
    struct node *next;
};

void name_generator(char *name,int length);
int location_generation(int high_max);
struct node * create_node(int maximation);
void add_end(struct node *list, struct node *new_nodes);
void visual_creator(int blocks_number,char visual_map[blocks_number+2][blocks_number],int original_blocks_number);
void print(int blocks_number,char visual_map[blocks_number+2][blocks_number]);
void add_data_file(int blocks_number,char visual_map[blocks_number+2][blocks_number],int real_blocks_number,char *inname);
void add_cells(int cell_number,int blocks_number,char visual_map[blocks_number+2][blocks_number],struct node *player,int original_block_number);
void move_north(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number]);
struct shift_cube backend[10][10];
int main()
{
  srand(time(NULL));
  int choice;
  int cells_number;
  char name[maxx];
  while(1)
    {
      printf("[1]load\n");
      printf("[2]single player\n");
      printf("[3]multiplayer\n");
      printf("[4]exit\n");
      scanf("%d",&choice);
      if (choice==2)
         {
           printf("so whats the address of the main blank file \n");
           scanf("%s",name);
           printf("how many cell you got boi?\n");
           scanf("%d",&cells_number);
           break;
         }


    }
  int i,j;
    int blocks_number;
    if(choice==2)
   { 
     int choice_second;
     struct node *current;
     struct node *player1;
     FILE *fstr;
    fstr=fopen(name,"rb");
    if (fstr==NULL)
      {
        printf("the address you gave me wasnt right bud !");
        return -1;
      }
    fread(&blocks_number,sizeof(int),1,fstr);
    int original_block_number;
    original_block_number=blocks_number;
      blocks_number*=4;
    blocks_number++;
    char visual_map[blocks_number+2][blocks_number];
    visual_creator(blocks_number,visual_map,original_block_number);
    add_data_file(blocks_number,visual_map,original_block_number,name);
    add_cells(cells_number,blocks_number,visual_map,player1,original_block_number);
    print(blocks_number,visual_map);
    printf("which sell you want to move my lord ?\n");
    int counter;
    for(current=player1;current==NULL;current=current->next)
    {
      counter++;
      printf("[%d]%s (%d,%d) wgot %d\n",counter,current->cell.name,current->cell.x,current->cell.y,current->cell.energy);

    }
    scanf("%d",&choice_second);
    current=NULL;

    

   }
}
void name_generator(char *name,int length)
{
     char charset[] ="abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int index;
    while (length-- > 0) {
          index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        *name++ = charset[index];
    }
    *name = '\0';
}
int location_generation(int high_max)
{
    int location;
    location=(rand()%(high_max));
    return location;
}
struct node * create_node(int maximation)
{
 struct node * nn;
 nn = (struct node *)malloc(sizeof(struct node));
 name_generator(nn->cell.name,max);
 while(1)
 {
   nn->cell.x=location_generation(maximation);
  nn->cell.y=location_generation(maximation);
  if ((backend[nn->cell.x][nn->cell.y].activate==0)&&(backend[nn->cell.x][nn->cell.y].type!=3))
    break;
 }
 backend[nn->cell.x][nn->cell.y].activate=1;
 nn->next=NULL;
 return nn;
}
void add_end(struct node *list, struct node *new_nodes)
{
  struct node *current;
  for(current=list;current->next!=NULL;current=current->next);
  current->next=new_nodes;
  new_nodes->next=NULL;
}
void visual_creator(int blocks_number,char visual_map[blocks_number+2][blocks_number],int original_block_number)
{
  int i=0 ,j=0;
    
    bool check_true_false=0;
    int counter2=0;
    int counter=0;
      for (i = 0; i <blocks_number; i++)
       { for (j = 0; j <blocks_number; j++)
        {
          if((i%4==2)&&(j%4==0))
            counter2++;
         if ((j%4==0)&&(i%4==0))
          counter++;
          if ((i%4==0)&&(j%4==0))
            visual_map[i][j]='z';
          else if ((i%4==0)&&(counter%2!=0)&&(j%4!=0))
            visual_map[i][j]='z';
          else if((i%4==0)&&(counter%2==0)&&(j%4!=0))
            visual_map[i][j]=' ';
           else if ((i%4==1)&&(j%4==0))
           {
            visual_map[i][j]='z';
           }
          else if ((i%4==1)&&(j%4!=0))
            {
              visual_map[i][j]=' ';
            }
          else if ((i%4==2)&&(j%4==0))
          {
            visual_map[i][j]='z';
          }
          else if ((i%4==2)&&(counter2%2==0)&&(j%4!=0))
          {
            visual_map[i][j]='z';
          }
          else if ((i%4==2)&&(counter2%2!=0)&&(j%4!=0))
          {
            visual_map[i][j]=' ';
          }
          else if ((i%4==3)&&((j%4==0)))
           {
            visual_map[i][j]='z';
           }
          else if ((i%4==3)&&(j%4!=0))
            {
              visual_map[i][j]=' ';
            }
        }
        counter=0;
        counter2=0;
       } 
       i=blocks_number;
      for(j=0;j<blocks_number;j++)
      {
        if ((j%4!=0)||(j==0))
        visual_map[i][j]=' ';
        else
        {
          visual_map[i][j]='z';
        }
      }
      counter=0;
      for(j=0;j<blocks_number;j++)
      {
        if (j%4==0)
        {
          counter++;
        }
        if((j%4==0)&&(j!=0))
          visual_map[blocks_number+1][j]='z';
        else if(j==0)
          visual_map[blocks_number+1][j]=' ';
        else if((j%4!=0)&&(counter%2!=0))
        {
          visual_map[blocks_number+1][j]=' ';
        }
        else
        {
          visual_map[blocks_number+1][j]='z';
        }
        if (original_block_number%2==0)
          {
            visual_map[0][blocks_number-1]=' ';
            visual_map[1][blocks_number-1]=' ';
          }
        else
        {
          visual_map[blocks_number][blocks_number-1]=' ';
          visual_map[blocks_number+1][blocks_number-1]=' ';
        }
        
      }
}
void print(int blocks_number,char visual_map[blocks_number+2][blocks_number])
{
  int i,j;
  for(i=0;i<=blocks_number+1;i++)
  { 
      {
       for(j=0;j<blocks_number;j++)
       {
         if (visual_map[i][j] == 'z')
         {
           printf(" ❑ ");
           continue;
         }
         if (visual_map[i][j]=='V')
         {
           printf(" ☢︎ ");
           continue;
         }
         if (visual_map[i][j]=='e')
          {
            printf(" 🔋");
            continue;
          } 
          
        printf(" %c ",visual_map[i][j]);
       }
      } 
    printf("\n");
  }
}
void add_data_file(int blocks_number,char visual_map[blocks_number+2][blocks_number],int original_block_number,char *inname)
{
    int i,j;
    int n;
    char what;
    int temporary_array[10][10];
    FILE *fop;
    fop=fopen(inname,"rb");
    if (fop==NULL)
        {
            printf("the file havent been found yet \n");
        }
        //chra ye add bishtar mikhune ? on az koja miad ? baraye chi vojod dare?
    fread(&n,sizeof(int),1,fop);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
             fread(&what,sizeof(unsigned char),1,fop);
             temporary_array[i][j]=what-'0';
        }
    }
  int stable_y=2;
       int stable_x;
  for(i=0;i<original_block_number;i++)
    {
        if(i%2==0)
             stable_x=blocks_number+1;
        else
        {
            stable_x=blocks_number+3;
        }
        
        for(j=0;j<original_block_number;j++)
        {
            if (i%2==0)
                {
                    stable_x-=4;
                    backend[i][j].x=stable_x;
                    backend[i][j].y=stable_y;
                    backend[i][j].type=temporary_array[i][j];
                    if (backend[i][j].type==1)
                        backend[i][j].capacity=100;
                    else
                    {
                        backend[i][j].capacity=0;
                    }
                    
                }
            else
            {
                stable_x-=4;
                backend[i][j].x=stable_x;
                    backend[i][j].y=stable_y;
                    backend[i][j].type=temporary_array[i][j];
                    if (backend[i][j].type==1)
                        backend[i][j].capacity=100;
                    else
                    {
                        backend[i][j].capacity=0;
                    }
            }
            
        }

        stable_y+=4;
    }
    //tasire shklk ha va rbtashon ba backend
    for(i=0;i<original_block_number;i++)
    {
        for(j=0;j<original_block_number;j++)
        {
            if(backend[i][j].type==1)
            {
                visual_map[(backend[i][j]).x+1][(backend[i][j].y)-1]='e';
            }
            else  if(backend[i][j].type==2)
                visual_map[(backend[i][j]).x+1][(backend[i][j].y)-1]='m';
            else  if(backend[i][j].type==3)
             visual_map[(backend[i][j]).x+1][(backend[i][j].y)-1]='f';
            else  if(backend[i][j].type==4)
             visual_map[(backend[i][j]).x+1][(backend[i][j].y)-1]='n';
        }
    }
    fclose(fop);
}
void add_cells(int cell_number,int blocks_number,char visual_map[blocks_number+2][blocks_number],struct node *player,int original_block_number)
{
  int i;
struct node *current_out;
player=create_node(original_block_number);

for(i=1;i<cell_number;i++)
{
    add_end(player,create_node(original_block_number));
}
for(current_out=player;current_out!=NULL;current_out=current_out->next)
   {
    visual_map[backend[current_out->cell.x][current_out->cell.y].x][backend[current_out->cell.x][current_out->cell.y].y]='V';
   } 
}



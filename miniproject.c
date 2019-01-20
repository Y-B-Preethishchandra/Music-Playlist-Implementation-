#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>


struct node 
{
	char addr[500];
	char name[100];
	int song_no;	
	char artist[50];
	int year;
	char movie[50];
	struct node * prev;
	struct node * next;
};


const int z=500;

void insert_rear( struct node **, char*,int,char*,char*,char*);//insert node to the rear of the linked list
void play(struct node **);//playing the song
void play_next(struct node **);//playing the next song
void play_prev(struct node **);//playing the previous song
int readfile(struct node **);//reading from the file
void initialize(struct node **);//moving the pointer to point to the first node
int * shuffle(int ,int ,int*);//shuffling the songs in the linked list
void shuffle_print_pos(struct node *,int);//playing the shuffled songs
void swap(struct node **, int, int );//function to swap data in the nodes
void sort_name(struct node **, int, int);//sort according to the name quick sort
void sort_year(struct node **, int, int);//sort according to the year quick sort
void displayaddr(struct node *);//display addresses of the songs
void displayname(struct node *);//display the names of all songs
void search(struct node **);//linear search of songs
char* to_lower(char *, char *);//convert string to lower case
void add_song(struct node **);//adding song to linked list and file
void delete_song(struct node **);//delete song from the linked list
void intro();//display intro
void playing();//display playing pattern



int no=0;



int main()
{	
	intro();//intro function call
	printf("\n                           Project By:\n                           Preethishchandra B Yadagere\n                           Preetham Upadhya\n                           Puneeth Karkera\n");
	int ch;
	int i=1;
	int j=0;
	int k=0;
	int l;
	struct node *first= NULL;//initializing the structure variable
	l=readfile(&first);//reading the file
	if(l==-1)
	{
		printf("File Not Found");
		return 0;
	}
	initialize(&first);//moving the pointer to first position
	int a[no];
	while(i)
	{	
		printf("\n_________________________\n0.Display playlist       |\n1.Play Current           |\n2.Play Next              |\n3. Play Previous         |\n4.Shuffle                |\n5.Shuffle Play           |\n6.Shuffle Play next      |\n7.Shuffle Play prev      |\n8.Sort Name              |\n9.Sort Yearwise          |\n10.Search                |\n11.Add Song              |\n12.Delete Song           |\n13.Display Addresses     |\n14.Exit                  |\n--------------------------\n");
		scanf("%d",&ch);
		
		switch(ch)
		{ 
			case 0: displayname(first);
			        break;
			case 1: play(&first);
				printf("                            ");
				playing();
			        break;
			case 2: play_next(&first);
				printf("                            ");
				playing();
			        break;
			case 3: play_prev(&first);
				printf("                            ");
				playing();
			        break;
			case 4: shuffle(0,no,a);
				k=1;
			        break;
			case 5: if(k==1)
			        {	
				        shuffle_print_pos(first,a[j]);
					printf("                           ");
					playing();
				        break;
			        }
			        else
			        {
					 printf("Not Shuffled\n");
				         break;
			        }
			case 6: if(k==1)
			        {	 
				         j++;
				         if(j==no)
					         j=0;
				         shuffle_print_pos(first,a[j]);
					
					 printf("                           ");
					 playing();
				         break;
			        }
			        else
			        {
					 printf("Not Shuffled\n");
			        	 break;
			        }
			case 7: if(k==1)
			        {
				        j--;
				        if(j==-1)
				 	        j=no-1;
				        shuffle_print_pos(first,a[j]);
					printf("                           ");
					playing();
				        break;
			        }
			        else
			        {
				 	 printf("Not Shuffled\n");
				         break;
			        }
			
			case 8: sort_name(&first,0,no-1);
			        break;
			case 9: sort_year(&first,0,no);
				break;
			case 10:search(&first);
				printf("                            ");
				playing();
			        break;
			case 11:add_song(&first);
				break;	
			case 12:delete_song(&first);
				break;
			case 13:displayaddr(first);
				break;
			default:printf("                           ");
				printf("Thank you\n                           Project By:\n                           Preethishchandra B Yadagere\n                           Preetham Upadhya\n                           Puneeth Karkera\n");
				exit(0);
		}
	}
	return 0;

}

void insert_rear( struct node **p, char* artist,int year,char* movie,char* name,char* address)
{		
	struct node *temp;//node variable
	temp = (struct node*)malloc(sizeof(struct node));//allocate memory
	temp->song_no=no;//copying details
	no++;//incrementing the no of songs
	strcpy(temp->artist,artist);
	strcpy(temp->name,name);
	strcpy(temp->movie,movie);
	strcpy(temp->addr,address);
	temp->year=year;
	
	temp -> next=temp->prev = temp;
	if (*p == NULL)//empty linked list
	{
			*p = temp;
	}
	else 
	{
   		temp->next=(*p)->next;//linking the node
		(*p)->next->prev=temp;
 		(*p)->next=temp;
		temp->prev=*p;
		*p=temp;	//initial pointer points to the last node	
	}
}

int readfile(struct node **p)
{
	FILE *fp;
	char s[300],artist[50],movie[30],name[50],add[500];
	const char st[2] = ",";
	int year;
	fp=fopen("Music_Playlist.txt","r");//opening file
	if (fp==NULL)
		return -1;
	while((fgets(s, 300, fp))!=NULL)
	{
		char *token;
		token=strtok(s,st);//separating the values separated by commas
		strcpy(artist,token);
		token = strtok(NULL, st);
		year=atoi(token);
		token = strtok(NULL, st);
		strcpy(movie,token);
		token = strtok(NULL, st);
		strcpy(name,token);
		token = strtok(NULL, st);
		strcpy(add,token);
		insert_rear(p,artist,year,movie,name,add);//adding to the linked list
	}
	fclose(fp);//cloing the file
}

void play(struct node **p)
{	
	printf("                                 PLAYING\n");
	printf("                           _________________________\n");
	printf("                          |Song:   %s\n",(*p)->name);
	printf("                          |Movie:  %s\n",(*p)->movie);
	printf("                          |Artist: %s\n",(*p)->artist);
	printf("                          |Year:   %d\n",(*p)->year);	
	
}

void play_next(struct node **p)
{
	(*p)=(*p)->next;
	printf("                                 PLAYING\n");
	printf("                           _________________________\n");
	printf("                          |Song:   %s\n",(*p)->name);
	printf("                          |Movie:  %s\n",(*p)->movie);
	printf("                          |Artist: %s\n",(*p)->artist);
	printf("                          |Year:   %d\n",(*p)->year);	
	
}

void play_prev(struct node **p)
{
	(*p)=(*p)->prev;
	printf("                                 PLAYING\n");
	printf("                           _________________________\n");
	printf("                          |Song:   %s\n",(*p)->name);
	printf("                          |Movie:  %s\n",(*p)->movie);
	printf("                          |Artist: %s\n",(*p)->artist);
	printf("                          |Year:   %d\n",(*p)->year);	
	
}

void initialize(struct node **p)
{
	(*p)=(*p)->next;//initializing the initial pointer to point to the first node
}


int * shuffle(int min,int x, int * array)
{
	static int j=0;
	int i;
	for (i = min; i < x; i++)
	{     
		array[i] = i;//creating the array having first n integers
	}
	for (i = min; i <x; i++)
	{    
		int temp = array[i];
		int randomIndex = (rand()+j)% x;//choosing random number as array index
		array[i]= array[randomIndex];//swapping the values depending on the random index
		array[randomIndex] = temp;
	}
	j++;
	return array;
}

void shuffle_print_pos(struct node * p,int pos)
{
	if(pos<no)
	{
		struct node *q;
		
		q=p;
		int i=0;
		while((q->next!=p)&&(i<pos))//locating the node using the position
		{
		    i++;
		    q=q->next;
		}
		
		
		play(&q);	
	}
	else
	{
		return;
	}
}

void sort_name(struct node **p, int low, int high)//using quick sort to sort the nodes according to the name
{
	int i, j;
	char newse[100];
	char newda[100];
	int k;
	struct node *q,*r;
	if(low >= high)
		return;
	j = low;
	for(i = low + 1; i <= high; i++)
	{
		
		q=r=*p;
		k=0;
		while((q->next!=*p)&&(k<i))//going to the position
		{
		    k++;
		    q=q->next;
		}
		k=0;
		while((r->next!=*p)&&(k<low))//going to the position
		{
		    k++;
		    r=r->next;
		}
		if(strcmp(q->name,r->name )< 0)
			swap(p, ++j, i);
	}
	swap(p, low, j);
	sort_name(p, low, j - 1);
	sort_name(p, j + 1, high);

}

void sort_year(struct node **p, int low, int high)//using quick sort to sort the nodes according to the year
{
	int i, j;
	struct node *q,*r;
	char newse[100];
	char newda[100];
	if(low >= high)
		return;
	j = low;
	for(i = low + 1; i <= high; i++)
	{
		
		q=r=*p;
		int k=0;
		while((q->next!=*p)&&(k<i))
		{
		    k++;
		    q=q->next;
		}
		while((r->next!=*p)&&(k<low))
		{
		    k++;
		    r=r->next;
		}
		if((q->next==*p)&&(k==i)&&(q->year < r->year))
			swap(p,++j,i);
	}
	swap(p, low, j);
	sort_name(p, low, j - 1);
	sort_name(p, j + 1, high);
}
void swap(struct node **p, int j, int i)//function used in the quick sort to swap the values
{
	char tempname[100],tempadd[100],tempart[50],tempmov[50];
	int tempyr;
	struct node *q,*r;
	q=*p;
	int k=0;
	while((q->next!=*p)&&(k<i))
	{
	    k++;
	    q=q->next;
	}
	r=*p;
	k=0;
	while((r->next!=*p)&&(k<j))
	{
	    k++;
	    r=r->next;
	}
	strcpy(tempname,q->name);
	strcpy(tempadd,q->addr);
	strcpy(tempmov,q->movie);
	strcpy(tempart,q->artist);
	tempyr=q->year;
	strcpy(q->name,r->name);
	strcpy(q->addr,r->addr);
	strcpy(q->movie,r->movie);
	strcpy(q->artist,r->artist);
	q->year=r->year;
	strcpy(r->name,tempname);
	strcpy(r->addr,tempadd);
	strcpy(r->artist,tempart);
	strcpy(r->movie,tempmov);
	r->year=tempyr;
	
}

void displayaddr(struct node *p)//function to display the song address
 {
	struct node *q;
	q=p;
	printf("\n");
	if(q==NULL)
		return;
	while(q->next!=p)
	{
		printf("%s\n",q->addr);
		q=q->next;
	} 
	printf("%s\n",q->addr);
	printf("\n");
}

void displayname(struct node *p)//function to display the song name
 {
	struct node *q;
	q=p;
	printf("\n");
	if(q==NULL)
		return;
	while(q->next!=p)
	{
		printf("%s\n",q->name);
		q=q->next;
	} 
	printf("%s\n",q->name);
	printf("\n");
}

void search(struct node **p)//linear search to search for song in the linked list
{
	char search[100];
	char newse[100];
	char newda[100];
	printf("\nEnter the song name:\n");
	scanf("%s",search);
	int i=strlen(search);
	struct node *q;
	q=*p;
	while((q->next!=(*p))&&((strncmp(to_lower(search,newse),to_lower(q->name,newda),i)!=0)))
	{
		q=q->next;
	}
	
	if(q->next==*p)
	{
		if(strncmp(newse,newda,i)!=0)
			play(&q);
		else{
		printf("\nNo Song Found\n");
		return;}
	}
	else play(&q);
}	

char* to_lower(char *string,char *new)//function used to convert characters in the string to lower case
{	
	int i=0;
	strcpy(new,string);   
	while(new[i]!='\0')
	{    
		if (new[i]>='A'&&new[i]<='Z') 
		{
			new[i] = new[i] + 32;
		}
		i++;    
	}
	return new;
}
void add_song(struct node **p)//function to add song to the linked list and the file
{
	char address[200],name[50],artist[50],movie[50];
	int year;
	printf("\nEnter the song address:\n");
	scanf("%s",address);
	printf("\nEnter the song name:\n");
	scanf("%s",name);
	printf("\nEnter the year:\n");
	scanf("%d",&year);
	printf("\nEnter the artist name:\n");
	scanf("%s",artist);
	printf("\nEnter the movie name:\n");
	scanf("%s",movie);
	FILE *fp;
	fp=fopen("Music_Playlist.txt","a");
	fputs(artist, fp);
	fputc(',',fp);
	fprintf(fp,"%d,%s,%s,%s",year,movie,name,address);//adding song to the file
	fprintf(fp,"\n");
	insert_rear(p,artist,year,movie,name,address);//adding song to the linked list
	printf("Successfully Added the song %s\n",name);
	fclose(fp);
}
void delete_song(struct node **p)//function to delete song from the linked list only
{
	char search[100];
	char newse[100];
	char newda[100];
	printf("\nEnter the song name:\n");
	scanf("%s",search);
	int i=strlen(search);
	struct node *q,*prev;
	prev=NULL;
	q=*p;
	while((q->next!=*p)&&((strncmp(to_lower(search,newse),to_lower(q->name,newda),i)!=0)))//find the song
	{
		prev=q;
		q=q->next;
		
	}
	
	if(q->next==*p)
	{
		if(strncmp(newse,newda,i)!=0)
		{q->prev->next=q->next;
	q->next->prev=q->prev;
	*p=q->next;
	free(q);}//deleting the song and linking the previous and next node
		else {
		printf("\nNo Song Found\n");
		return;}
	}
	else{
	q->prev->next=q->next;
	q->next->prev=q->prev;
	*p=q->next;
	free(q);}//deleting the song and linking the previous and next node
}


void intro()//function to print the intro pattern
{
	printf("             _______________      ________________      \n");
	printf("             ------------| |      ----------------      \n");
	printf("                         | |      | |          | |      \n");
	printf("                         | |      | |          | |      \n");
	printf("                         | |      | |          | |      \n");
	printf("                         | |      | |          | |      \n");
	printf("             ____________| |      | |__________| |      \n");
	printf("             ---------------      ----------------                 _______    ______    \n");
	printf("                         | |      | |           |\\    /| |      | |        | |   \n");
	printf("                         | |      | |           | \\  / | |      | |        | |   \n");
	printf("                         | |      | |           |  \\/  | |      | |______  | |   \n");
	printf("                         | |      | |           |      | |      |        | | |   \n");
	printf("             ____________| |      | |           |      | |      |        | | |   \n");
	printf("             ---------------      | |           |      | |______|  ______| | |______   \n");

}

void playing()///function to create playing pattern
{
	int i = 0,j,k=0;
	char *string=NULL;
	int x=1,y=0;
	string=(char *)malloc(sizeof(char)+2);
	string[x-1]='|';
	printf("%c",string[x-1]);
	usleep(500000);
	printf("\033[1D");
	while (i<2) 
	{
		fflush(stdout);
		string[x-1]='/';
		printf("%c",string[x-1]);
		usleep(500000);
		printf("\033[1D");
		fflush(stdout);
		string[x-1]='-';
		printf("%c",string[x-1]);
		usleep(500000);
		printf("\033[1D");
		fflush(stdout);
		string[x-1]='\\';
		printf("%c",string[x-1]);
		usleep(500000);
		printf("\033[1D");
		fflush(stdout);
		string[x-1]='*';
		printf("%c",'*');
		string[x]='|';
		string=realloc(string,sizeof(char)*(x+2));
		usleep(500000);
		x++;
		fflush(stdout);
		printf("%c",string[x-1]);
		printf("\033[1D");
		usleep(500000);
	
		i++;
	}
}


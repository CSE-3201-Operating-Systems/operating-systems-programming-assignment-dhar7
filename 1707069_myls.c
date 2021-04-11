#include <stdio.h>
#include <dirent.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>


//int years[100],months[100],days[100],hours[100],mins[100],secs[100];
char folders[100][40],stats[100][20],files[100][50],final[100][50];


void swap_folder(int k)
{
   char temp[50];
   strcpy(temp,final[k]);
   strcpy(final[k],final[k+1]);
   strcpy(final[k+1],temp);
   
   strcpy(temp,files[k]);
   strcpy(files[k],files[k+1]);
   strcpy(files[k+1],temp);
}


int listdir(const char *path) 
{
  struct dirent *entry;
  DIR *dp;

  dp = opendir(path);
  if (dp == NULL) 
  {
    perror("opendir");
    return -1;
  }

  int elements = 0;
  char name[20];
  while((entry = readdir(dp)))
  {
     if ( !(strcmp(entry->d_name,".."))) {}
     else if (!(strcmp(entry->d_name,"."))) {}
     else {strcpy(files[elements],entry->d_name);elements++;}
     
  } 
  for (int i=0;i<elements+2;i++)
  {
      //printf("%s\n",files[i]);
      if (files[i][0] == '.')
      { 
          for (int j = 1 ; j < (strlen(files[i]) - 0) ; j++) { final[i][j-1] = files[i][j];}
      }
      else { strcpy(final[i],files[i]); }
  } 
  //for (int i=0;i<29;i++) { printf("%s = %s\n",files[i],final[i]); }   
  for (int i=0;i<elements+2;i++)
  {  
     final[i][0] = tolower(final[i][0]);
  }
  //for (int i=0;i<29;i++) { printf("%c \n",final[i][0]); } 
  for (int i=0;i<elements+2;i++)
  {  
     for (int k=0;k<elements+1;k++)
     {  
           if(final[k][0] > final[k+1][0])
           {
               swap_folder(k);
           }
           else if(final[k][0] == final[k+1][0])
           {
             if(final[k][1] > final[k+1][1])
             {
                  swap_folder(k);
             }
             else if(final[k][1] == final[k+1][1])
             {
                if(final[k][2] > final[k+1][2])
                {
                  swap_folder(k);
                }
                else if(final[k][2] == final[k+1][2])
                {
                 if(final[k][3] > final[k+1][3])
                 {
                   swap_folder(k);
                 }
                 else if(final[k][3] == final[k+1][3])
                 {
                    if(final[k][4] > final[k+1][4])
                    {
                      swap_folder(k);
                    }
                    else if(final[k][4] == final[k+1][4])
                    {
                      if(final[k][5] > final[k+1][5])
                      {
                         swap_folder(k);
                      }
                    }
                }
                }
             }
           }
     }
  }printf(".\n");printf(".."); 
  for (int i=1;i<elements+2;i++) { printf("%s \n",files[i]); }  
  closedir(dp);
  return 0;
}

void processing(const char *name,int i)
{
    int year,month,day,hour,min,sec;
    
    char pre[] = "stat -c %y ";
    char post[] = " > ls";
    char folder[50];
    strcpy(folder,name);
    strcat(pre,folder);strcat(pre,post);
    if (!strcmp(pre,"stat -c %y mlss > ls")) system("stat -c %y myls > ls"); 
    else system(pre);

    FILE *ptr;
    ptr = fopen("ls","r");
    char stat[] = "";
    for (int i=0;i<19;i++)
    {
        //if (i==2 ||i==3 ||i==5 ||i==6 ||i==8 ||i==9 ||i==11 ||i==12 ||i==14 ||i==15 ||i==17 ||i==18 )
       //{
            char c = fgetc(ptr);
            strncat(stat,&c,1);
        //}
    }
    //printf("%s\n",stat);
    strcpy(folders[i],name);
    strcpy(stats[i],stat); 
    //year = (stat[2] - '0' )*10 + (stat[3] - '0'); years[i] = year;
    //month = (stat[5] - '0' )*10 + (stat[6] - '0'); months[i] = month;
    //day = (stat[8] - '0' )*10 + (stat[9] - '0'); days[i] = day;
    //hour = (stat[11] - '0' )*10 + (stat[12] - '0'); hours[i] = hour;
    //min = (stat[14] - '0' )*10 + (stat[15] - '0'); mins[i] = min;
    //sec = (stat[17] - '0' )*10 + (stat[18] - '0'); secs[i] = sec;
    //printf("%s = %d/%d/%d/  %d:%d:%d\n",name,year,month,day,hour,min,sec);
}

void swap(int i)
{
   char holder[21],carrier[41];
   strcpy(holder,stats[i+1]);
   strcpy(carrier,folders[i+1]);
   strcpy(stats[i+1],stats[i]);
   strcpy(folders[i+1],folders[i]);
   strcpy(stats[i],holder);
   strcpy(folders[i],carrier);
}

void sort_sec(int i)
{
    int sec = (stats[i][17] - '0')*10 + stats[i][18] - '0' ;
    int sec_next = (stats[i+1][17] - '0')*10 + stats[i+1][18] - '0' ;
    if (sec_next > sec)
    {
        swap(i);
    }
    //else if ( sec_next == sec)
    //{
    //    sort_sec(i);
    //}
    else if (sec_next < sec)
    {
        //no work , bcz already sorted
    } 

}


void sort_min(int i)
{
    int min = (stats[i][14] - '0')*10 + stats[i][15] - '0' ;
    int min_next = (stats[i+1][14] - '0')*10 + stats[i+1][15] - '0' ;
    if (min_next > min)
    {
        swap(i);
    }
    else if ( min_next == min)
    {
        sort_sec(i);
    }
    else if (min_next < min)
    {
        //no work , bcz already sorted
    } 

}

void sort_hour(int i)
{
    int hour = (stats[i][11] - '0')*10 + stats[i][12] - '0' ;
    int hour_next = (stats[i+1][11] - '0')*10 + stats[i+1][12] - '0' ;
    if (hour_next > hour)
    {
        swap(i);
    }
    else if ( hour_next == hour)
    {
        sort_min(i);
    }
    else if (hour_next < hour)
    {
        //no work , bcz already sorted
    } 

}

void sort_date(int i)
{
    int date = (stats[i][8] - '0')*10 + stats[i][9] - '0' ;
    int date_next = (stats[i+1][8] - '0')*10 + stats[i+1][9] - '0' ;
    if (date_next > date)
    {
        swap(i);
    }
    else if ( date_next == date)
    {
        sort_hour(i);
    }
    else if (date_next < date)
    {
        //no work , bcz already sorted
    } 

}

void sort_month(int i)
{
    int month = (stats[i][5] - '0')*10 + stats[i][6] - '0' ;
    int month_next = (stats[i+1][5] - '0')*10 + stats[i+1][6] - '0' ;
    if (month_next > month)
    {
        swap(i);
    }
    else if ( month_next == month)
    {
        sort_date(i);
    }
    else if (month_next < month)
    {
        //no work , bcz already sorted
    } 

}

void sort_year()
{
   for(int j=0;j<50;j++)
   {
       for (int i=0;i<50;i++)
       {
          int year = (stats[i][2] - '0')*10 + stats[i][3] - '0' ; 
          int year_next = (stats[i+1][2] - '0')*10 + stats[i+1][3] - '0';
          if (year_next > year)
          {
              swap(i);
          }
          else if ( year_next == year)
          {
              sort_month(i);
          }
          else if (year_next < year)
          {
              //no work, bcz already sorted
          } 
       }
   }    
}

int sort2(const char *path)
{
   int i=0;
   struct dirent *entry;
   DIR *dp;

   dp = opendir(path);
   if (dp == NULL) 
   {
     perror("opendir");
     return -1;
   }
   while((entry = readdir(dp)))
   {
     const char *name = entry->d_name;
     if (name[0] != '.')
     {
       processing(name,i);
       struct stat attrib;
       stat(name, &attrib);
       char date[10];
       strftime(date, 20, "%d-%m-%y", localtime(&(attrib.st_ctime)));
       //printf("The file %s was last modified at %s\n", name, date);
       i++;
       date[0] = 0; 
     }
   }
   for(int j=0 ; j<i ; j++)
   {
      //printf("%s = %s\n",folders[j],stats[j]);
   }
   //printf("........................................................................................................\n");
   sort_year();
   for(int j=0 ; j<i ; j++)
   {
      printf("%s \n",folders[j]);
   }
   
}

void fetch_info(const char *name,int i)
{
    
    char size[10],links[3],perm[15],permission[15],owner[10],group[10],mm[4],dd[4],hh[4],min[4];
    char month[20] ,date[5],*hour,*minute;
    char information[100];
    char pre[30] = "stat ";
    char post[30] = " > /home/dhar/toy/en/info";
    char folder[30] ;
    strcpy(folder,name);
    strcat(pre,folder);
    strcat(pre,post);
    if (!strcmp(pre,"stat -c %y mlss > ls")) system("stat -c %y myls > ls"); 
    else system(pre);

    FILE *ptr;
    ptr = fopen("/home/dhar/toy/en/info","r");
    char chunk[128];int line = 0;
    while (fgets(chunk , sizeof(chunk) , ptr)!= NULL)
    {
        if( line == 1 )
        {
            //size[0] = chunk[8];size[1] = chunk[9];size[2] = chunk[10];size[3] = chunk[11];printf("%s = %s  &&&&",name,size);
            for (int i = 0;i < 15 ; i++ )
            {
                if (chunk[i] == ':')
                {
                    size[0] = chunk[i+2];size[1] = chunk[i+3];size[2] = chunk[i+4];size[3] = chunk[i+5];//printf("%s = %s\n",name,size);
                    break;
                }
            }
        }
        else if(line == 2)
        {
             //links[0] = chunk[45]; printf("Links = %s  &&&&",links);
             links[0] = chunk[strlen(chunk)-3];links[1] = chunk[strlen(chunk)-2];//printf("%s = %s\n",name,links);
        }
        if(line == 3)
        {
            for(int i=0 ; i < 50 ; i++)
            {
                if (chunk[i] == '/' && (chunk[i+1] == 'd' || chunk[i+1] == '-'))
                {
                    for(int j=1;j<=10;j++)
                    {
                        perm[j-1] = chunk[i+j];
                    }
                }
            }//printf("%s\n",perm);
            group[0] = chunk[strlen(chunk)-6];group[1] = chunk[strlen(chunk)-5];group[2] = chunk[strlen(chunk)-4];group[3] = chunk[strlen(chunk)-3],group[4] = '\0';
            for(int i = (strlen(chunk) - 2) ; i>=0 ; i-- )
            {
                if (chunk[i] == 'G')
                {
                    int k =0;//printf("YESSSSSS\n");
                    for(k  ; k <= 9 ; k++ )
                    {
                        owner[k] = chunk[i-(9-k)];
                        if ( chunk[i-(8-k)] == ' ' ) break;
                    }
                    owner[k] = '\0';
                }
            }
            //printf("%s = %s = %c%c = %s = %s == %s\n",name,perm,links[0],links[1],size,group,owner);
        }
        if(line == 5)
        {
            for ( int i=0;i<60;i++ )
            {
                if ( i == 12)
                {
                    //mm[0] = chunk[i+1] ; mm[2] = chunk[i+2]; mm[3] = '\0';
                    dd[0] = chunk[i+4] ; dd[2] = chunk[i+5]; dd[3] = '\0';
                    hh[0] = chunk[i+7] ; hh[2] = chunk[i+8]; hh[3] = '\0';
                    min[0] = chunk[i+11] ; min[2] = chunk[i+10]; min[3] = '\0';
                    //printf("%s %s %s %s\n",mm,dd,hh,min);
                    if(chunk[i+2] == '3') strcpy(month,"March");
                    else if(chunk[i+2] == '4') strcpy(month,"April");
                    else if(chunk[i+2] == '5') strcpy(month,"May");
                    else if(chunk[i+2] == '6') strcpy(month,"June");
                    else if(chunk[i+2] == '7') strcpy(month,"July");
                    else if(chunk[i+2] == '8') strcpy(month,"August");
                    else if(chunk[i+2] == '9') strcpy(month,"September");
                    else if(chunk[i+2] == '0') strcpy(month,"October");
                    else if( (chunk[i+2] == '2') && (chunk[i+1] == '0') ) strcpy(month,"February");
                    else if( (chunk[i+2] == '2') && (chunk[i+1] == '1') ) strcpy(month,"December");
                    else if( (chunk[i+2] == '1') && (chunk[i+1] == '0') ) strcpy(month,"January");
                    else if( (chunk[i+2] == '1') && (chunk[i+1] == '1') ) strcpy(month,"November");
                    strcpy(date,dd);
                    //char cmnd[30] = "stat -c %A ";
                    //strcpy(cmnd,name);
                    //system(cmnd);
                    //printf("%s/%c%c  %c%c:%c%c \n",month,chunk[i+4],chunk[i+5],chunk[i+7],chunk[i+8],chunk[i+10],chunk[i+11]);
                    printf("%s %c%c %s %s %s %s  %c%c  %c%c:%c%c  %s\n",perm,links[0],links[1],group,owner,size,month,chunk[i+4],chunk[i+5],chunk[i+7],chunk[i+8],chunk[i+10],chunk[i+11],name);
                }
            }
        }
        line ++ ; 
    } 
    strcat(information,perm) ; strcat(information,"  ");
    strcat(information,links) ; strcat(information,"  "); 
    strcat(information,owner) ; strcat(information,"  ");
    strcat(information,group) ; strcat(information,"  ");
    strcat(information,size) ; strcat(information,"  ");
    strcat(information,month) ; strcat(information,"  ");
    strcat(information,name) ; strcat(information,"  ");
    //printf("%s\n",information);
}

void total()
{

   system("ls -s > /home/dhar/toy/en/total.txt");
   char c[30];
   FILE *f;
   f = fopen("/home/dhar/toy/en/total.txt" , "r");
   fscanf(f, "%[^\n]", c);
   printf("%s\n", c);
   fclose(f);
 
}

int information(const char *path)
{
   int i=0;
   struct dirent *entry;
   DIR *dp;

   dp = opendir(path);
   if (dp == NULL) 
   {
     perror("opendir");
     return -1;
   }
   total();
   while((entry = readdir(dp)))
   {
     const char *name = entry->d_name;
     if (name[0] != '.')
     {
       fetch_info(name,i);
     }
   }   
}



int main(int argc, char **argv) {
  int counter = 1;

  if (argc == 1)
	listdir(".");
  else
  {
     if (!(strcmp(argv[1],"-a"))) listdir(".");
     else if (!(strcmp(argv[1],"-t"))) sort2(".");
     else if (!(strcmp(argv[1],"-l"))) information(".");
  }

  return 0;
}

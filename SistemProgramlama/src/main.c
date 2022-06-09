//G191210068 Ömer Faruk Güzel 2A Sistem Programlama


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "fields.h"
#include "dllist.h"

int main(int argc, char **argv)
{
  Dllist sl, stmp;  
  IS is;//input 
  IS is2;//sozluk
  int cevrilen_kelime_sayisi=0;
  int cevrilemeyen_kelime_sayisi=0;
  int karsilastirilan_kelime_sayisi=0;


  sl = new_dllist();

  if (argc != 4) { fprintf(stderr, "Eksik Veya Fazla Parametre\n"); exit(1); }
 

  is = new_inputstruct(argv[2]);
  is2 = new_inputstruct(argv[3]);
  if (is == NULL ) {
    perror(argv[2]);
    exit(1);
  }
  if (is2 == NULL ) {
    perror(argv[3]);
    exit(1);
  }
  

int result;


  if(strcmp(argv[1],"eng")==0)
  {
	while(get_line(is) >= 0) 
	{	
	    for (int i = 0; i < is->NF; i++) 
	    {
	     karsilastirilan_kelime_sayisi++;
	     
	     int Length  =0;	    
	    while(is->fields[i][Length]!='\0')
	    Length++;


	   if (ispunct(is->fields[i][Length-1]))
	   {
	     is->fields[i][Length-1]='\0';	   	
	   }
	   if(ispunct(is->fields[i][0]))
	   {
	     for(int k=1;k<Length;k++)
	     {
		is->fields[i][k-1]=is->fields[i][k];
	     }
	   }
	     while(get_line(is2) >= 0) 
	     {
		for (int j = 2; j < is2->NF; j++)
	    	{
	    	  result = strcmp(is->fields[i], is2->fields[j]);
	    	
	    	    if (result==0 ) 
	    	    {
	    	    cevrilen_kelime_sayisi++;
	    	     dll_append(sl, new_jval_s(strdup(is2->fields[j-1])));
	     	     
	     	      break;
	   	    }   	   
	    	    
		}
		if (result==0) 
	    	{	    	   
	     	  break;
	   	}		   
	     }
	     
	     if (result!=0) 
	     {
	     cevrilemeyen_kelime_sayisi++;
	       dll_append(sl, new_jval_s(strdup(is->fields[i])));
	     
	     }   
	     jettison_inputstruct(is2);
	     is2 = new_inputstruct(argv[3]);	    

	    }
	}
  
  }
  else if(strcmp(argv[1],"tr")==0)
  {
	while(get_line(is) >= 0) 
	{	
	    for (int i = 0; i < is->NF; i++) 
	    {	  
	    karsilastirilan_kelime_sayisi++;
	    
	    int Length  =0;	    
	    while(is->fields[i][Length]!='\0')
	    Length++;


	   if (ispunct(is->fields[i][Length-1]))
	   {
	     is->fields[i][Length-1]='\0';
	   	
	   }
	   if(ispunct(is->fields[i][0]))
	   {
	     for(int k=1;k<Length;k++)
	     {
		is->fields[i][k-1]=is->fields[i][k];
	     }
	   }
	    
	     while(get_line(is2) >= 0) 
	     {
	     
		for (int j = 1; j < is2->NF-1; j++)
	    	{
	    	  result = strcmp(is->fields[i], is2->fields[j]);
	    	
	    	    if (result==0) 
	    	    {
	    	    cevrilen_kelime_sayisi++;
	    	      dll_append(sl, new_jval_s(strdup(is2->fields[j+1])));
	     	      
	     	      break;
	   	    }	
	   	   	    	    
		}
		if (result==0) 
	    	{	    	   
	     	  break;
	   	}	
		
	   
	     }
	     if (result!=0) 
	     {
	     cevrilemeyen_kelime_sayisi++;
	      dll_append(sl, new_jval_s(strdup(is->fields[i])));
	      
	     }   
	     jettison_inputstruct(is2);
	     is2 = new_inputstruct(argv[3]);	    
	    }
	}
  }
  else{
      printf("Komut Hatasi eng veya tr yaziniz");
    exit(1);
  }
  

   int num;
   FILE *fptr;

   fptr = fopen("txt/output.txt","w");

   if(fptr == NULL)
   {
      printf("Dosya Hatasi");   
      exit(1);             
   }
   
  stmp = sl->flink;

    
  while (stmp != sl) {
    fprintf(fptr,"%s %s",stmp->val.s,"");
    printf("%s %s", stmp->val.s, "");
    stmp = stmp->flink;
  }
  printf("\n");
   while (stmp != sl) {
     free(sl->flink->val.s);
      dll_delete_node(sl->flink);
  }
   fclose(fptr);
 printf("%s %i\n","Karsilastirilan kelime Sayisi",karsilastirilan_kelime_sayisi);
   printf("Cevrilen kelime Sayisi %i\n",cevrilen_kelime_sayisi);
    printf("Cevrilemeyen kelime Sayisi %i\n",cevrilemeyen_kelime_sayisi);
    
    
    
  

  jettison_inputstruct(is);
  jettison_inputstruct(is2);
  return 0;
}

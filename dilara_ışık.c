# include <stdio.h>
	# include <pthread.h>
	# include <stdlib.h>
	
	int num=0;

 char ch;

	struct to_read{
	  FILE *fp;
	  long int offset;
	  int start;
	  int chunk_size;
	};
	

	struct word{
	  char *word;
	  int count;
	};
	  
	void word_freq(struct to_read *data)
	{
	  char word[100];
	  int wordcount=0;
	
	  int i,c;
	  i=0;c=0;
	
	while ((ch=getc(data->fp)) != EOF) {
		
		   if (ch == ' ' || ch == '\n')
		    {
			 ++wordcount; 
			}	   
	   }
	   	
printf("\n thread ile bulunan kelime sayisi %d\n",wordcount);

	  pthread_exit(NULL);
	  return;
	}
	

	int main(int argc, char **argv)
	{
	  int nthreads, ret_val, tid, chunk_size;
	  void *status;
	  FILE *fp;
	  pthread_t *threads;
	

	  struct to_read data;
	

	  fp = fopen("file.txt", "r");
	  
	  if (fp==NULL)
	    {
	      perror("Could not open file. Exiting");
	      exit(1);
	    }
	

	  printf("Enter the number of threads: ");
	  scanf("%d",&nthreads);
	  threads = malloc(nthreads*sizeof(pthread_t));
	
	  chunk_size = 13219/nthreads;
	

	  for(tid = 0; tid < nthreads-1; tid++)
	    {
	      data.fp=fp;
	      data.offset = chunk_size;
	      data.start = tid*chunk_size+1;
	      ret_val = pthread_create(&threads[tid], NULL, &word_freq, &data);
	      
	      if(ret_val!= 0) {
	        printf ("Create pthread error!\n");
	        exit (1);
	      }
	    }
	
	  data.fp=fp;
	  data.offset = chunk_size + (13219 % nthreads);
	  data.start = (nthreads-1)*chunk_size+1;
	  ret_val = pthread_create(&threads[nthreads-1], NULL, &word_freq, &data);
	      
	  if(ret_val!= 0) {
	    printf ("Create pthread error!\n");
	    exit (1);
	  }
	

	  pthread_join(threads[nthreads-1],&status);
	

	  fclose(fp);
	  free(threads);
	

	  pthread_exit(NULL);
	  return 0;  
	}



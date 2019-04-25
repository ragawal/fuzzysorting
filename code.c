#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct out{
	float n1,n2;
};

void change(float* a, float* b) 
{ 	
    float t = *a; 
    *a = *b; 
    *b = t; 
}

struct out intersect(float arr1[], float arr2[], int p, int s, float a, float b)
{ struct out s1;
  int num = (rand() % ( s - p + 1)) + p;
  change(&arr1[num],&arr1[s]);
  change(&arr2[num],&arr2[s]);
  a = arr1[s];
  b = arr2[s];
  for(int i=p;i<s;i++)
	{ if (arr1[i]<=b&&arr2[i]>=a)
		{ if(arr1[i]>a)
			a=arr1[i];
		    if(arr2[i]<b)
			b=arr2[i];	}
}
s1.n1=a;
s1.n2=b;
return s1;
}

int right(float arr1[],float arr2[], float a1,int p,int s){
int i =p-1;
for (int j=p;j<s;j++)
	{ if(arr1[j]<a1)
		{ i=i+1;
		  change(&arr1[i],&arr1[j]);
		  change(&arr2[i],&arr2[j]);
		}}
change(&arr1[i+1],&arr1[s]);
change(&arr2[i+1],&arr2[s]);

return i+1;
}


int left(float arr1[],float arr2[], float b1,int p,int r){
int i =p-1;
for (int j=p;j<r;j++)
	{ if(arr2[j]<b1)
		{ i=i+1;
		  change(&arr1[i],&arr1[j]);
		  change(&arr2[i],&arr2[j]);
		}}
change(&arr1[i+1],&arr1[r]);
change(&arr2[i+1],&arr2[r]);

return i+1;

}
 
void fuzzysort(float arr1[],float arr2[],int p,int s)
{ struct out s2;
	if(p<s)
	{ float a=0;
	  float b=0;
	  s2=intersect(arr1,arr2,p,s,a,b);
	  int r = right(arr1,arr2,s2.n1,p,s);
	  int q = left(arr1,arr2,s2.n2,p,r);
 	  fuzzysort(arr1,arr2,p,q-1);
	  fuzzysort(arr1,arr2,r+1,s);
	}
}

void printArray(float  arr1[],float arr2[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%f,%f ", arr1[i],arr2[i]); 
}

int main() 
{   double total_time;
	clock_t start_time, end_time;
    FILE *inputfile;
    FILE *outputfile;
	float f;
	double n;
	float arr1[1000001];  
    float arr2[1000001];
	long int size = 0;
	for(n=1000;n<1000001;n=n+5000){
	inputfile=fopen("large_overlap.txt", "r");
	if(inputfile){
		while(!feof(inputfile))
		{
			fscanf(inputfile,"%f",&f);
			arr1[size] = f;
			fscanf(inputfile,"%f",&f);
			arr2[size] = f;

			size++;
			if(size>n)
				break;
		}
	}
	fclose(inputfile);
	printf("File Read \n");
	printf("Size = %ld \n",size); 
    start_time = clock();
    fuzzysort(arr1,arr2, 0, n-1);
    end_time = clock(); 
    outputfile=fopen("timing.txt", "a");
    //printf("Sorted array"); 
    //printArray(arr1, arr2, n);
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    //fprintf(outputfile, "size= %f \n", n);
    fprintf(outputfile, "%f \n", total_time);
    fclose(outputfile);
	printf("\nTime taken(in seconds) to run Fuzzy-Sort of size %f: %f \n", n, total_time);} 
    return 0; 
}

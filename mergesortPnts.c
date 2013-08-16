#include<stdio.h>
#include<stdlib.h>

#define MAX 2000

// defines a point and accessible throught the program
struct Point
{
   int x;
   int y;
};

typedef struct Point  pnt;

void merge(pnt arr[],int low,int mid,int high);
void mergesort(pnt arr[],int low,int high);

int main()

{

int size;
int i;
int i1=0,i2=0,i3=0,i4=0;

scanf("%d",&size);
printf("\nsize of input is:   %d\n", size);

pnt  p[size];
pnt p1[size],p2[size],p3[size],p4[size];
printf("size of the structure is: %d\n", sizeof(pnt));


// the following reads the input via shell redirected input 
// and arranges the input in all four quadrants

  for(i=0;i<size;i++)
 {
   scanf("%d %d",&p[i].x,&p[i].y);

      if(p[i].x>=0 && p[i].y>=0)
      {
               p1[i1].x = p[i].x;
               p1[i1].y = p[i].y;
               i1 = i1 +1;
       }

      if(p[i].x<0 && p[i].y>=0)
      {
               p2[i2].x = p[i].x;
               p2[i2].y = p[i].y;
               i2 = i2 +1;
       }

      if(p[i].x<0 && p[i].y<0)
      {
               p3[i3].x = p[i].x;
               p3[i3].y = p[i].y;
               i3 = i3 +1;
       }
      if(p[i].x>=0 && p[i].y<0)
      {
               p4[i4].x = p[i].x;
               p4[i4].y = p[i].y;
               i4 = i4 +1;
       }

  }

 printf("values: %d %d %d %d\n", i1,i2,i3,i4);

//  passes the array for the first quadrant
  mergesort(&p1[0],0,i1-1);

//  passes the array for the second quadrant
  mergesort(&p2[0],0,i2-1);

// passes the array for the third quadrant
  mergesort(&p3[0],0,i3-1);

// passes the array for the fourth quadrant
  mergesort(&p4[0],0,i4-1);


 printf("after the merge:\n");

// when duplicates emerge the point array is populated with 0 0 when merge happens
// those hold no value and deemed be not part of original array of pointers and hence not printing them by using the cond 
//(p[i].x !=0 && p[i].y!=0)

  for(i=0;i<i1;i++)
 {
   if((p1[i].x ==0) && (p1[i].y==0))
   continue;
   else
   printf("%d %d \n",(p1[i].x),(p1[i].y));
  }

  for(i=0;i<i2;i++)
 {
   if((p2[i].x ==0) && (p2[i].y==0))
   continue;
   else
   printf("%d %d \n",(p2[i].x),(p2[i].y));
  }

  for(i=0;i<i3;i++)
 {
   if((p3[i].x ==0) && (p3[i].y==0))
   continue;
   else
   printf("%d %d \n",(p3[i].x),(p3[i].y));
  }

  for(i=0;i<i4;i++)
 {
   if((p4[i].x ==0) && (p4[i].y==0))
   continue;
   else
   printf("%d %d \n",(p4[i].x),(p4[i].y));
  }
   
  return 0;
}



void mergesort(pnt arr[],int low,int high){

    int mid;
    if(low<high){
         mid=(low+high)/2;
         mergesort(arr,low,mid);
         mergesort(arr,mid+1,high);
         merge(arr,low,mid,high);
    }
}

void merge(pnt arr[],int low,int mid,int high)
{

    int i,m,k,l;
    int m1,m2,sq;
    pnt temp[MAX];
    l=low;
    i=low;
    m=mid+1;

// merge logic begins here
    while((l<=mid)&&(m<=high))
   {
         // calculates the m1 and m2 in order to compare slopes of the two points to be merged
         m1 = arr[m].x * arr[l].y;
         m2 = arr[l].x   * arr[m].y;

         if(m1<m2)
        {
             temp[i]=arr[l];
             l++;
         }
         else
         {
           if(m1>m2)
           {
             temp[i]=arr[m];
             m++;
           }
           else
           {
             // this part keeps the point closer to origin when the slopes are equal or in other words when points are   collinear
             // this uses a small technique of squaring the x-axis coordinates and y-axis coordinates to determine and substract individual results
             // by doing so, we can clearly establish a distance-relation of points with respect to the origin
             sq = ((arr[l].x * arr[l].x ) - (arr[m].x * arr[m].x ) + (arr[l].y * arr[l].y ) - (arr[m].y * arr[m].y ));
             if((m1 - m2 == 0)&&(sq!=0))
            {

                 if (sq < 0)
                 {
                       temp[i]=arr[l]; 
                       l++;
                 }
                 else
                 {    
                        temp[i]=arr[m]; 
                        m++;
                  }
            }
            // handles the duplicate points here ( bug prone )
            if((m1 - m2 == 0)&&(sq==0))
            {
                        temp[i]=arr[l];
                        m++;
                        l++;
                        //size = size - 1;
                        //i--;
            }

           }

         }
         i++;
    }


// following takes care of assigning the values according to the comparison happened in loop above
     if(l>mid)
    {
          for(k=m;k<=high;k++){
              temp[i]=arr[k];
              i++;
          }
     }
     else
     {
          for(k=l;k<=mid;k++)
          {
              temp[i]=arr[k];
              i++;
          }
     }
//finally it's all rearranged here
    for(k=low;k<=high;k++)
    {
         arr[k]=temp[k];
         temp[k].x = 0;
         temp[k].y = 0;
    }

}

#include<stdio.h>
#include <stdlib.h>
int main()
{
 int da[20],di[20],te[20],tem[20],l;
 int i,j,m,n,data,div,t,k,e;
 printf("\nEnter the total bit of data and divisor");
 scanf("%d %d",&data,&div);
 m=data+div-1;
 printf("\nEnter the data:");
 for(i=0;i<data;i++)
    {   scanf("%d",&da[i]);te[i]=da[i];  }
 for(i=data;i<m;i++)
    {   te[i]=0;                        }
 printf("\nEnter the divisor");
 for(i=0;i<div;i++)
    {   scanf("%d",&di[i]);             }
 l=div;t=0;
 k=0;
 for(i=0;i<data;i++)
    {
      e=0;t=0;
      for(j=1;j<div;j++)
         {
           if(((da[j]==1)&&(di[j]==1))||((da[j]==0)&&(di[j]==0)))
              {
                tem[j-1]=0;
                if(e!=1)
                   {
                     k=k+1;
                     t=t+1;
                     i=i+1;
                   }
              }
           else
              {
                tem[j-1]=1;
                e=1;
              }
         }
      j=0;
      for(e=t;e<div-1;e++)
         {
           da[j]=tem[e];
           j++;
         }
      for(j=j;j<div;j++)
         {
           if(l>=data+1)
              {
                da[j]=0;
              }
           else
              {
                da[j]=te[l];
                l=l+1;
              }
         }
    }
 printf("\n The CRC BITS are\t ");
 for(i=0;i<div-1;i++)
    {
      printf(" %d",tem[i]);
    }
}
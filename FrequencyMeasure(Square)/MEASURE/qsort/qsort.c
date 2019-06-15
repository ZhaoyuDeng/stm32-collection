#include "sys.h"

void SelectionSort(u32 *num,u32 n)
{
  u32 i = 0;
  u32 min = 0;
  u32 j = 0;
  u32 tmp = 0;
  for(i = 0;i < n-1;i++)
  {
 	  min = i;//每次讲min置成无序组起始位置元素下标 
    for(j = i;j < n;j++)//遍历无序组，找到最小元素。 
    {
	    if(num[min]>num[j])
	  {
	  min = j;
	  }
	}
	if(min != i)//如果最小元素不是无序组起始位置元素，则与起始元素交换位置 
	{
	  tmp = num[min];
	  num[min] = num[i];
	  num[i] = tmp;
	}
 }
}

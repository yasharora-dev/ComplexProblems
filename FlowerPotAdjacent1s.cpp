//
//  FlowerPotAdjacent1s.cpp
//  ComplexProblems
//
//  Created by Yash Arora on 28/09/20.
//  Copyright © 2020 Yash Arora. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

class Flowerpots_Adjacent1s{

public:
    
    
static bool findFlowePots(vector<int> &arr, int k)
{
   /* if(arr[0]==0 && arr[1]==0)
    {
        arr[0]=1;
        k--;
    }*/
    int len = arr.size();
    
    for(int i=0;i<len;i++)
    {
        if(arr[i]!=0)
            continue;
        
        if( (i==0 && arr[i+1]==0) || ((i == len-1) && arr[i-1]==0) )
        {
            k--;
            arr[i]=1;
        }
        else if(arr[i-1]==0 && arr[i+1]==0)
        {
            k--;
            arr[i]=1;
        }
        
        
    }
    
   /* if(arr[arr.size()-1]==0 && arr[arr.size()-2]==0)
    {
        k--;
        arr[arr.size()-1]=1;
    }*/
    
    return (k<=0);
    
}
static void Test_Flowerpots_Adjacent1s()
{

        vector<int> arr {  0, 0, 0, 0,0 };
          
        cout << findFlowePots(arr,3)<<endl;
}
    
};

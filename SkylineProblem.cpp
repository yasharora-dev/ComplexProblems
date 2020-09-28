//
//  SkylineProblem.cpp
//  ComplexProblems
//
//  Created by Yash Arora on 26/09/20.
//  Copyright © 2020 Yash Arora. All rights reserved.
//
//https://www.youtube.com/watch?v=GSBLe8cKu0s&list=PLrmLmBdmIlpuE5GEMDXWf0PWbBD9Ga1lO&index=7
/*
* Given skyline of a city merge the buildings
*
* Time complexity is O(nlogn)
* Space complexity is O(n)
*
* References
* https://leetcode.com/problems/the-skyline-problem/
* https://leetcode.com/discuss/67091/once-for-all-explanation-with-clean-java-code-nlog-time-space
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <set>



using namespace std;

class Building{
public:
    int start;
    int end;
    int height;
    
    Building(int st,int e,int ht)
    {
        start=st;
        end=e;
        height=ht;
    }
};


class strip{
public:
    int XCord;
    int height;
    bool isStart;
    
    strip(int X,int ht, bool stEnd)
    {
        XCord=X;
        height=ht;
        isStart=stEnd;
    }
};



class Skyline{
    
public:
    
    
    static int getMaxEndCityBoundary(vector<Building> &buildings)
    {
        //min,max
        int maxEnd=0;
        
        for(int i=0;i<buildings.size();i++)
        {
            maxEnd = max(buildings[i].end,maxEnd);
        }
        
        return maxEnd;
    }
    
    //Time COmplex: O(n^2)
    //Space: O(n)
    static vector<pair<int,int>> getBuildingsSkyline(vector<Building> &buildings)
    {
        
        vector<pair<int,int>> skyline;
        //get boundary of city min,max
        int cityEnd =  getMaxEndCityBoundary(buildings);
        
        vector<int> auxHeight(cityEnd+1);
        //consider each X cordinate as building of width 1 unit and take a aux array to store max height of
        //all such 1 length buildings from lowest left to max right i.e. city's start and city's end
        
        
        
        for(int i=0;i<buildings.size();i++)
        {
            for(int j=buildings[i].start;j<buildings[i].end;j++)
            {
                //for every range [st,end) add the heights to the building if the height is greater than
                //current height
                //in this way auxHeights will have the highest hieght at each cordinate
                //now you need to create the ouput cordinates using ths
                //here index represent the building and its value represents its height
                auxHeight[j]=max(buildings[i].height,auxHeight[j]);
            }
        }
        
        int prevHt=0;
        for(int i=1;i<auxHeight.size();i++)
        {
            if(auxHeight[i]!=prevHt)
            {
                prevHt=auxHeight[i];
                skyline.push_back(make_pair(i, auxHeight[i]));
            }
        }
        return skyline;
    }
    
    static bool compareStrips(const strip &a, const strip &b)
    {
  
        //first compare by XCord.
        //If they are same then use this logic
         //if two starts are compared then higher height building should be picked first
         //if two ends are compared then lower height building should be picked first
         //if one start and end is compared then start should appear before end
        if (a.XCord != b.XCord)
        {
            return a.XCord < b.XCord;
        }
        else {
            if(a.isStart && b.isStart)
                return a.height > b.height;
            else if(!a.isStart && !b.isStart)
                return a.height < b.height;
            else
                return a.isStart?true:false;
        }
        
    }
    //time; O(nlogn)
    //space: O(n)
    static vector<pair<int,int>> getBuildingsSkyline_BST(vector<Building> &buildings)
    {
        vector<pair<int,int>> skyline;
        //here the intuition is that we need the previous Max height and current max height at anytime
        //instead of storing all the heights
        //this can lead to optimization and reduce the time complexity from O(n^2)
        set<int> auxHeights;
        auxHeights.insert(0); //base case
        int maxVal=0;
        
        //now separate the starts and ends from building triplets
        //as in previous approach we dont need to store all the cordinates from start to end
        //we can only store start and end and use that to determine the skyline points
        
        vector<strip> Strips;
        
        for(int i=0;i<buildings.size();i++)
        {
            Strips.push_back(strip(buildings[i].start,buildings[i].height,true));
            Strips.push_back(strip(buildings[i].end,buildings[i].height,false));
        }
        
        //sort the strips based on XCord as we are interested in traversing from left end of city to right end
        sort(Strips.begin(), Strips.end(), compareStrips);
        
        
        for(int i=0;i<Strips.size();i++)
        {
            //if its start strip then if by adding the strip/building the maxHeight changes i.e. increases
            //then this is the tallest building till now so add it in output
            if(Strips[i].isStart)
            {
                
                auxHeights.insert(Strips[i].height);
                int newMaxVal = *(auxHeights.rbegin());
                
                if(newMaxVal!=maxVal)
                {
                    maxVal=newMaxVal;
                    skyline.push_back(make_pair(Strips[i].XCord,Strips[i].height));
                }
                
            }
            //if its the end strip then we need to remove its height from auxHeight as its end is reached
            //and if the maxVal changes after the rmeoval then it means that this was the tallest building till
            //now and its finished, so there might be other building shorter than this
            //so add it in output
            //here the putput would be Xcord and newMaxHeight after the removal
            // i.e. the tallest building now after the removal
            //it can any other shorter building with greater width or 0
            else
            {
                auxHeights.erase(auxHeights.find(Strips[i].height));
                int newMaxVal = *(auxHeights.rbegin());
                if(newMaxVal!=maxVal)
                {
                    maxVal=newMaxVal;
                    skyline.push_back(make_pair(Strips[i].XCord,newMaxVal));
                }
                
            }
        }
        
        return skyline;
    }
    
    
    static void Test_Skyline()
    {
        vector<Building> buildings{ Building(1,3,3),
                                    Building(2,4,4),
                                    Building(5,8,2),
                                    Building(6,7,4),
                                    Building(8,9,4) };
        
        cout<<"Skyline for the buildings is as below"<<endl;
        vector<pair<int,int>> skyline = getBuildingsSkyline(buildings);
        
        for(auto cord: skyline)
            cout<<cord.first << " , "<<cord.second<<endl;
        
        cout<<"Skyline for the buildings in optimized approach is as below"<<endl;
        vector<pair<int,int>> Potskyline = getBuildingsSkyline_BST(buildings);
        
        for(auto cord: Potskyline)
            cout<<cord.first << " , "<<cord.second<<endl;
        
        
    }
};

//
//  WordBreak.cpp
//  ComplexProblems
//
//  Created by Yash Arora on 30/09/20.
//  Copyright © 2020 Yash Arora. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class WordBreak{
  
public:
    static bool existsInDict(string str, vector<string> &dict)
    {
        for(string &word: dict)
        {
            if(word.compare(str)==0)
                return true;
        }
        return false;
    }
    static bool WordBreak_Rec(string pat, vector<string> &dict)
    {
        //if empty string then return true
        int size = pat.size();
        
        
        //we are going to pass new substr at every recursion, so when there is an empty string with size=0 return true
        // as if the first string exists in dict it will be true and this should return
        //e.g. in case of e, it should return true as e and empty string will both return true
        //so empty string always return true
        if(size == 0)
            return true;
        
        //iterate for all prefix lengths
        // inside for e.g. code string c will be called and then it will be true if any of c o d e is true
        // this  is possible due to for loop and recursive call which will again call this for loop for all lengths
        for(int i=1;i<=size;i++)
        {
            //if a char exists in dict and the remaining string also exists in dict then return true
            //here in recursive call every length will be checked again
            if(existsInDict(pat.substr(0,i),dict) && WordBreak_Rec(pat.substr(i,size-i), dict))
                return true;
        }
        
        return false;
    }
    
    //use memoization to store the overlapping subproblems which can be reused
    static bool WordBreak_TopDownDP(string pat, vector<string> &dict, unordered_map<string,bool> &map)
    {
        if(map.find(pat)!=map.end())
            return true;
        
        int size = pat.size();
        
        if(size == 0)
        {
            map[pat]=true;
            return true;
        }
        for(int len=1;len<=size;len++)
        {
            if(existsInDict(pat.substr(0,len), dict) && WordBreak_TopDownDP(pat.substr(len,size-1), dict,map))
            {
                map[pat]=true;
                return true;
            }
            
        }
        
        map[pat]=false;
        return false;
    }
    
    static bool WordBreak_BtmUpDP(string pat, vector<string> &dict)
    {
        int size = pat.size();
        
        unordered_set<string> dictSet;
        
        for(auto word: dict)
            dictSet.insert(word);
        
        //edge case
        if(size==0)
            return true;
        
        vector<bool> DP(size+1);
        DP[0]=true; //empty string is always true
        
        for(int len=1;len<=size;len++)
        {
            for(int i=0;i<len;i++)
            {
                string str = pat.substr(i,len-i);
                if(DP[i] && (dictSet.count(str)>0))
                {
                    DP[len]=true;
                    break;
                }
            }
            
        }
        
        return DP[size];
    }
    
    static bool WordBreak_BtmUpDP_v2(string pat, vector<string> &dict)
    {
        return 1;
    }
    
    static void Test_WordBreak()
    {
        string pat = "code";
        vector<string> dict { "c", "od", "e"};
        
        if(WordBreak_Rec(pat,dict))
            cout<<pat<<" word can be break into words existing in dictionary"<<endl;
        else
            cout<<pat<<" word cannot be break into words existing in dictionary"<<endl;
        
        unordered_map<string, bool> map;
        if(WordBreak_TopDownDP(pat,dict,map))
            cout<<pat<<" word can be break into words existing in dictionary"<<endl;
        else
            cout<<pat<<" word cannot be break into words existing in dictionary"<<endl;
        
        
        if(WordBreak_BtmUpDP(pat,dict))
            cout<<pat<<" word can be break into words existing in dictionary"<<endl;
        else
            cout<<pat<<" word cannot be break into words existing in dictionary"<<endl;
        
        string pat1 = "iamyash";
        vector<string> dict1 { "am", "as", "i", "yash"};
        
        if(WordBreak_BtmUpDP(pat1,dict1))
            cout<<pat1<<" word can be break into words existing in dictionary"<<endl;
        else
            cout<<pat1<<" word cannot be break into words existing in dictionary"<<endl;
        
    }
};

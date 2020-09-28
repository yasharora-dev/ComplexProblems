//
//  WordSearch_NotZigZag.cpp
//  ComplexProblems
//
//  Created by Yash Arora on 27/09/20.
//  Copyright © 2020 Yash Arora. All rights reserved.
//
/*
 https://www.geeksforgeeks.org/search-a-word-in-a-2d-grid-of-characters/
 
 Given a 2D grid of characters and a word, find all occurrences of the given word in the grid. A word can be matched in all 8 directions at any point. Word is said to be found in a direction if all characters match in this direction (not in zig-zag form).

 The 8 directions are, Horizontally Left, Horizontally Right, Vertically Up and 4 Diagonal directions.
 Input:  grid[][] = {"GEEKSFORGEEKS",
                     "GEEKSQUIZGEEK",
                     "IDEQAPRACTICE"};
         word = "GEEKS"

 Output: pattern found at 0, 0
         pattern found at 0, 8
         pattern found at 1, 0
 Explanation: 'GEEKS' can be found as prefix of
 1st 2 rows and suffix of first row

 Input:  grid[][] = {"GEEKSFORGEEKS",
                     "GEEKSQUIZGEEK",
                     "IDEQAPRACTICE"};
         word = "EEE"

 Output: pattern found at 0, 2
         pattern found at 0, 10
         pattern found at 2, 2
         pattern found at 2, 12
 Explanation: EEE can be found in first row
 twice at index 2 and index 10
 and in second row at 2 and 12
 */

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

#define R 3
#define C 14




class WordSearchInLine{
public:
    
    static bool DFSSearch(char grid[R][C], string &pat, int row,int col)
    {
        
        if(row<0 || col <0 || row >=R || col >=C)
            return false;
        
        vector<int> X {-1,1,0,0,-1,1,-1,1};
        vector<int> Y {0,0,-1,1,-1,1,1,-1};
        
        for(int dir=0;dir<X.size();dir++)
        {
            int rowd = row + X[dir];
            int cold = col + Y[dir];
            int k;
            for(k=1;k<pat.length();k++)
            {
                if(rowd < 0 || rowd >=R || cold<0 || cold>=C)
                    break;
                
                if(grid[rowd][cold] != pat[k])
                       break;
                    
                    rowd+=X[dir];
                    cold+=Y[dir];
            }
            
            if(k==pat.length())
                return true;
        }
        
        return false;
    }
    static void patternSearch(char grid[R][C],string pat)
    {
        int nrow=R;
        int ncol = C;
        
        for(int i=0;i<nrow;i++)
        {
            for(int j=0;j<ncol;j++)
            {
                if(grid[i][j]==pat[0] && DFSSearch(grid,pat,i,j) )
                {
                    cout<<"pattern starts at "<<i <<" and "<<j<<endl;
                }
            }
        }
    }
    static void Test_WordSearchInLine()
    {
        char grid[R][C] = { "GEEKSFORGEEKS",
                              "GEEKSQUIZGEEK",
                              "IDEQAPRACTICE" };
        
        patternSearch(grid,"GEEKS");
                                    
    }
};

//
//  JosephusProblem.cpp
//  ComplexProblems
//
//  Created by Yash Arora on 29/09/20.
//  Copyright © 2020 Yash Arora. All rights reserved.
//
/*
 
 There are N Children are seated on N chairs arranged around a circle. The chairs are numbered from 1 to N. The game starts going in circles counting the children starting with the first chair. Once the count reaches K, that child leaves the game, removing his/her chair. The game starts again, beginning with the next chair in the circle. The last child remaining in the circle is the winner. Find the child that wins the game.
 
 or
 
 There are n people standing in a circle waiting to be executed. The counting out begins at some point in the circle and proceeds around the circle in a fixed direction. In each step, a certain number of people are skipped and the next person is executed. The elimination proceeds around the circle (which is becoming smaller and smaller as the executed people are removed), until only the last person remains, who is given freedom. Given the total number of persons n and a number k which indicates that k-1 persons are skipped and kth person is killed in circle. The task is to choose the place in the initial circle so that you are the last one remaining and so survive.

 For example, if n = 5 and k = 2, then the safe position is 3. Firstly, the person at position 2 is killed, then person at position 4 is killed, then person at position 1 is killed. Finally, the person at position 5 is killed. So the person at position 3 survives.
 If n = 7 and k = 3, then the safe position is 4. The persons at positions 3, 6, 2, 7, 5, 1 are killed in order, and person at position 4 survives.
 
 
 Video: recursive solution gfg gaurav sen
 https://www.youtube.com/watch?v=fZ3p2Iw-O2I
 
 
For k=2 special case
 
 https://www.geeksforgeeks.org/josephus-problem-using-bit-magic/?ref=rp
 
 Video: Mathematical Proof for K=2
 https://www.youtube.com/watch?v=fZ3p2Iw-O2I
 
 
 */
#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;

class JosephusProblem{
    
public:
    
    static int MSBPosition(int n)
    {
        int pos=0;
        while(n>0)
        {
            pos++;
            n=n>>1; //divide by 2 or right shift by 1
        }
        return pos;
    }
    //O(logn) solution when k=2 i.e. every alternate person keeps on killing
    static int JosephusProblemK2_formula(int n) {
        //as per the above video you can clearly see twi solutions
        //W(n) : 2*l +1 if n= 2^a+l, where a > l and 2^a is the largest power of 2 smaller than n
        //this is because for exact 2^n the winner is 1
        // 1: 1 (2^0), 2:1 (2^0), 4:1 (2^2) etc
        
        int msbPos = MSBPosition(n);
        
        //now largest power of 2 smaller than n is msbPos with 1 i.e. for 41 its 2^5=32
        
        int power = pow(2,msbPos-1); //2^5: 32
        
        int l = n-power;
        
        return (2*l+1);
        
        
    }
    
    //O(logn) solution when k=2 i.e. every alternate person keeps on killing
    static int JosephusProblemK2_bitMagic(int n) {
        //as per the above video you can clearly see twi solutions
        //if you rotate the mSB and plcae it at LSB it gives you the answe
        
        int msbPos = MSBPosition(n);
        
        //now to remove the msb and place it lsb
        //we need to unset msb pos and then add one 0 at LSB and set it to 1
        
        //for unsetting we can use xor
        
        int XOR = 1 << (msbPos-1); //muliples by 2
        
        int ans = n ^ XOR;
        //now add 0 at end so left shift by 1
        ans = ans << 1;
        //zero appended at end, now set it to 1
        ans = ans | 1;
        
        return ans;
        
    }
    static int JosephusProblemGeneralized_Rec(int n, int k)
    {
        //here we two params for state of solution: n and k
        //as with diff n and k values the answer will change
        //fn(n,k)
        //now we know that when n==1 then 1 will win, so that becomes our base case
        //now for every turn a person is killed to n-1 becomes new state
        //and as we are in a circle we need to find the remainder of the people answer so %n+1
        //1 to adjust the starting 1
        //also k-1 person are to be skipped next time to find the next person to be killed
        
        //fn(n,k)= (fn(n-1,k)+k-1)%n+1 and fn(1,k)=1;
        
        if(n==1)
            return 1;
        
        return ((JosephusProblemGeneralized_Rec(n-1,k)+k-1)%n+1);
        
    }
    static int JosephusProblemGeneralized_DP(int n, int k){
        int sum =0;
        
        for(int i=2;i<=n;i++)
        {
            sum=(sum+k)%i;
        }
        return sum+1;
    }
    
    static void Test_JosephusProblem()
    {
        //there are 7 people and every 3rd person has be killed find the standing position where you will tbe the last man standing
        
        cout<<"With N=7 and K=3 Last Man Standing will be: "<<JosephusProblemGeneralized_Rec(7,3)<<endl;
        cout<<"With N=7 and K=3 Last Man Standing will be: "<<JosephusProblemGeneralized_DP(7,3)<<endl;
        cout<<"With N=41 and K=8 Last Man Standing will be: "<<JosephusProblemGeneralized_Rec(41,8)<<endl;
        cout<<"With N=41 and K=8 Last Man Standing will be: "<<JosephusProblemGeneralized_DP(41,8)<<endl;

        cout<<"With N=41 and K=2 Last Man Standing will be: "<<JosephusProblemK2_formula(41)<<endl;
        cout<<"With N=41 and K=2 Last Man Standing will be: "<<JosephusProblemK2_bitMagic(41)<<endl;
    }
};

//
//  main.cpp
//  ComplexProblems
//
//  Created by Yash Arora on 26/09/20.
//  Copyright © 2020 Yash Arora. All rights reserved.
//

#include <iostream>
#include "SkylineProblem.cpp"
#include "WordSearch_NotZigZag.cpp"
#include "FlowerPotAdjacent1s.cpp"
#include "JosephusProblem.cpp"
#include "WordBreak.cpp"


int main(int argc, const char * argv[]) {
    // insert code here...
    
    Skyline::Test_Skyline();
    
    WordSearchInLine::Test_WordSearchInLine();
    
    Flowerpots_Adjacent1s::Test_Flowerpots_Adjacent1s();
    
    JosephusProblem::Test_JosephusProblem();
    
    WordBreak::Test_WordBreak();
    
    return 0;
}

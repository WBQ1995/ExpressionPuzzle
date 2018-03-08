//
//  main.cpp
//  ExpressionPuzzle
//
//  Created by PRO on 2018-03-05.
//  Copyright © 2018 AIR. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int find_Comb(int target,int S[],int size);

int main(int argc, const char * argv[]) {
    
    ifstream fi(argv[1]);

    if(!fi){
        cout<<"We cannot open your input file; try again later; bye;"<<endl;
        return -1;
    }
    
    ofstream fo(argv[2]);
    
    if(!fo){
        cout<<"We cannot open your output file; try again later; bye;"<<endl;
        return -1;
    }
    int size;
    int N;
    fi>>N;
    
    for(int i=0;i<N;++i){
        
        fi>>size;
        int S[size];
   
        for(int i = 0; i < size; i ++){
            fi >> S[i];
        }
        
        int target;
        fi>>target;
        
        //the optimal solution of number N
        int number[80000 + 1];
        
        //if the solution consist of "+" operation
        int flag[80000 + 1];
        
        //if N counld be presented by the given digits and the length
        int aFlag[80000 + 1];
    
        for(int i = 1;i <= target; i ++){
            number[i] = 50000;
            flag[i] = 0;
            aFlag[i] = 0;
        }

        //find all that counld be presented by the given digits
        for(int i = 1; i <= target; i ++){
            int min = find_Comb(i,S,size);
            if(min!=0){
                number[i] = min;
                flag[i] = 1;
                aFlag[i] = min;
            }
        }
        
        if(target == 0)
            number[target] = 1;

        for(int i = 1; i <= target; i ++){
            int m = 50000;
            for(int x = 1; x <= i; x ++){
                if(aFlag[x] != 0 && number[i - x] > 0){
                    int temp = aFlag[x] + 1 + number[i - x];
                    if(temp < m)
                        m = temp;
                }
            }
            
            for(int j = 0 ; j < size; j ++){
                
                int candidate1 = 50000;
                int candidate2 = 50000;
                
                if(i - S[j] >= 0){
                    if(i - S[j] == 0){
                        number[i] = 1;
                        flag[i] = 1;
                    }
                    else{
                        if(number[i - S[j]] > 0 && number[i - S[j]] != 50000 && S[j] != 0){
                            candidate1 = number[i - S[j]] + 2;
                            if(candidate1 > m)
                                candidate1 = m;
                        }
                    }
                    
                }

                if(S[j] != 0){
                    if((i % S[j]) == 0 && number[i/S[j]] > 0 && flag[i/S[j]] == 1){
                        candidate2 = number[i/S[j]] + 2;
                        if(candidate2 > m)
                            candidate2 = m;
                    }
                }
                if(candidate1 < candidate2){
                    if (number[i] > candidate1){
                        number[i] = candidate1;
                        flag[i] = 0;
                    }
                    
                }
                else if(candidate1 > candidate2){
                    if (number[i] > candidate2){
                        number[i] = candidate2;
                        flag[i] = 1;
                    }
                }
                
                else{
                    //if(candidate2 != 2000)
                        //number[i] = candidate2;
                }
            }
        }
        
        if(number[target] == 50000)
            fo<<'N'<<endl;
        else
            fo<<number[target]<<endl;
    }
    
    return 0;
}

//to find the number that counld be presented by the given digits
int find_Comb(int target,int S[],int size){
    
    int length  = 0;

    string res;
    stringstream ss;
    
    ss<<target;
    ss>>res;
    
    for(int i = 0; i < res.length();i ++){
        bool find = false;
        int res1;
        stringstream ss1;
        ss1<<res[i];
        ss1>>res1;
        for(int j = 0;j < size;j ++){
            if(res1 == S[j])
                find = true;
        }
        if(!find)
            return 0;
    }
    length = res.length();
    return length;
}

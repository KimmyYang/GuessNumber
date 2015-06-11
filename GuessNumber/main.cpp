//
//  main.cpp
//  GuessNumber
//
//  Created by Kimmy on 2015/4/20.
//  Copyright (c) 2015年 Kimmy. All rights reserved.
//

#include <iostream>
#include <list>
#include <assert.h>
#include "TypeDef.h"
#include "Answer.h"

using namespace std;
/*
Create the answer set
Range from 0A1B ~ 3A1B
 
Every XAXB will create(new) a object(class Answer) and store the answer set's size in it
*/
bool prepare(AnswerSet &ansSet , AnswerVector** pAnswerVector){
    
    int a=0,b=0;
    Answer *pAns = NULL;
    
    for(a=0;a<=BASE_NUMBER_SIZE;++a){
        for(b=0;b<=BASE_NUMBER_SIZE;++b){
#if(DEBUG_ENABLE)
            if(a!=_A || b!=_B)continue;
            cout<<"a = "<<a<<" b = "<<b<<endl;
#endif
            
            if(a==0&&b==0)continue;
            else if(a+b>4)break;
            
            pAns = new Answer(a,b);//new the object
            *pAnswerVector = pAns->genInitAnswer();//initial
            ansSet.push_back(pAns);//store all the object in ansSet
        }
    }
    if(ansSet.empty() || *pAnswerVector==NULL)return false;
    
    cout<<"Total create "<<ansSet.size()<<" answer set"<<endl;
    return true;
}
/*
check the user answer,
if ans is invaild , then ignore the ans.
*/
bool isVaildValue(int value){
    
    int unit_1 = (value/1)%10;
    int unit_10 = (value/10)%10;
    int unit_100 = (value/100)%10;
    int unit_1000 = (value/1000)%10;

    if(unit_1!=unit_10 && unit_1!=unit_100 && unit_1!=unit_1000 && unit_10!=unit_100 && unit_10!=unit_1000 && unit_100!=unit_1000 && value<10000){
        return true;
    }
    cout<<"Invaild Value."<<endl;
    return false;
}
/*
 generate the base vector
*/
void genBaseVector(int value, BaseVector& baseVector){

    baseVector[0] = (value/1)%10;
    baseVector[1] = (value/10)%10;
    baseVector[2] = (value/100)%10;
    baseVector[3] = (value/1000)%10;
#if(DEBUG_ENABLE)
    cout<<"value = "<<baseVector[3]<<baseVector[2]<<baseVector[1]<<baseVector[0]<<endl;
#endif
}
/*
 check user's answer is correct or not
*/
bool isCorrect(BaseVector& userAns , BaseVector *pBase){
 if(userAns[0]==pBase->at(0) &&
    userAns[1]==pBase->at(1) &&
    userAns[2]==pBase->at(2) &&
    userAns[3]==pBase->at(3))
     return true;
    return false;
}
/*
 compare computer's answer
*/
bool Compare(BaseVector &userSecretVector , BaseVector &comGuessVector)
{
    int a_Count=0,b_Count=0;
    for (int i=0; i<4; i++){
        if (userSecretVector[i]==comGuessVector[i]){
            a_Count=a_Count+1;
        }	}
    for(int i=0; i<4; i++){
        if (userSecretVector[i]!=comGuessVector[i]){
            for(int j=0; j<4; j++){
                if(i!=j && userSecretVector[i]==comGuessVector[j]){
                    b_Count=b_Count+1;
                }	}	}	}
    if(a_Count==4 && b_Count==0){
        printf("[User Respond] Answer Correct! %iA%iB\n", a_Count, b_Count);
        return true;
    }
    else printf("[User Respond] %iA%iB\n", a_Count, b_Count);
    return false;
}
void ComputerGuess(BaseVector &comGuessVector){

    srand(time(NULL));
    do{comGuessVector[0]=rand()%10;
    }while(comGuessVector[0]==0);
    do{comGuessVector[1]=rand()%10;
    }while(comGuessVector[1]==comGuessVector[0]);
    do{comGuessVector[2]=rand()%10;
    }while(comGuessVector[2]==comGuessVector[1]||comGuessVector[2]==comGuessVector[0]);
    do{comGuessVector[3]=rand()%10;
    }while(comGuessVector[3]==comGuessVector[2]||comGuessVector[3]==comGuessVector[1]||comGuessVector[3]==comGuessVector[0]);
    for(int i=0; i<4; i++){
        printf("%i", comGuessVector[i]);
    }
    printf("\n");
}
int main(int argc, const char * argv[]) {

    cout<<"debug mode : "<<DEBUG_ENABLE<<endl;

    AnswerSet ansSet;
    bool isFind = false , isInit = true;
    int userAns = 0,userSecret=0 ,round = 0 ;
    size_t nMaxAnsSet = 0;
    Answer *pAns = NULL , *_pAns = NULL;
    AnswerVector *pAnswerVector = NULL;
    BaseVector userAnsVector , userSecretVector , comAnsVector;
    userAnsVector.resize(BASE_NUMBER_SIZE);
    userSecretVector.resize(BASE_NUMBER_SIZE);
    comAnsVector.resize(BASE_NUMBER_SIZE);
    
    /* prepare the answer set */
    cout<<"prepare ..."<<endl;
    if(!prepare(ansSet, &pAnswerVector)){
        cout<<"prepare fail ..."<<endl;
        assert(false);
    }
    
    cout<<"======================="<<endl;
    
    /* enter user secret number */
    do{
        cout<<"Please enter your secret number : ";
        cin>>userSecret;
    }while (!isVaildValue(userSecret));
#if(DEBUG_ENABLE)
    cout<<"userSecret = "<<userSecret<<endl;
#endif
    genBaseVector(userSecret, userSecretVector);
    
    cout<<"Computer create its own secret number : "<<"XXXX"<<endl;
    cout<<"Start the game ..."<<endl;
    cout<<"======================="<<endl;
    
    while(!isFind){
        ++round;
        cout<<"[Round "<<round<<"]"<<endl;
        do{
           cout<<"[User Guess] please enter the answer :";
           cin>>userAns;
        }while(!isVaildValue(userAns));
        genBaseVector(userAns,userAnsVector);
        
        AnswerSet::iterator itor = ansSet.begin();
        nMaxAnsSet = 0; _pAns = NULL;
        
        for(;itor!=ansSet.end();++itor){
            pAns = *itor;
            if(!pAns){
                cout<<"Internal Error : Null Answer ..."<<endl;
                assert(false);
            }
            if(isInit){//1st, will return 0A1B ans set
                if(!pAns->match(0,1))continue;
                pAns->updateAnswerSize(userAnsVector , pAnswerVector);//update answer size
                pAns->filterAnswer(userAnsVector , pAnswerVector);//filter the answer, and update the answer vector

                if(!pAnswerVector){
                    cout<<"Internal Error : Answer Vector is null ..."<<endl;
                    assert(false);
                }
                isInit = false;
                _pAns = pAns;
                break;
            }else{
                pAns->updateAnswerSize(userAnsVector , pAnswerVector);//update answer size
                if(!pAnswerVector){
                    cout<<"Internal Error : Answer Vector is null ..."<<endl;
                    assert(false);
                }
                /*
                 find the max anwser size, and will be the answer
                */
                if(pAns->getAnsSetSize() > nMaxAnsSet){
                    nMaxAnsSet = pAns->getAnsSetSize();
                    _pAns = pAns;
                }
            }
        }
        if(!_pAns){
            cout<<"Internal Error : _pAns is null ..."<<endl;
            assert(false);
        }
        /*
         filter the answer, and updated the answer vector
         */
        if(pAnswerVector->size()>1)_pAns->filterAnswer(userAnsVector , pAnswerVector);
        cout<<"[Computer Respond] "<<_pAns->getA()<<"A"<<_pAns->getB()<<"B"<<endl;
        /*
         remain only one answer
        */
        if(pAnswerVector->size() == 1){
            BaseVector *pBase = pAnswerVector->at(0);
            if(isCorrect(userAnsVector, pBase)){
                cout<<"[Computer Respond] Correct !! The answer is : "<<pBase->at(3)<<pBase->at(2)<<pBase->at(1)<<pBase->at(0)<<endl;
                isFind = true;
            }
        }
        /*
         computer guess
        */
        cout<<"[Computer Guess] auto enter the answer : ";
        ComputerGuess(comAnsVector);
        if(Compare(userSecretVector, comAnsVector))isFind=true;//compare computer's answer
        cout<<endl;
        
    }
    return 0;
}


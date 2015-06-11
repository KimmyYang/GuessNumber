//
//  Answer.cpp
//  GuessNumber
//
//  Created by Kimmy on 2015/4/20.
//  Copyright (c) 2015年 Kimmy. All rights reserved.
//
/*
This class is store for the xAxB object

*/

#include "Answer.h"
#include <iostream>
#include <assert.h>
using namespace std;

void Answer::CleanBaseVector(AnswerVector *pAnswerVector){
    
    AnswerVector::iterator Itor;
    BaseVector *pBase = NULL;
    for(Itor=pAnswerVector->begin();Itor!=pAnswerVector->end();){
        pBase = *Itor;
        if(pBase)delete pBase;
        else ++Itor;
    }
    if(!pAnswerVector->empty()){
        cout<<"Internal Error : Clean Base Vector error ..."<<endl;
        assert(false);
    }
}
/*
init the answer vector, 
put all the non-duplicate numbers in it
*/
AnswerVector* Answer::genInitAnswer(){
    AnswerVector *pAnsVector = NULL;
    
    int i=0,unit_1=0,unit_10=0,unit_100=0,unit_1000=0;
    pAnsVector = new AnswerVector();//new
    BaseVector *baseVec = NULL;
    
    for(i=0;i<10000;i++){
        unit_1 = (i/1)%10;
        unit_10 = (i/10)%10;
        unit_100 = (i/100)%10;
        unit_1000 = (i/1000)%10;
        if(unit_1!=unit_10 && unit_1!=unit_100 && unit_1!=unit_1000 && unit_10!=unit_100 && unit_10!=unit_1000 && unit_100!=unit_1000){
            baseVec = new BaseVector();
            baseVec->resize(BASE_NUMBER_SIZE);
            baseVec->at(0) = unit_1;
            baseVec->at(1) = unit_10;
            baseVec->at(2) = unit_100;
            baseVec->at(3) = unit_1000;
#if(DEBUG_ENABLE)
            if(unit_1==_unit1 && unit_10==_unit10 && unit_100==_unit100 && unit_1000==_unit1000)
                cout<<"find "<<unit_1<<unit_10<<unit_100<<unit_1000<<endl;
#endif
            pAnsVector->push_back(baseVec);
        }
    }
#if(DEBUG_ENABLE)
    if(pAnsVector->empty()){
        cout<<"Internal Error"<<endl;
        assert(false);
    }
#endif
    setAnsSetSize(pAnsVector->size());
    return pAnsVector;
}
/*
clean the non-match base vector's answer
*/
void Answer::CleanNonMatchAnswer(AnswerVector *pAnsVecotr){
    
    AnswerVector::iterator itor;
    BaseVector *pBaseVec = NULL;
    
    for(itor=pAnsVecotr->begin(); itor!=pAnsVecotr->end();){
        
        pBaseVec = *itor;
#if(DEBUG_ENABLE)
        //PrintBaseVector(pBaseVec);
#endif
        if(pBaseVec->empty() && pBaseVec){
            pAnsVecotr->erase(itor);
            if(!pBaseVec)delete pBaseVec;
            if(!getAnsSetSize())break;
        }
        else ++itor;
    }
}
/*
update the answer size
*/
void Answer::updateAnswerSize(const BaseVector &userAns , AnswerVector *pAnsVector){
    
    int a = 0 , b = 0, num = 0 , i = 0, j = 0, k = 0 , nNonMatchCnt = 0;
    BaseVector *pBaseVec = NULL;
    size_t nAnsVecSize = pAnsVector->size();
#if(DEBUG_ENABLE)
    cout<<"Before , "<<m_A<<"A"<<m_B<<"B : "<<getAnsSetSize()<<endl;
#endif
    for(i=0; i<nAnsVecSize; ++i){
        a = 0; b = 0;
        pBaseVec = pAnsVector->at(i);
        if(!pBaseVec){
            cout<<"BaseVector is NULL ..."<<endl;
            assert(false);
        }
        
        for(j=0; j<BASE_NUMBER_SIZE; ++j){
            num = pBaseVec->at(j);
            for(k=0; k<BASE_NUMBER_SIZE; ++k){
                
                if(num==userAns[k]){
                    if(j==k)++a;
                    else ++b;
                }
            }//for end
        }//for end
        if(a!= m_A || b!=m_B){
            ++nNonMatchCnt;
        }
    }
#if(DEBUG_ENABLE)
    if(pAnsVector->size() < nNonMatchCnt){
        cout<<"Interal Error"<<endl;
        assert(false);
    }
#endif
    setAnsSetSize(pAnsVector->size()-nNonMatchCnt);//update the answer size
#if(DEBUG_ENABLE)
    cout<<"After , "<<m_A<<"A"<<m_B<<"B : "<<getAnsSetSize()<<endl;
#endif
}
/*
 filter the proper answer, and clean the non-match answer
*/
void Answer::filterAnswer(const BaseVector &userAns , AnswerVector *pAnsVector){
    
    int a = 0 , b = 0, num = 0 , i = 0, j = 0, k = 0 , nNonMatchCnt = 0;
    BaseVector *pBaseVec = NULL;
    size_t nAnsVecSize = pAnsVector->size();
#if(DEBUG_PRINT_ENABLE)
    cout<<"Before , "<<m_A<<"A"<<m_B<<"B : "<<getAnsSetSize()<<endl;
#endif
    for(i=0; i<nAnsVecSize; ++i){
        a = 0; b = 0;
        pBaseVec = pAnsVector->at(i);
        if(!pBaseVec){
            cout<<"Internal Error : BaseVector is NULL ..."<<endl;
            assert(false);
        }
        
        for(j=0; j<BASE_NUMBER_SIZE; ++j){
            num = pBaseVec->at(j);
            for(k=0; k<BASE_NUMBER_SIZE; ++k){
                
                if(num==userAns[k]){
                    if(j==k)++a;
                    else ++b;
                }
            }//for end
        }//for end
        if(a!= m_A || b!=m_B){
            ++nNonMatchCnt;
            pBaseVec->clear();
        }
    }
#if(DEBUG_ENABLE)
    if(pAnsVector->size() < nNonMatchCnt){
        cout<<"Interal Error"<<endl;
        assert(false);
    }
#endif
    CleanNonMatchAnswer(pAnsVector);//clean non-match anser
    setAnsSetSize(pAnsVector->size());//update the answer size
#if(DEBUG_ENABLE)
    cout<<"pAnsVector size = "<<pAnsVector->size()<<" nNonMatchCnt = "<<nNonMatchCnt<<endl;
    cout<<"After , "<<m_A<<"A"<<m_B<<"B : "<<getAnsSetSize()<<endl;
#endif
}

bool Answer::match(int a, int b){
    if(m_A == a && m_B == b)return true;
    return false;
}
/*
use for debug
*/
void Answer::PrintBaseVector(BaseVector* pBase){
    
    if(!pBase || pBase->empty()){
        return;
    }
    
    BaseVector::reverse_iterator rItor =pBase->rbegin();
    BaseVector::reverse_iterator rItEnd =pBase->rend();
    
    cout<<"Base Value = ";
    for(;rItor!=rItEnd;++rItor){
        cout<<*rItor;
    }
    cout<<endl;
    
}

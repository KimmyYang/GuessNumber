//
//  Answer.h
//  GuessNumber
//
//  Created by Kimmy on 2015/4/20.
//  Copyright (c) 2015年 Kimmy. All rights reserved.
//

#ifndef __GuessNumber__Answer__
#define __GuessNumber__Answer__

#include <stdio.h>
#include "TypeDef.h"

class Answer{
 
public:
    Answer(int a , int b){
        //constructor ..
        m_A = a;
        m_B = b;
        m_AnsSetSize = 0;
    }
    virtual ~Answer(){
    //nothig to do
    }
    
    AnswerVector* genInitAnswer();
    void filterAnswer(const BaseVector& ,AnswerVector *);
    void updateAnswerSize(const BaseVector& ,AnswerVector *);
    size_t getAnsSetSize(){return m_AnsSetSize;}
    void setAnsSetSize(size_t size){m_AnsSetSize = size;}
    bool match(int,int);
    int getA(){return m_A;}
    int getB(){return m_B;}
private:
    void CleanNonMatchAnswer(AnswerVector*);
    void CleanBaseVector(AnswerVector *);
    void PrintBaseVector(BaseVector*);
    int m_A;
    int m_B;
    size_t m_AnsSetSize;
};

#endif /* defined(__GuessNumber__Answer__) */

//
//  TypeDef.h
//  GuessNumber
//
//  Created by Kimmy on 2015/4/20.
//  Copyright (c) 2015年 Kimmy. All rights reserved.
//

#ifndef GuessNumber_TypeDef_h
#define GuessNumber_TypeDef_h
#include <stdio.h>
#include <vector>
#include <list>

/*
 use for debug
*/
#define DEBUG_ENABLE 0
#if(DEBUG_ENABLE)
#define _A 0
#define _B 1
#define _unit1      1
#define _unit10     2
#define _unit100    3
#define _unit1000   5
#endif


/*
 structure of the AnswerVector : [BaseVector] -> [0~9][0~9][0~9][0~9]
 
 so every BaseVector only resize to 4 (only store 4 number in it)
 but AnswerVector store more than one BaseVector in it
 
 if AnswerVector size = 1, then the remaining BaseVector is the final anwser
*/
#define BASE_NUMBER_SIZE 4
class Answer;
typedef std::vector<int> BaseVector;
typedef std::vector<BaseVector*> AnswerVector;
typedef std::list<Answer*> AnswerSet;


#endif

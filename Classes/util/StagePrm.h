#ifndef __STAGEPRM_H__
#define __STAGEPRM_H__

#include "cocos2d.h"
USING_NS_CC;

struct StagePrm {

    int _stageNum;
    std::string _comment;
    float timeLimit_;
    
    StagePrm(){
        _stageNum=0;
        _comment="";
        timeLimit_=0;
    }
};

#endif

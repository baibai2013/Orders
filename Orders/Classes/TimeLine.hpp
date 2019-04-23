//
//  TimeLine.hpp
//  Orders
//
//  Created by li on 2019/4/23.
//

#ifndef TimeLine_hpp
#define TimeLine_hpp
#include "cocos2d.h"
#include "base/CCProtocols.h"
#include <vector>
NS_CC_BEGIN
class CC_DLL TimeLine : public cocos2d::LayerColor
{
public:
    static TimeLine * create(const Color4B& color, GLfloat width, GLfloat height);
    void updateView();
CC_CONSTRUCTOR_ACCESS:
    TimeLine();
    virtual ~TimeLine();
    bool initWithColor(const Color4B& color, GLfloat width, GLfloat height);
    
protected:
    DrawNode* drawNode;
    
public:
    const float cxl_heigh_scale = 0.4;
    
    CC_SYNTHESIZE(std::vector<char*>,mData,Mdata);
};
NS_CC_END
#endif /* TimeLine_hpp */

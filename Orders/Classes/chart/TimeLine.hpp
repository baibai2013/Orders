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
#include "../model/TimeLineModel.hpp"
#include <vector>
NS_CC_BEGIN
class CC_DLL TimeLine : public cocos2d::LayerColor
{
public:
    static TimeLine * create(const Color4B& color, GLfloat width, GLfloat height);
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    TimeLine();
    virtual ~TimeLine();
protected:
     void onDraw(const Mat4& transform, uint32_t flags);
    
CC_CONSTRUCTOR_ACCESS:
    bool initWithColor(const Color4B& color, GLfloat width, GLfloat height);
   
protected:
    DrawNode* drawNode;
    CustomCommand _customCommand;
public:
    const float cxl_heigh_scale = 0.4;
    CC_SYNTHESIZE(TimeLineModel*,mData,Mdata);
};
NS_CC_END
#endif /* TimeLine_hpp */

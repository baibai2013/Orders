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
    Vec2 timeMapToPos(std::string time,float value);
    void initDraw();
CC_CONSTRUCTOR_ACCESS:
    bool initWithColor(const Color4B& color, GLfloat width, GLfloat height);
   
protected:
    DrawNode* drawNode;
    CustomCommand _customCommand;
public:
    const float cxl_heigh_scale = 0.4;
    const float padingTop = 20 ,padingBottom = 20;
    const float padingLeft = 60 , padingRight = 60;
    float cjlHeight;
    float timeLineHeight;
    float timeLineWidth;
    float timeLineMaxValue;
    float timeLineMinValue;
    Vec2 cjlStartPos;
    Vec2 timeLineStartPos;
    Vec2 timeLineStep;
    Vec2 cjlStep;
    
    CC_SYNTHESIZE(TimeLineModel*,mData,Mdata);
    CC_SYNTHESIZE(bool,redraw,MRedraw);
};
NS_CC_END
#endif /* TimeLine_hpp */

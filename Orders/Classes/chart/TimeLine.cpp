//
//  TimeLine.cpp
//  Orders
//
//  Created by li on 2019/4/23.
//

#include "TimeLine.hpp"

USING_NS_CC;


TimeLine::TimeLine(){
    
}

TimeLine::~TimeLine(){
    
}

TimeLine* TimeLine::create(const Color4B &color, GLfloat width, GLfloat height)
{
    TimeLine * layer = new (std::nothrow) TimeLine();
    if( layer && layer->initWithColor(color,width,height))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool TimeLine::initWithColor(const Color4B &color, GLfloat width, GLfloat height)
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(color, width, height) )
    {
        return false;
    }
    
    auto s = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
   
    drawNode = DrawNode::create();
    addChild(drawNode);
    //draw a solid rectangle
//    draw->drawSolidRect(Vec2(10,10), Vec2(200,200), Color4F(1,1,0,1));
    
    // Draw polygons
//    Vec2 points[] = { Vec2(s.height/4,0), Vec2(s.width,s.height/5), Vec2(s.width/3*2,s.height) };
//    draw->drawPolygon(points, sizeof(points)/sizeof(points[0]), Color4F(1,0,0,0.5), 4, Color4F(0,0,1,0.5));
    // star poly (triggers buggs)
//    {
//        const float o=80;
//        const float w=20;
//        const float h=50;
//        Vec2 star[] = {
//            Vec2(o+w,o-h), Vec2(o+w*2, o),                        // lower spike
//            Vec2(o + w*2 + h, o+w ), Vec2(o + w*2, o+w*2),        // right spike
//                          {o +w, o+w*2+h}, {o,o+w*2},                 // top spike
//                          {o -h, o+w}, {o,o},                         // left spike
//        };
//
//        draw->drawPolygon(star, sizeof(star)/sizeof(star[0]), Color4F(1,0,0,0.5), 1, Color4F(0,0,1,1));
//    }
    
  
    
    
    return true;
}


void TimeLine::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder, transform, flags);
    _customCommand.func = CC_CALLBACK_0(TimeLine::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void TimeLine::onDraw(const Mat4& transform, uint32_t /*flags*/)
{
    if(redraw) return;
    
    drawNode->clear();
    
    auto size = getContentSize();
    auto padingTop = 20 ,padingBottom = 20;
    auto padingLeft = 50 , padingRight = 50;
    
    //成交量图高
    auto cjlHeight = (size.height - (padingTop+padingBottom) * 2) * cxl_heigh_scale;
    //时分图高
    auto timeLineHeight = size.height - cjlHeight;
    
    auto oneTimeLineHeight = timeLineHeight / 5;
    //绘制背景表格
    {
        //横线
        for(int i=0;i<5;i++){
            drawNode->drawLine(Vec2(padingLeft, size.height - (padingTop + oneTimeLineHeight * i)), Vec2(size.width-padingRight,size.height -( padingTop + oneTimeLineHeight * i)), Color4F::GRAY);
        }
        //竖线
        drawNode->drawLine(Vec2(padingLeft,size.height - padingTop), Vec2(padingLeft,size.height-(padingTop+ oneTimeLineHeight * 4 )), Color4F::GRAY);
        
        drawNode->drawLine(Vec2(size.width - padingRight ,size.height - padingTop), Vec2(size.width - padingRight ,size.height-(padingTop+ oneTimeLineHeight * 4 )), Color4F::GRAY);
    }
    
    
    {
        //坐标
        float stepYAlxis = (mData->todayMaxPrice-mData->yesterdayEndPrice) / 2;
        char s[20];
        for(int i=0;i<5;i++){
          
            float value = mData->todayMaxPrice - stepYAlxis * i;
            float percent = value  / mData->yesterdayEndPrice;
            
            //左边y轴
            sprintf(s, "%.2f",value);
            auto label =  Label::createWithSystemFont(std::string(s), "Avenir Next", 16,Size(padingLeft, 32), TextHAlignment::CENTER);
            addChild(label);
            label->setPosition(Vec2(padingLeft/2, size.height - (padingTop + oneTimeLineHeight * i)));
            
            
            //右边y轴
            sprintf(s, "%.2f",percent);
            label =  Label::createWithSystemFont(std::string(s), "Avenir Next", 16,Size(padingLeft, 32), TextHAlignment::CENTER);
            addChild(label);
            label->setPosition(Vec2(size.width-padingRight, size.height - (padingTop + oneTimeLineHeight * i)));
        }
        
    }
    
    
    redraw = true;
   
}


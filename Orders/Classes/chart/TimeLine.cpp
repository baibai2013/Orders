//
//  TimeLine.cpp
//  Orders
//
//  Created by li on 2019/4/23.
//

#include "TimeLine.hpp"
#include <iostream>
#include "../three/Utils.hpp"
#include "../model/TimeLineModel.hpp"
USING_NS_CC;


TimeLine::TimeLine():redraw(true){
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
    
    auto size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
   
    drawNode = DrawNode::create();
    addChild(drawNode);
    
    //成交量图高
    cjlHeight = (size.height - (padingTop+padingBottom) * 2) * cxl_heigh_scale;
    //时分图高
    timeLineHeight = size.height - cjlHeight;
    
    timeLineWidth = size.width-padingRight-padingLeft;
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
    if(redraw){
        _customCommand.init(_globalZOrder, transform, flags);
        _customCommand.func = CC_CALLBACK_0(TimeLine::onDraw, this, transform, flags);
        renderer->addCommand(&_customCommand);
        redraw = false;
    }
}

Vec2 TimeLine::timeMapToPos(std::string time,float value)
{

    int numberX = Utils::stringToMinute("%2d%2d",time)-Utils::stringToMinute("%2d%2d", "0930");
    float numberY = (value - timeLineMinValue) * 100;
    return Vec2(timeLineStep.x * numberX,timeLineStep.y * numberY) + timeLineStartPos;
}

void TimeLine::initDraw()
{
//    Vec2 cjlStartPos;
//    Vec2 timeLineStartPos;
//    Vec2 timeLineStep;
//    Vec2 cjlStep;
    auto size = getContentSize();
    timeLineStartPos.set(padingLeft, size.height - padingTop-timeLineHeight);
    
    if(mData == nullptr) return;
    
    int totalNumberX = Utils::stringToMinute("%2d%2d", "1500")-Utils::stringToMinute("%2d%2d", "0930");
    float timeLineStepX = timeLineWidth / totalNumberX;
    if(fabs(mData->todayMaxPrice - mData->yesterdayEndPrice) > fabs(mData->todayMinPrice-mData->yesterdayEndPrice)){
        timeLineMaxValue = mData->todayMaxPrice;
    }else {
        timeLineMaxValue =mData->yesterdayEndPrice + fabs(mData->todayMinPrice-mData->yesterdayEndPrice);
    }
    timeLineMinValue = timeLineMaxValue- ((timeLineMaxValue - mData->yesterdayEndPrice) * 2);
    float timeLineStepY = timeLineHeight /((timeLineMaxValue - timeLineMinValue) * 100);
    timeLineStep.set(timeLineStepX, timeLineStepY);
    
    
}

void TimeLine::onDraw(const Mat4& transform, uint32_t /*flags*/)
{
   
    initDraw();
    drawNode->clear();
    
    auto size = getContentSize();
 
    //绘制背景表格
    {
        auto oneTimeLineHeight = timeLineHeight / 4;
        //横线
        for(int i=0;i<5;i++){
            drawNode->drawLine(Vec2(padingLeft, size.height - (padingTop + oneTimeLineHeight * i)), Vec2(size.width-padingRight,size.height -( padingTop + oneTimeLineHeight * i)), Color4F::GRAY);
        }
        //竖线
        drawNode->drawLine(Vec2(padingLeft,size.height - padingTop), Vec2(padingLeft,size.height-(padingTop+ oneTimeLineHeight * 4 )), Color4F::GRAY);
        
        drawNode->drawLine(Vec2(size.width - padingRight ,size.height - padingTop), Vec2(size.width - padingRight ,size.height-(padingTop+ oneTimeLineHeight * 4 )), Color4F::GRAY);
        //y轴
        float stepYAxis = (mData->todayMaxPrice-mData->yesterdayEndPrice) / 2;
        char s[20];
        for(int i=0;i<5;i++){
          
            float value = mData->todayMaxPrice - stepYAxis * i;
            float percent = (value - mData->yesterdayEndPrice )/mData->yesterdayEndPrice;
            
            
            //左边y轴
            sprintf(s, "%.2f",value);
            auto label =  Label::createWithSystemFont(std::string(s), "Avenir Next", 16,Size(padingLeft, 32), TextHAlignment::CENTER);
            addChild(label);
            label->setPosition(Vec2(padingLeft/2, size.height - (padingTop + oneTimeLineHeight * i)));
            
            
            //右边y轴
            sprintf(s, "%.2f",percent);
            label =  Label::createWithSystemFont(std::string(s)+"%", "Avenir Next", 16,Size(padingLeft, 32), TextHAlignment::CENTER);
            addChild(label);
            label->setPosition(Vec2(size.width-padingRight+padingRight/2, size.height - (padingTop + oneTimeLineHeight * i)));
            
        }
        
        //x轴
        std::vector<std::string> xAxisString{"09:30","10:30","11:30","14:00","15:00"};
        float stepXAxis = timeLineWidth / 4;
        for(int i=0;i<5;i++){
           auto label =  Label::createWithSystemFont(xAxisString[i], "Avenir Next", 16,Size(padingLeft, 32), TextHAlignment::CENTER);
            addChild(label);
            label->setPosition(Vec2(timeLineStartPos.x + stepXAxis * i, timeLineStartPos.y - padingTop));
        }
    }
    
    {
        //数据
        int size = mData->mData.size();
        auto actualPriceLine = PointArray::create(size);
        auto averagePriceLine = PointArray::create(size);
       
        for(int i=0;i<size;i++){
            TimeLinePoint* timeLinePoint = mData->mData[i];
            Vec2 pointActualPrice = timeMapToPos(timeLinePoint->time,timeLinePoint->actualPrice);
            Vec2 pointAveragePrice = timeMapToPos(timeLinePoint->time,timeLinePoint->averagePrice);
            actualPriceLine->addControlPoint(pointActualPrice);
            averagePriceLine->addControlPoint(pointAveragePrice);
        }
      
        if(actualPriceLine->count() > 0)
            drawNode->drawCardinalSpline(actualPriceLine,0.5f,50,Color4F(0.0f,0.0f,1.0f,1.0f));
        if(averagePriceLine->count() > 0)
            drawNode->drawCardinalSpline(averagePriceLine,0.5f,50,Color4F(1.0f,0.0f,0.0f,1.0f));
       
        
    }
    
    
    
   
}


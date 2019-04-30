//
//  TimeLineModel.hpp
//  Orders
//
//  Created by li on 2019/4/25.
//

#ifndef TimeLineModel_hpp
#define TimeLineModel_hpp

class TimeLinePoint{
public:
    TimeLinePoint();
    TimeLinePoint(std::string _time,float _actualPrice,float _averagePrice,float _volume);
public:
    std::string time;//日期
    float actualPrice;//当时价格
    float averagePrice;//均价
    float volume;//成交量
};


class TimeLineModel{
    
public:
    TimeLineModel();
public:
    std::string code;//代码
    std::string name;//名称
    std::vector<TimeLinePoint*> mData;
    float todayStartPrice;//开盘价格
    float yesterdayEndPrice;//昨天收盘价格
    float todayMaxPrice;//今日最高价
    float todayMinPrice;//今日最低价
    float todayMaxVolume;//今日最高成交量
};


#endif /* TimeLineModel_hpp */

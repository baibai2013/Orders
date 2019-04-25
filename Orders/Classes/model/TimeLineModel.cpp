//
//  TimeLineModel.cpp
//  Orders
//
//  Created by li on 2019/4/25.
//

#include "TimeLineModel.hpp"

TimeLineModel::TimeLineModel():
        code(""),
        name(""),
        yesterdayEndPrice(0.0f),
        todayMaxPrice(0.0f),
        todayMinPrice(0.0f),
        todayStartPrice(0.0f)
{}


TimeLinePoint::TimeLinePoint():
        time(""),
        actualPrice(0.0f),
        averagePrice(0.0f),
        volume(0.0f)
{}

TimeLinePoint::TimeLinePoint(std::string _time,
                             float _actualPrice,
                             float _averagePrice,
                             float _volume)
{
    time = _time;
    actualPrice = _actualPrice;
    averagePrice = _averagePrice;
    volume = _volume;
}

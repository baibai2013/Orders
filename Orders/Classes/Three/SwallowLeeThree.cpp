//
//  SwallowLeeThree.cpp
//  Orders
//
//  Created by li on 2019/4/25.
//

#include <iostream>

#include "SwallowLeeThree.hpp"
#include "../lib/csv.h"
#include "Utils.hpp"


TimeLineModel* SwallowLeeThree::getTimeLineData(std::string todayTime){
    std::string basePath ="/Users/li/Documents/workspace/c++/Orders/Orders/Resources/data/";
    std::string time;float actualPrice;float volume;
    
    auto timeLineModel = new TimeLineModel();
    io::CSVReader<3> inYesterday(basePath+Utils::yesterdayString(todayTime)+".csv");
    inYesterday.read_header(io::ignore_extra_column,"time", "actualPrice","volume");
    while (inYesterday.read_row(time,actualPrice,volume)) {
    }
    timeLineModel->yesterdayEndPrice = actualPrice;
    
    io::CSVReader<3> in(basePath+todayTime+".csv");
    in.read_header(io::ignore_extra_column,"time", "actualPrice","volume");
   
    std::vector<TimeLinePoint*> data;
    
    float totalPrice=0.0f,totalVolume=0.0f;
    in.read_row(time,actualPrice,volume);
    timeLineModel->todayStartPrice = actualPrice;
    while (in.read_row(time,actualPrice,volume)) {
        printf("%s,%.2f,%.2f\n",time.c_str(),actualPrice,volume);
        auto timeLinePoint = new TimeLinePoint(time,actualPrice,0.0f,volume);
        totalPrice += actualPrice;
        totalVolume += volume;
        timeLinePoint->averagePrice = totalPrice / totalVolume;
        timeLineModel->todayMaxPrice = std::max(timeLineModel->todayMaxPrice, actualPrice);
        timeLineModel->todayMinPrice = std::min(timeLineModel->todayMinPrice, actualPrice);
        data.push_back(timeLinePoint);
    }
    
    return timeLineModel;
}

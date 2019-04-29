//
//  Utils.cpp
//  Orders
//
//  Created by li on 2019/4/25.
//

#include "Utils.hpp"
std::string Utils::yesterdayString(std::string today){
    time_t tm = Utils::stringToTime("%4d%2d%2d", today);
    tm -= 60*60*24;
    return Utils::timeToString("%s%s%s", tm);
}

std::string Utils::timeToString(std::string format,time_t time){
    
    tm *tm_ = localtime(&time);
    int year, month, day, hour=0, minute=0, second=0;
    year = tm_->tm_year+ 1900;
    month = tm_->tm_mon + 1;
    day = tm_->tm_mday;
    hour = tm_->tm_hour;
    minute = tm_->tm_min;
    second = tm_->tm_sec;
    char yearStr[5], monthStr[3], dayStr[3], hourStr[3], minuteStr[3], secondStr[3];
    sprintf(yearStr, "%d", year);
    sprintf(monthStr, "%d", month);
    if(monthStr[1] == '\0'){
        monthStr[2] = '\0';
        monthStr[1] = monthStr[0];
        monthStr[0] = '0';
    }
    sprintf(dayStr, "%d", day);
    if(dayStr[1] == '\0'){
        dayStr[2] = '\0';
        dayStr[1] = dayStr[0];
        dayStr[0] = '0';
    }
    sprintf(hourStr, "%d",hour);
    if(hourStr[1] == '\0'){
        hourStr[2] = '\0';
        hourStr[1] = hourStr[0];
        hourStr[0] = '0';
    }
    sprintf(minuteStr,"%d",minute);
    if(minuteStr[1] == '\0'){
        minuteStr[2] = '\0';
        minuteStr[1] = minuteStr[0];
        minuteStr[0] = '0';
    }
    sprintf(secondStr, "%d",second);
    if(secondStr[1] == '\0'){
        secondStr[2] = '\0';
        secondStr[1] = secondStr[0];
        secondStr[0] = '0';
    }
    
    char s[20];
    if(format == "%s%s%s"){
         sprintf(s, format.c_str(),yearStr,monthStr,dayStr);
    }else if(format == "%s%s%s%s%s%s"){
        sprintf(s, format.c_str(),yearStr,monthStr,dayStr,hourStr,minuteStr,secondStr);
    }
    
    std::string str(s);
    return str;
}

time_t Utils::stringToTime(std::string format,std::string str){
    tm _tm;
    int year, month, day, hour=0, minute=0, second=0;
    sscanf(str.c_str(), format.c_str(), &year, &month, &day,&hour,&minute,&second);
    _tm.tm_year = year - 1900;
    _tm.tm_mon = month - 1;
    _tm.tm_mday = day;
    _tm.tm_hour = hour;
    _tm.tm_min = minute;
    _tm.tm_sec = second;
    _tm.tm_isdst = 0;
    time_t _time_t = mktime(&_tm);
    return _time_t;
}


int Utils::stringToMinute(std::string format,std::string str){
    int  hour=0, minute=0;
    sscanf(str.c_str(), format.c_str(), &hour,&minute);
    return hour*60+minute;
}

//
//  Utils.hpp
//  Orders
//
//  Created by li on 2019/4/25.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>
#include <ctime>
class Utils{
public:
    static std::string yesterdayString(std::string today);
    static std::string timeToString(std::string format,time_t time);
    static time_t stringToTime(std::string format,std::string str);
};
#endif /* Utils_hpp */

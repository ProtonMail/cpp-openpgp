#include <openpgp/pgptime.h>

// get current time since epoch
time_t now(){
    time_t rawtime;
    time(&rawtime);
    return rawtime;
}

// write a time in seconds from epoch to string
std::string show_time(time_t T){
    // value to string conversion
    struct tm * gmt = gmtime(&T);
    std::stringstream date;
    // convert to string. could use asctime, but needed a bit more info
    date << dayofweek[gmt -> tm_wday] << " " << month[gmt -> tm_mon] << " " << gmt -> tm_mday << " " << gmt -> tm_hour << ":" << gmt -> tm_min << ":" << gmt -> tm_sec << " UTC " << (1900 + gmt -> tm_year);
    return date.str();
}

std::string show_date(time_t T){
    struct tm * gmt = gmtime(&T);
    std::stringstream date;
    date << (1900 + gmt -> tm_year) << "-" << (gmt -> tm_mon + 1) << "-" << gmt -> tm_mday;
    return date.str();
}


time_t get_utc(int year, int month, int day, int hour, int minute, int second) {
    tm in;
    in.tm_year = year - 1900;
    in.tm_mon  = month - 1;
    in.tm_mday = day;
    in.tm_hour = hour;
    in.tm_min  = minute;
    in.tm_sec  = second;
    time_t result = mktime(&in); // generate by local timezone
    
    // detect timezone
    int utc = 0, local = 0;
    tm *tmp;
    tmp = gmtime(&result);
    utc = tmp->tm_hour;
    tmp = localtime(&result);
    local = tmp->tm_hour;
    if ( utc != local ) {
        int diff = local - utc;
        if ( diff < 0 && diff < -12 ) {
            diff += 24;
        } else if (diff > 0 && diff > 12) {
            diff -= 24;
        }
        result += diff*60*60;
    }
    return result;
}


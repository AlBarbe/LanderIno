//-------------------------------------------------------------------------------------------------------------//
//----- Class to easy acces data and time from internal clock, updated to present time from an ntp server -----//
//-------------------------------------------------------------------------------------------------------------//

#ifndef __My_Time_Config__
#define __My_Time_Config__

#include <Arduino.h>
#include <time.h>

class MyClock {

    public:
        //initzializer
        MyClock (){
        }
        virtual ~MyClock() { ; };

        //---- Get data from ntp server
        void ntpsync (const char* ntpserver) {
            configTime(gmtOffset_sec, daylightOffset_sec, ntpserver);
            if(!getLocalTime(&MyTimeInfo)){
                Serial.println("Failed to obtain time");
                return;
            }
            getLocalTime(&MyTimeInfo);
        }

        //----- Updata time structure from internal clock
        void TUpdate () {
            time(&now);                         // read the current time
            localtime_r(&now, &MyTimeInfo);     // update the structure tm with the current time
        }

        //----- Set gmt
        void SetGmtOffset (int sec) {
            gmtOffset_sec = sec;
        }

        //----- In case of esp32 non update regulary set hour ofset
        void SetDayLightOffset (int sec) {
            daylightOffset_sec = sec;
        }

        //----- Writte time in console
        void WriteTime() {
            TUpdate();
            Serial.print("year:");
            Serial.print(MyTimeInfo.tm_year + 1900);  // years since 1900
            Serial.print("\tmonth:");
            Serial.print(MyTimeInfo.tm_mon + 1);      // January = 0 (!)
            Serial.print("\tday:");
            Serial.print(MyTimeInfo.tm_mday);         // day of month
            Serial.print("\thour:");
            Serial.print(MyTimeInfo.tm_hour);         // hours since midnight  0-23
            Serial.print("\tmin:");
            Serial.print(MyTimeInfo.tm_min);          // minutes after the hour  0-59
            Serial.print("\tsec:");
            Serial.print(MyTimeInfo.tm_sec);          // seconds after the minute  0-61*
            Serial.println();
        }

        //----- Function to get different data
        int year () {
            return MyTimeInfo.tm_year;
        }
        int month () {
            return MyTimeInfo.tm_mon;
        }
        int day () {
            return MyTimeInfo.tm_mday;
        }
        int hour () {
            return MyTimeInfo.tm_hour;
        }
        int minute () {
            return MyTimeInfo.tm_min;
        }
        int wday () {
            return MyTimeInfo.tm_wday;
        }
        struct tm exportStruct () {
            return MyTimeInfo;
        }
        
        private:
        struct tm MyTimeInfo;
        time_t now;
        int gmtOffset_sec = 3600;
        int daylightOffset_sec = 0;
        char* server;
    };
    
//----- Functions to get name of day and month in form of String
String wday_name ( int input ) {
    String output;
    switch (input)
    {
        case(0):
            output = "Mon";
            break;
        case(1):
            output = "Tue";
            break;
        case(2):
            output = "Wed";
            break;
        case(3):
            output = "Thu";
            break;
        case(4):
            output = "Fri";
            break;
        case(5):
            output = "Sat";
            break;
        case(6):
            output = "Sun";
            break;
        default:
            output = "error";
            break;
    }
    return output;
}

String month_name ( int input ) {
    String output;
    switch (input)
    {
        case(0):
            output = "Jen";
            break;
        case(1):
            output = "Feb";
            break;
        case(2):
            output = "Mar";
            break;
        case(3):
            output = "Apr";
            break;
        case(4):
            output = "May";
            break;
        case(5):
            output = "Jun";
            break;
        case(6):
            output = "Jul";
            break;
        case(7):
            output = "Aug";
            break;
        case(8):
            output = "Sep";
            break;
        case(9):
            output = "Oct";
            break;
        case(10):
            output = "Nov";
            break;
        case(11):
            output = "Dec";
            break;
        default:
            output = "error";
            break;
    }
    return output;
}

#endif //__My_Time_Config__

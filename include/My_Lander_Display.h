//--------------------------------------------------------------------------------------------------------------//
//----- Class to display data on screen using tft_espi library, (retriving class from main using pointers) -----//
//--------------------------------------------------------------------------------------------------------------//

#ifndef __My_Lander_Display__
#define __My_Lander_Display__

#include <TFT_eSPI.h>
#include <My_Weather.h>

class Lander_Display {
    public:
        Lander_Display(TFT_eSPI *tft_pointer ) { tft = tft_pointer; }
        virtual ~Lander_Display() { ; };

        //----- Initialize screen with geometrical colored structure, can also update if color selected change
        void init () {
            tft->init();
            tft->setRotation(2);
            tft->fillScreen(TFT_BLACK);
            
            //clock - setion
            tft->drawWideLine(60, 24, 84, 48, 2, color, TFT_BLACK);
            tft->fillRect(0, 0, 60, 25, color);
            tft->fillRect(84, 47, 44, 2, color);
            tft->fillTriangle(60, 0, 60, 24, 84, 0, color);
            tft->setTextColor(TFT_BLACK);
            tft->drawString(clock,2,0,4);

            //roomPressure and roomTemperature - section
            tft->drawWideLine(58, 67, 72, 81, 2, color, TFT_BLACK);
            tft->fillRect(0, 67, 58, 2, color);
            tft->fillRect(72, 81, 58, 2.5, color);

            //sunrise icon
            tft->drawArc(20, 153, 9, 7,90, 270, color, TFT_BLACK, true);
            tft->fillRect(8, 154, 25, 2, color);

            tft->drawLine(20, 140, 20, 134, color);
            tft->drawLine(21, 140, 21, 134, color);

            tft->drawLine(20,134,17,137,color);
            tft->drawLine(20,133,17,136,color);

            tft->drawLine(21,134,24,137,color);
            tft->drawLine(21,133,24,136,color);

            //sunset icon
            tft->drawArc(63, 153, 9, 7,90, 270, color, TFT_BLACK, true);
            tft->fillRect(51, 154, 25, 2, color);

            tft->drawLine(63, 140, 63, 134, color);
            tft->drawLine(64, 140, 64, 134, color);

            tft->drawLine(63,140,60,137,color);
            tft->drawLine(63,139,60,136,color);

            tft->drawLine(64,140,67,137,color);
            tft->drawLine(64,139,67,136,color);

            //wind icon
            tft->fillRect(99, 144, 9, 2, color);
            tft->drawArc(108,142, 3, 2,180,360,color,TFT_BLACK,true); 
            tft->fillRect(96, 149, 16, 2, color);
            tft->drawArc(112,152, 3, 2,180,360,color,TFT_BLACK,true); 
            tft->fillRect(99, 154, 9, 2, color);
        }
        
        //----- Retrive current time data in form of tm structure, it came from MyClock structure
        void tmstructup (struct tm buffer) {
            PresentTime = buffer;
        }

        //----- Update Sensor data 
        void measureup (float temp, float pres) {
            tft->setTextColor(TFT_BLACK);                       //deleting old data
            tft->drawRightString(roomTemperature,64, 38 ,4);
            tft->drawRightString(roomPressure,125,55,2);  
            roomTemperature = String ( ((round (temp*10.f))/10.f) );    //update measures
                if (roomTemperature.length() == 5) {
                    roomTemperature.remove(4, 1);
                } else if ( roomTemperature.length() == 4 ) {
                    roomTemperature.remove(3, 1);
                }
                roomTemperature += "\u00b0";
            roomPressure = String((pres)/100000.f);
                if (roomPressure.length() == 9) {
                    //roomPressure.remove (6,3);
                }
                roomPressure += " bar";
            tft->setTextColor(TFT_WHITE);                    //write new measures
            tft->drawRightString(roomTemperature,64,38,4);
            tft->drawCircle(61, 41, 2, TFT_WHITE);
            tft->drawRightString(roomPressure,125,55,2);
        };

        //----- Update Time
        void timeup (struct tm buffer) {
            PresentTime = buffer;

            if (minute != PresentTime.tm_min) {     //if minute change update clock (minimize flickering)
                tft->setTextColor(color);           //deleting old time
                tft->drawString(clock,2,0,4);
                if (PresentTime.tm_hour < 10) {                   //Update time String
                    clock = "0" + String(PresentTime.tm_hour);
                } else {
                    clock = "" + String(PresentTime.tm_hour);
                }
                if (PresentTime.tm_min < 10) {                    
                    clock += ":0" + String(PresentTime.tm_min);
                } else {
                    clock += ":" + String(PresentTime.tm_min);
                }
                tft->setTextColor(TFT_BLACK);       //write new time
                tft->drawString(clock,2,0,4);
                minute = PresentTime.tm_min;        //update minute for the change condition
            }

            if (day != PresentTime.tm_mday) {       //if day change update date (minimize flickering)
                tft->setTextColor(TFT_BLACK);           //delete old date
                tft->drawString (year,87,5,2);
                tft->drawString(date,77,22,2);
                if (PresentTime.tm_mday < 10) {     //Update date String
                    date = " " + String(PresentTime.tm_mday);
                } else {
                    date = String(PresentTime.tm_mday);
                }
                date += "-" + month_name(PresentTime.tm_mon);
                year = 1900 + PresentTime.tm_year;
                tft->setTextColor(TFT_WHITE);       //write new date
                tft->drawString (year,87,5,2);
                tft->drawString(date,77,22,2);
                day = PresentTime.tm_mday;          //update day for the change condition
            }
        }

        //----- Update weather
        void weatherUp(String rawData) {
            tft->setTextColor(TFT_BLACK);                       //delete old measure
            tft->drawRightString(cityTemperature, 47, 79, 2);
            tft->drawCircle(51, 83, 2, TFT_BLACK);
            tft->drawRightString("Naters",118, 85, 2);
            tft->drawCentreString(description, 64, 106, 1);
            tft->drawString(sunrise, 10, 123, 1);
            tft->drawString(sunset, 49, 123, 1);
            tft->drawRightString(wind, 113, 123, 1);
            tft->drawString("m",115,120,1);
            tft->drawString("s",118,128,1);
            wt.extractData(rawData);                            //extract data from API String
            getWeather ();                                      //update internal varibles
            tft->setTextColor(TFT_WHITE);                       //write new measure
            tft->drawRightString(cityTemperature, 47, 79, 2);
            tft->drawCircle(51, 83, 2, TFT_WHITE);
            tft->drawRightString("Naters",118, 85, 2);
            tft->drawCentreString(description, 64, 106, 1);
            tft->drawString(sunrise, 10, 123, 1);
            tft->drawString(sunset, 49, 123, 1);
            tft->drawRightString(wind, 113, 123, 1);
            tft->drawString("m",115,120,1);
            tft->drawString("s",118,128,1);
        };

        //----- Update internal variables
        void getWeather() {
            wind = String(wt.get_wind());
            description = wt.get_description();
            sunrise = wt.get_sunrise();
            sunset = wt.get_sunset();
            cityTemperature = String(wt.get_temperature());
            cityHumidity = String(wt.get_humidity()) + " %";
        };

        void setColor (uint32_t new_color) {        //set new structure color
            color = new_color;
        }

    private:
        //-----Pointers----//
    TFT_eSPI* tft;
        //----Variables----//
    weatherData wt;
    struct tm PresentTime;
    int day;
    int minute;
    uint32_t color = 0xfba0;
        //-----clock-------//
    String clock = "00:00";
    String date = "00/00";
    String year = "0000";
        //-----Sensor------//
    String roomTemperature = "00.0";
    String roomPressure = "0.00 bar";
        //-----Weather-----//
    String city = "Naters";
    String wind;
    String description;
    String sunrise = "0:00";
    String sunset = "0:00";
    String cityTemperature = "00.0";
    String cityHumidity = "00%";
};

#endif //__My_Lander_Display__
//--------------------------------------------------------------------------//
//----- Class meant to extract data from the String extracted from API -----//
//--------------------------------------------------------------------------//

#ifndef __my_Weather__
#define __my_Weather__

#include <arduino.h>
#include <ArduinoJson.h>

String retriveInfo;

class weatherData {
  public: 

    //---------- initializer -----------//
    weatherData () {}
    virtual ~weatherData() { ; };

    //----- data extracion from raw ----//
    void extractData (String raws) {
      JsonDocument doc;
      String buffer;

      deserializeJson(doc, raws);
      String bufWeather = doc["weather"].as<String>();
        bufWeather.remove(0, 1);     //used to remove "[" and read data
      String bufMain = doc["main"].as<String>();
      String bufWind = doc["wind"].as<String>();
      String bufSys = doc["sys"].as<String>();

      deserializeJson(doc, bufMain);
      temperature = doc["temp"].as<float>();
      humidity = doc["humidity"].as<int>();

      deserializeJson(doc, bufWeather);
      description = doc["description"].as<String>();

      deserializeJson(doc, bufWind);
      wind = doc["speed"].as<float>();

      deserializeJson(doc, bufSys);
      Sunrise = unixToString(doc["sunrise"].as<int>());
      Sunset = unixToString(doc["sunset"].as<int>());
    }

    //----- print data in terminal ----//
    void SerialPrintData () {           
      Serial.print ("wind :");
      Serial.println(wind);
      Serial.print ("sunrise :");
      Serial.println(Sunrise);
      Serial.print ("sunset :");
      Serial.println(Sunset);
      Serial.print ("description :");
      Serial.println(description);
    }

    //------- get data functions ------//
    float get_wind () {return wind;};
    String get_sunrise() { return Sunrise; };
    String get_sunset() { return Sunset; };
    String get_description() { return description; };
    float get_temperature() { return temperature; };
    int get_humidity() { return humidity; };

  private: 
    float wind = 0;
    String Sunrise;
    String Sunset;
    String description;
    float temperature;
    int humidity;

    //----- unix to readable time -----//
    String unixToString (int input) {
      time_t unixTime = input;
      struct tm ts;
      ts = *localtime(&unixTime);
      String minutes(ts.tm_min);
      String hours(ts.tm_hour);
      if (ts.tm_min < 10) {
        String output1(hours + ":0" + minutes);
        return output1;
      }
      else {
        String output2 (hours + ":" + minutes);
        return output2;
      }
    }
};




#endif //__my_Weather__

# include <iostream>

# include "GPXDataUnit.h"

GPXDataUnit::GPXDataUnit()
{
    reset();
}

void GPXDataUnit::reset()
{
    this->time = 0;
    this->lat = 0.0;
    this->lng = 0.0;
    this->ele = 0.0;
    this->hr = 0;
}

int GPXDataUnit::getTime()
{
    return time;
}

double GPXDataUnit::getLat()
{
    return lat;
}

double GPXDataUnit::getLng()
{
    return lng;
}

double GPXDataUnit::getEle()
{
    return ele;
}

int GPXDataUnit::getHr()
{
    return hr;
}

void GPXDataUnit::setTime(int time)
{
    this->time = time;
}

void GPXDataUnit::setLat(double lat)
{
    this->lat = lat;
}

void GPXDataUnit::setLng(double lng)
{
    this->lng = lng;
}

void GPXDataUnit::setEle(double ele)
{
    this->ele = ele;
}

void GPXDataUnit::setHr(int hr)
{
    this->hr = hr;
}

std::string GPXDataUnit::toString()
{
    std::string str = "";
    
    str = str + "time : " + std::to_string(time);
    str = str + ", lat : " + std::to_string(lat);
    str = str + ", lng : " + std::to_string(lng);
    str = str + ", ele : " + std::to_string(ele);
    str = str + ", hr : " + std::to_string(hr);

    return str;
}
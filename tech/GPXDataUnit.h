
# include <iostream>

# if (!defined(GPX_DATA_UNIT_H))
# define GPX_DATA_UNIT_H

class GPXDataUnit
{
    private:

    int time = 0;
    double lat = 0.0;
    double lng = 0.0;
    double ele = 0.0;
    int hr = 0;
    
    public:

    GPXDataUnit();

    void reset();

    int getTime();
    double getLat();
    double getLng();
    double getEle();
    int getHr();

    void setTime(int time);
    void setLat(double lat);
    void setLng(double lng);
    void setEle(double ele);
    void setHr(int hr);

    std::string toString();
};

# endif // GPX_DATA_UNIT_H

# include <vector>
# include <fstream>
# include <math.h>

# include "debug.h"
# include "../STRUtils.cpp"

class GPXData
{
    private:

    const int trkPtsDivider = 5;
    static const int earthRadiusKm = 6371;

    typedef struct GPXTrkPt
    {
        int time = 0;
        double lat = 0.0;
        double lng = 0.0;
        double ele = 0.0;
        int hr = 0;

        void reset()
        {
            time = 0;
            lat = 0.0;
            lng = 0.0;
            ele = 0.0;
            hr = 0;
        }
    } GPXTrkPt;

    std::vector<GPXTrkPt> gpxTrkPts;

    public:

    int parse(std::string fileName, std::string * label);
    int process(std::vector<double> * speeds, std::vector<double> * elevationGradients, std::vector<double> * heartRates);
    static double degToRad(double deg);
    static double distBtwCoord(double lat1, double lng1, double lat2, double lng2);
};
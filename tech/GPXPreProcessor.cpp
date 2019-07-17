
# include <iostream>
# include <vector>
# include <math.h>

# include "GPXDataUnit.h"

class GPXPreProcessor
{
    private:
    
    static const int pointsNbDivider = 5;
    static const int earthRadiusKm = 6371;
    
    public:

    static int process(std::vector<GPXDataUnit> * gpxData, std::vector<double> * speeds, std::vector<double> * elevationGradients, std::vector<double> * heartRates)
    {
        int result = 1;

        int timesSum = 0;
        double distancesSum = 0.0;
        double elevationsSum = 0.0;
        double heartRatesSum = 0.0;

        speeds->clear();
        elevationGradients->clear();
        heartRates->clear();

        int iGPXData = 0;
        std::vector<GPXDataUnit>::iterator currGPXDataUnitIt = gpxData->begin();
        std::vector<GPXDataUnit>::iterator prevGPXDataUnitIt;

        while (currGPXDataUnitIt != gpxData->end())
        {
            timesSum = 0;
            distancesSum = 0.0;
            elevationsSum = 0.0;
            heartRatesSum = 0.0;

            iGPXData = 0;
            while (currGPXDataUnitIt != gpxData->end() && iGPXData < pointsNbDivider)
            {
                prevGPXDataUnitIt = currGPXDataUnitIt;
                currGPXDataUnitIt++;
                
                timesSum = timesSum + currGPXDataUnitIt->getTime() - prevGPXDataUnitIt->getTime();
                distancesSum = distancesSum + distBtwCoord(prevGPXDataUnitIt->getLat(), prevGPXDataUnitIt->getLng(), currGPXDataUnitIt->getLat(), currGPXDataUnitIt->getLng());
                elevationsSum = elevationsSum + (currGPXDataUnitIt->getEle() - prevGPXDataUnitIt->getEle());
                heartRatesSum = heartRatesSum + currGPXDataUnitIt->getHr(); 
                
                iGPXData = iGPXData + 1;
            }

            if (currGPXDataUnitIt != gpxData->end())
            {
                speeds->push_back(distancesSum / timesSum * 3600);
                if (distancesSum != 0.0)
                {
                    elevationGradients->push_back(elevationsSum / (distancesSum * 1000.0));
                }
                else
                {
                    elevationGradients->push_back(0.0);
                }
                heartRates->push_back(heartRatesSum / pointsNbDivider);
            }
        }

        result = 0;
        
        return result;
    }
    
    static double degToRad(double deg)
    {
        return deg * 3.14 / 180.0;
    }
    
    static double distBtwCoord(double lat1, double lng1, double lat2, double lng2)
    {
        double dLat = degToRad(lat2 - lat1);
        double dLng = degToRad(lng2 - lng1);

        lat1 = degToRad(lat1);
        lat2 = degToRad(lat2);

        double a = sin(dLat/2) * sin(dLat/2) + sin(dLng/2) * sin(dLng/2) * cos(lat1) * cos(lat2); 
        double c = 2 * atan2(sqrt(a), sqrt(1 - a)); 
        
        return earthRadiusKm * c;
    }
};


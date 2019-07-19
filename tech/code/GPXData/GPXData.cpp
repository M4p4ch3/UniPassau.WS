
# include "GPXData.h"

int GPXData::parse(std::string fileName, std::string * label)
{
    int result = 1;

    std::ifstream gpxFile;
    gpxFile.open(fileName);

    if (gpxFile.is_open())
    {
        std::string line = "";
        int baseTime = 0;
        int time = 0;
        GPXTrkPt gpxTrkPt;

        gpxTrkPts.clear();

        // Label is 'regular' by default
        *label = "regular";

        // Read until '<trk>'
        while (STRUtils::contains(line, "<trk>") == false)
        {
            // If Activity contains <label>
            if (STRUtils::contains(line, "<label>"))
            {
                // Get Activity Label (overTraining)
                *label = STRUtils::getXMLStr(line);
            }

            std::getline(gpxFile, line);
        }

        // Read until end of GPX File
        while (STRUtils::contains(line, "</gpx>") == false)
        {
            // New <trkpt>
            if (STRUtils::contains(line, "<trkpt"))
            {
                gpxTrkPt.reset();
                
                gpxTrkPt.lat = STRUtils::getLat(line);
                gpxTrkPt.lng = STRUtils::getLng(line);

                // Until End of <trkpt>
                while (STRUtils::contains(line, "</trkpt>") == false)
                {
                    if (STRUtils::contains(line, "<ele"))
                    {
                        gpxTrkPt.ele = STRUtils::getXMLVal(line);
                    }
                    else if (STRUtils::contains(line, "<gpxtpx:hr"))
                    {
                        gpxTrkPt.hr = STRUtils::getXMLVal(line);
                    }
                    else if (STRUtils::contains(line, "<time"))
                    {
                        time = STRUtils::getXMLTime(line);

                        // If baseTime not defined
                        if (baseTime == 0)
                        {
                            // Define baseTime
                            baseTime = time;
                        }

                        gpxTrkPt.time = time - baseTime;
                    }

                    std::getline(gpxFile, line);
                }

                gpxTrkPts.push_back(gpxTrkPt);
            }
            
            std::getline(gpxFile, line);
        }

        gpxFile.close();

        result = 0;
    }
    else
    {
        DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("Error : Cant open file : '%s'", fileName.c_str()));
        
        result = 1;
    }

    return result;
}

int GPXData::process(std::vector<double> * speeds, std::vector<double> * elevationGradients, std::vector<double> * heartRates)
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
    std::vector<GPXTrkPt>::iterator currGPXTrkPt = gpxTrkPts.begin();
    std::vector<GPXTrkPt>::iterator prevGPXTrkPt;

    while (currGPXTrkPt != gpxTrkPts.end())
    {
        timesSum = 0;
        distancesSum = 0.0;
        elevationsSum = 0.0;
        heartRatesSum = 0.0;

        iGPXData = 0;
        while (currGPXTrkPt != gpxTrkPts.end() && iGPXData < trkPtsDivider)
        {
            prevGPXTrkPt = currGPXTrkPt;
            currGPXTrkPt++;
            
            timesSum = timesSum + currGPXTrkPt->time - prevGPXTrkPt->time;
            distancesSum = distancesSum + distBtwCoord(prevGPXTrkPt->lat, prevGPXTrkPt->lng, currGPXTrkPt->lat, currGPXTrkPt->lng);
            elevationsSum = elevationsSum + (currGPXTrkPt->ele - prevGPXTrkPt->ele);
            heartRatesSum = heartRatesSum + currGPXTrkPt->hr; 
            
            iGPXData = iGPXData + 1;
        }

        if (currGPXTrkPt != gpxTrkPts.end())
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
            heartRates->push_back(heartRatesSum / trkPtsDivider);
        }
    }

    result = 0;
    
    return result;
}

double GPXData::degToRad(double deg)
{
    return deg * 3.14 / 180.0;
}

double GPXData::distBtwCoord(double lat1, double lng1, double lat2, double lng2)
{
    double dLat = degToRad(lat2 - lat1);
    double dLng = degToRad(lng2 - lng1);

    lat1 = degToRad(lat1);
    lat2 = degToRad(lat2);

    double a = sin(dLat/2) * sin(dLat/2) + sin(dLng/2) * sin(dLng/2) * cos(lat1) * cos(lat2); 
    double c = 2 * atan2(sqrt(a), sqrt(1 - a)); 
    
    return earthRadiusKm * c;
}
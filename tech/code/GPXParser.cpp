
# include <iostream>
# include <vector>
# include <fstream>

# include "debug/debug.h"
# include "GPXDataUnit.h"
# include "STRUtils.cpp"

class GPXParser
{
    public :
    
    static int parse(std::string fileName, std::string * label, std::vector<GPXDataUnit> * gpxData)
    {
        int result = 1;

        std::ifstream gpxFile;
        gpxFile.open(fileName);

        if (gpxFile.is_open())
        {
            std::string line = "";
            
            gpxData->clear();
            GPXDataUnit gpxDataUnit;
            int baseTime = 0;
            int time = 0;

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
                    // Reset gpxDataUnit
                    gpxDataUnit.reset();

                    gpxDataUnit.setLat(STRUtils::getLat(line));
                    gpxDataUnit.setLng(STRUtils::getLng(line));

                    // Until End of <trkpt>
                    while (STRUtils::contains(line, "</trkpt>") == false)
                    {
                        if (STRUtils::contains(line, "<ele"))
                        {
                            gpxDataUnit.setEle(STRUtils::getXMLVal(line));
                        }
                        else if (STRUtils::contains(line, "<gpxtpx:hr"))
                        {
                            gpxDataUnit.setHr(STRUtils::getXMLVal(line));
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

                            gpxDataUnit.setTime(time - baseTime);
                        }

                        std::getline(gpxFile, line);
                    }

                    // Append gpxDataUnit to gpxData
                    gpxData->push_back(gpxDataUnit);
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
};

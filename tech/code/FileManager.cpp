
# include <iostream>
# include <fstream>
# include <vector>
# include <dirent.h>

# include "Stats.h"

class FileManager
{
    private:

    public:

    static std::vector<std::string> getContent(std::string folder)
    {
        std::string name = "";

        std::vector <std::string> content;
        
        DIR * dir = nullptr;
        struct dirent * ent = nullptr;

        dir = opendir(folder.c_str());

        if (dir != NULL)
        {
            ent = readdir(dir);
                
            while (ent != NULL)
            {
                name = ent->d_name;

                if (name != "." && name != "..")
                {
                    content.push_back(ent->d_name);
                }

                ent = readdir(dir);
            }
            
            closedir(dir);
        }

        return content;
    }

    static int write(std::string fileName, std::vector<double> speeds, std::vector<double> elevationGradients, std::vector<double> heartRates)
    {
        int result = 1;
        
        int iVector = 0;
        int elementsNb = 0;
        
        std::ofstream myFile;
        myFile.open(fileName);

        if (myFile.is_open())
        {
            elementsNb = speeds.size();
            if (elevationGradients.size() < elementsNb)
            {
                elementsNb = elevationGradients.size();
            }
            if (heartRates.size() < elementsNb)
            {
                elementsNb = heartRates.size();
            }

            myFile << "speed,elevationGradient,heartRate\n";

            iVector = 0;
            while (iVector < elementsNb)
            {

                myFile << speeds[iVector] << "," << elevationGradients[iVector] << "," << heartRates[iVector] << "\n"; 

                iVector = iVector + 1;
            }

            myFile.close();

            result = 0;
        }
        else
        {
            result = 1;
        }

        return result;
    }

    static int writeStatsHeader(std::string fileName)
    {
        int result = 1;

        std::ofstream myFile;
        myFile.open(fileName);

        if (myFile.is_open())
        {
            myFile << "label,";
            myFile << "speedQuartile1,speedMedian,speedQuartile3,";
            myFile << "elevationGradientQuartile3,";
            myFile << "heartRateQuartile1,heartRateMedian,heartRateQuartile3\n";

            myFile.close();

            result = 0;
        }
        else
        {
            result = 1;
        }

        return result;
    }

    static int append(std::string fileName, std::string label, Stats speedsStates, Stats elevationGradientsStats, Stats heartRatesStats)
    {
        int result = 1;

        std::ofstream myFile;
        myFile.open(fileName, std::ofstream::app);

        if (myFile.is_open())
        {
            myFile << label << ",";

            /*
            myFile << speedsStates.getMinimum() << "," << speedsStates.getQuartile1() << "," << speedsStates.getMedian() << ",";
            myFile << speedsStates.getQuartile3() << "," << speedsStates.getMaximum() << "," << speedsStates.getVariance() << ",";

            myFile << elevationGradientsStats.getAverage() << "," << elevationGradientsStats.getMinimum() << "," << elevationGradientsStats.getQuartile1() << "," << elevationGradientsStats.getMedian() << ",";
            myFile << elevationGradientsStats.getQuartile3() << "," << elevationGradientsStats.getMaximum() << "," << elevationGradientsStats.getVariance() << ",";

            myFile << heartRatesStats.getAverage() << "," << heartRatesStats.getMinimum() << "," << heartRatesStats.getQuartile1() << "," << heartRatesStats.getMedian() << ",";
            myFile << heartRatesStats.getQuartile3() << "," << heartRatesStats.getMaximum() << "," << heartRatesStats.getVariance() << "\n";
            //*/

            myFile << speedsStates.getQuartile1() << "," << speedsStates.getMedian() << "," << speedsStates.getQuartile3() << ",";
            myFile << elevationGradientsStats.getQuartile3() << ",";
            myFile << heartRatesStats.getQuartile1() << "," << heartRatesStats.getMedian() << "," << heartRatesStats.getQuartile3() << "\n";

            myFile.close();
            
            result = 0;
        }
        else
        {
            result = 1;
        }

        return result;
    }
};
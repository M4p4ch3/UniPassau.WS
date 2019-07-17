
# include <iostream>
# include <fstream>
# include <vector>
# include <dirent.h>

# include "Stats.h"

class FileManager
{
    private:

    public:

    static vector<string> getContent(string folder)
    {
        string name = "";

        vector <string> content;
        
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

    static int write(std::string fileName, std::string label, std::vector<double> speeds, std::vector<double> elevationGradients, std::vector<double> heartRates)
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

            myFile << "label:'" << label << "'\n";
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

    static int write(std::string fileName, std::string label, Stats speedsStates, Stats elevationGradientsStats, Stats heartRatesStats)
    {
        int result = 1;

        std::ofstream myFile;
        myFile.open(fileName);

        if (myFile.is_open())
        {
            myFile << "data,description,average,minimum,quartile1,median,quartile3,maximum,variance\n";
            
            myFile << "label," << label << ",,,,,,,\n";
            
            myFile << "speed,," << speedsStates.getAverage() << "," << speedsStates.getMinimum() << "," << speedsStates.getQuartile1() << "," << speedsStates.getMedian() << ",";
            myFile << speedsStates.getQuartile3() << "," << speedsStates.getMaximum() << "," << speedsStates.getVariance() << "\n";

            myFile << "elevationGradient,," << elevationGradientsStats.getAverage() << "," << elevationGradientsStats.getMinimum() << "," << elevationGradientsStats.getQuartile1() << "," << elevationGradientsStats.getMedian() << ",";
            myFile << elevationGradientsStats.getQuartile3() << "," << elevationGradientsStats.getMaximum() << "," << elevationGradientsStats.getVariance() << "\n";

            myFile << "heartRate,," << heartRatesStats.getAverage() << "," << heartRatesStats.getMinimum() << "," << heartRatesStats.getQuartile1() << "," << heartRatesStats.getMedian() << ",";
            myFile << heartRatesStats.getQuartile3() << "," << heartRatesStats.getMaximum() << "," << heartRatesStats.getVariance() << "\n";
            
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
            myFile << "speedAverage,speedMinimum,speedQuartile1,speedMedian,speedQuartile3,speedMaximum,speedVariance,";
            myFile << "elevationGradientAverage,elevationGradientMinimum,elevationGradientQuartile1,elevationGradientMedian,elevationGradientQuartile3,elevationGradientMaximum,elevationGradientVariance,";
            myFile << "heartRateAverage,heartRateMinimum,heartRateQuartile1,heartRateMedian,heartRateQuartile3,heartRateMaximum,heartRateVariance\n";

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

            myFile << speedsStates.getAverage() << "," << speedsStates.getMinimum() << "," << speedsStates.getQuartile1() << "," << speedsStates.getMedian() << ",";
            myFile << speedsStates.getQuartile3() << "," << speedsStates.getMaximum() << "," << speedsStates.getVariance() << ",";

            myFile << elevationGradientsStats.getAverage() << "," << elevationGradientsStats.getMinimum() << "," << elevationGradientsStats.getQuartile1() << "," << elevationGradientsStats.getMedian() << ",";
            myFile << elevationGradientsStats.getQuartile3() << "," << elevationGradientsStats.getMaximum() << "," << elevationGradientsStats.getVariance() << ",";

            myFile << heartRatesStats.getAverage() << "," << heartRatesStats.getMinimum() << "," << heartRatesStats.getQuartile1() << "," << heartRatesStats.getMedian() << ",";
            myFile << heartRatesStats.getQuartile3() << "," << heartRatesStats.getMaximum() << "," << heartRatesStats.getVariance() << "\n";
            
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
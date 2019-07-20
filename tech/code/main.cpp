
# include <iostream>
# include <vector>

# include "debug.h"
# include "GPXData.h"
# include "Stats.h"

# include "FileManager.cpp"

int main()
{
    std::string label = "";
 
    int result = 1;

    std::string mode = "";
 
    Stats speedsStats;
    Stats elevationGradientsStats;
    Stats heartRatesStats;

    GPXData gpxData;

    std::vector<double> speeds;
    std::vector<double> elevationGradients;
    std::vector<double> heartRates;

    std::vector<std::string> filesNames;

    DEBUG_PRINT(TYPE_INFO, STYLE_LINE_START, ("Mode ? (train/predict) : "));
    std::cin >> mode;

    if (mode == "train")
    {
        DEBUG_PRINT(TYPE_INFO, STYLE_START, ("Train Mode"));

        DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Writing Headers of File : 'knime/trainingData.csv'"));
        result = FileManager::writeStatsHeader("../knime/trainingData.csv");

        if (result == 0)
        {
            DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Getting Content of Folder : 'data/train'"));
            filesNames = FileManager::getContent("../data/train/");

            DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("%d Files Found", (int)(filesNames.size())));

            for (std::string fileName : filesNames)
            {
                DEBUG_PRINT(TYPE_INFO, STYLE_START, ("Selected File : '%s'", fileName.c_str()));
                
                label = "";
                speeds.clear();
                elevationGradients.clear();
                heartRates.clear();

                DEBUG_PRINT(TYPE_INFO, STYLE_START, ("Parsing"));
                result = gpxData.parse("../data/train/" + fileName, &label);
                DEBUG_PRINT(TYPE_INFO, STYLE_END, ("Parsing"));

                if (result == 0)
                {
                    DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Processing"));
                    result = gpxData.process(&speeds, &elevationGradients, &heartRates);

                    if (result == 0)
                    {
                        DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Writing File : 'processed/%s.csv'", fileName.c_str()));
                        result = FileManager::write("../processed/" + fileName + ".csv", label, speeds, elevationGradients, heartRates);
                        
                        if (result == 0)
                        {
                            DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Computing Stats"));
                            result = speedsStats.compute(speeds);
                            result = result + elevationGradientsStats.compute(elevationGradients);
                            result = result + heartRatesStats.compute(heartRates);

                            if (result == 0)
                            {
                                DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Writing File : 'stats/%s.csv'", fileName.c_str()));
                                result = FileManager::write("../stats/" + fileName + ".csv", label, speedsStats, elevationGradientsStats, heartRatesStats);

                                DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Appending Stats to File : 'knime/trainingData.csv'"));
                                result = result + FileManager::append("../knime/trainingData.csv", label, speedsStats, elevationGradientsStats, heartRatesStats);

                                if (result == 0)
                                {

                                }
                                else
                                {
                                    DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("ERROR : While writing File : 'stats/%s.csv', or appending to File : 'knime/trainingData.csv'", fileName.c_str()));
                                }
                            }
                            else
                            {
                                DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("ERROR : While computing Stats"));
                            }
                        }
                        else
                        {
                            DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("ERROR : While writing File : 'processed/%s.csv'", fileName.c_str()));
                        }
                    }
                    else
                    {
                        DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("ERROR : While processing"));
                    }
                }
                else
                {
                    DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("ERROR : While parsing"));
                }

                DEBUG_PRINT(TYPE_INFO, STYLE_END, ("Selected File : '%s'", fileName.c_str()));
            }
        }
        else
        {
            DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("ERROR : While writing Header of File : 'knime/trainingData.csv'"));
        }

        DEBUG_PRINT(TYPE_INFO, STYLE_END, ("Train Mode"));
    }
    else if (mode == "predict")
    {
        DEBUG_PRINT(TYPE_INFO, STYLE_START, ("Predict Mode"));
        
        std::string fileName = "";
        
        DEBUG_PRINT(TYPE_INFO, STYLE_LINE_START, ("File : "));
        std::cin >> fileName;

        DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Parsing"));
        result = gpxData.parse("../data/predict/" + fileName + ".gpx", &label);

        if (result == 0)
        {
            DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Processing"));
            result = gpxData.process(&speeds, &elevationGradients, &heartRates);

            if (result == 0)
            {
                DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Computing Stats"));
                result = speedsStats.compute(speeds);
                result = result + elevationGradientsStats.compute(elevationGradients);
                result = result + heartRatesStats.compute(heartRates);

                if (result == 0)
                {
                    DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Writing Headers of File : 'knime/%s.csv'", fileName.c_str()));
                    result = FileManager::writeStatsHeader("../knime/" + fileName + ".csv");
                    
                    DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Appending Stats to File : 'knime/%s.csv'", fileName.c_str()));
                    result = result + FileManager::append("../knime/" + fileName + ".csv", label, speedsStats, elevationGradientsStats, heartRatesStats);

                    if (result == 0)
                    {

                    }
                    else
                    {
                        DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("ERROR : While writing File : '../knime/%s.csv'", fileName.c_str()));
                    }
                }
                else
                {
                    DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("ERROR : While computing Stats"));
                }
            }
            else
            {
                DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("ERROR : While processing"));
            }
        }
        else
        {
            DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("ERROR : While parsing GPX File : '%s'", fileName.c_str()));
        }

        DEBUG_PRINT(TYPE_INFO, STYLE_END, ("Predict Mode"));
    }

    return 0;
}

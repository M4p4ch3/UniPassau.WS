
# include <iostream>
# include <vector>

# include "GPXParser.cpp"
# include "GPXPreProcessor.cpp"
# include "FileManager.cpp"
# include "Stats.cpp"

int main()
{
    std::string label = "";
 
    int result = 1;

    std::string mode = "";
 
    Stats speedsStats;
    Stats elevationGradientsStats;
    Stats heartRatesStats;

    std::vector<double> speeds;
    std::vector<double> elevationGradients;
    std::vector<double> heartRates;

    std::vector<std::string> filesNames;

    std::vector<GPXDataUnit> gpxData;

    std::cout << "Mode ? (train/predict) : " << std::flush;
    std::cin >> mode;

    if (mode == "train")
    {
        result = FileManager::writeStatsHeader("../knime/trainingData.csv");

        if (result == 0)
        {
            filesNames = FileManager::getContent("../data/train/");

            for (std::string fileName : filesNames)
            {
                std::cout << "Processing File : " << fileName << std::endl;
                
                label = "";
                speeds.clear();
                elevationGradients.clear();
                heartRates.clear();

                result = GPXParser::parse("../data/train/" + fileName, &label, &gpxData);

                if (result == 0)
                {
                    result = GPXPreProcessor::process(&gpxData, &speeds, &elevationGradients, &heartRates);

                    if (result == 0)
                    {
                        result = FileManager::write("../processed/" + fileName + ".csv", label, speeds, elevationGradients, heartRates);
                        
                        if (result == 0)
                        {
                            result = speedsStats.compute(speeds);
                            result = result + elevationGradientsStats.compute(elevationGradients);
                            result = result + heartRatesStats.compute(heartRates);

                            if (result == 0)
                            {
                                result = FileManager::write("../stats/" + fileName + ".csv", label, speedsStats, elevationGradientsStats, heartRatesStats);
                                result = result + FileManager::append("../knime/trainingData.csv", label, speedsStats, elevationGradientsStats, heartRatesStats);

                                if (result == 0)
                                {

                                }
                                else
                                {
                                    std::cout << "Error : While writing File : '../stats/" + fileName + ".csv', ";
                                    std::cout << "or appending to File : '../knime/trainingData.csv'" << std::endl;
                                }
                            }
                            else
                            {
                                std::cout << "Error : While computing Stats" << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "Error : While writing File : '../processed/" + fileName + ".csv'" << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "Error : While processing" << std::endl;
                    }
                }
                else
                {
                    std::cout << "Error : While parsing GPX File : '" << fileName << "'" << std::endl;
                }
            }
        }
        else
        {
            std::cout << "Error : While writing Header of File : '../knime/trainingData.csv" << std::endl;
        }
    }
    else if (mode == "predict")
    {
        std::string fileName = "";
        
        std::cout << "File : " << std::flush;
        std::cin >> fileName;

        result = GPXParser::parse("../data/predict/" + fileName + ".gpx", &label, &gpxData);

        if (result == 0)
        {
            result = GPXPreProcessor::process(&gpxData, &speeds, &elevationGradients, &heartRates);

            if (result == 0)
            {
                result = speedsStats.compute(speeds);
                result = result + elevationGradientsStats.compute(elevationGradients);
                result = result + heartRatesStats.compute(heartRates);

                if (result == 0)
                {
                    result = FileManager::writeStatsHeader("../knime/" + fileName + ".csv");
                    result = result + FileManager::append("../knime/" + fileName + ".csv", label, speedsStats, elevationGradientsStats, heartRatesStats);

                    if (result == 0)
                    {

                    }
                    else
                    {
                        std::cout << "Error : While writing File : '../knime/" + fileName + ".csv'" << std::endl;
                    }
                }
                else
                {
                    std::cout << "Error : While computing Stats" << std::endl;
                }
            }
            else
            {
                std::cout << "Error : While processing" << std::endl;
            }
        }
        else
        {
            std::cout << "Error : While parsing GPX File : " << fileName << std::endl;
        }
    }

    return 0;
}

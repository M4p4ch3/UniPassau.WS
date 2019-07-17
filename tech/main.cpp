
# include <iostream>
# include <vector>

# include "GPXParser.cpp"
# include "GPXPreProcessor.cpp"
# include "FileManager.cpp"
# include "Stats.cpp"

int main()
{
    int result = 1;
    
    bool isOverTraining = false;

    std::vector<std::string> filesNames;
    std::vector<GPXDataUnit> gpxData;
    
    std::vector<double> speeds;
    std::vector<double> elevationGradients;
    std::vector<double> heartRates;

    Stats speedsStats;
    Stats elevationGradientsStats;
    Stats heartRatesStats;

    std::string mode = "";

    std::cout << "Mode ? (train/predict):" << std::flush;
    std::cin >> mode;

    if (mode == "train")
    {
        result = FileManager::writeStatsHeader("./knime/trainingData.csv");

        if (result == 0)
        {
            filesNames = FileManager::getContent("./data/train/");

            for (std::string fileName : filesNames)
            {
                std::cout << "File : " << fileName << std::endl;
                std::cout << "\tOverTrainging ? (1/0) : " << std::flush;
                std::cin >> isOverTraining;

                result = GPXParser::parse("./data/train" + fileName, &gpxData);

                if (result == 0)
                {
                    result = GPXPreProcessor::process(&gpxData, &speeds, &elevationGradients, &heartRates);

                    if (result == 0)
                    {
                        result = FileManager::write("./processed/" + fileName + ".csv", speeds, elevationGradients, heartRates, isOverTraining);
                        
                        if (result == 0)
                        {
                            result = speedsStats.compute(speeds);
                            result = result + elevationGradientsStats.compute(elevationGradients);
                            result = result + heartRatesStats.compute(heartRates);

                            if (result == 0)
                            {
                                result = FileManager::write("./stats/" + fileName + ".csv", speedsStats, elevationGradientsStats, heartRatesStats, isOverTraining);
                                result = result + FileManager::append("./knime/trainingData.csv", speedsStats, elevationGradientsStats, heartRatesStats, isOverTraining);
                            }
                        }
                    }
                }
            }
        }
    }
    else if (mode == "predict")
    {
        std::string fileName = "";
        
        std::cout << "File : " << std::flush;
        std::cin >> fileName;

        result = GPXParser::parse("./data/predict/" + fileName + ".gpx", &gpxData);

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
                    result = FileManager::writeStatsHeader("./knime/" + fileName + ".csv");
                    result = result + FileManager::append("./knime/" + fileName + ".csv", speedsStats, elevationGradientsStats, heartRatesStats, isOverTraining);
                }
            }
        }
    }

    return 0;
}

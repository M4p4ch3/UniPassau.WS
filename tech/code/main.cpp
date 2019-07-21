
# include <iostream>
# include <vector>

# include "debug.h"
# include "GPXData.h"
# include "Stats.h"

# include "FileManager.cpp"

int handleFile(std::string fileName, std::string mode, std::string * label, Stats * speedsStats, Stats * elevationGradientsStats, Stats * heartRatesStats)
{
    int result = 1;

    std::string statsFileName = "";

    std::vector<double> speeds;
    std::vector<double> elevationGradients;
    std::vector<double> heartRates;

    GPXData gpxData;

    DEBUG_PRINT(TYPE_INFO, STYLE_START, ("Selected File : '%s'", fileName.c_str()));

    DEBUG_PRINT(TYPE_INFO, STYLE_START, ("Parsing"));
    result = gpxData.parse("../data/run/" + mode + "/gpx/" + fileName, label);
    DEBUG_PRINT(TYPE_INFO, STYLE_END, ("Parsing"));

    if (result == 0)
    {
        DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Processing"));
        result = gpxData.process(&speeds, &elevationGradients, &heartRates);

        if (result == 0)
        {
            DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Writing processed File : 'data/run/processed/%s.csv'", fileName.c_str()));
            result = FileManager::write("../data/run/processed/" + fileName + ".csv", speeds, elevationGradients, heartRates);
            
            if (result == 0)
            {
                DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Computing Stats"));
                result = speedsStats->compute(speeds);
                result = result + elevationGradientsStats->compute(elevationGradients);
                result = result + heartRatesStats->compute(heartRates);

                if (result == 0)
                {
                    if (mode == "train")
                    {
                        statsFileName = "trainingData";
                    } // if (mode == "train")
                    else // (mode == "test")
                    {
                        statsFileName = fileName;
                    } // else // (mode == "test")

                    DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Appending Stats to File : 'data/run/%s/knime/%s.csv'", mode.c_str(), statsFileName.c_str()));
                    result = FileManager::append("../data/run/" + mode + "/knime/" + statsFileName + ".csv", *label, *speedsStats, *elevationGradientsStats, *heartRatesStats);
                    
                    if (result != 0)
                    {
                        DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("ERROR : While Appending Stats to File : 'data/tun/test/knime/%s.csv'", statsFileName.c_str()));
                    } // if (result != 0)
                } // if (result == 0)
                else // (result != 0)
                {
                    DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("ERROR : While computing Stats"));
                } // else // (result != 0)
            } // if (result == 0)
            else // (result != 0)
            {
                DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("ERROR : While writing processed File : 'data/run/processed/%s.csv'", fileName.c_str()));
            } // else // (result != 0)
        } // if (result == 0)
        else // (result != 0)
        {
            DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("ERROR : While processing"));
        } // else // (result != 0)
    } // if (result == 0)
    else // (result != 0)
    {
        DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("ERROR : While parsing"));
    } // else // (result != 0)

    DEBUG_PRINT(TYPE_INFO, STYLE_END, ("Selected File : '%s'", fileName.c_str()));

    return result;
}

int main()
{
    int result = 1;

    std::string mode = "";
    std::string fileName = "";

    std::string label = "";
 
    std::vector<std::string> filesNames;

    Stats speedsStats;
    Stats elevationGradientsStats;
    Stats heartRatesStats;

    while (mode != "-1")
    {
        DEBUG_PRINT(TYPE_INFO, STYLE_LINE_START, ("Mode {'train', 'test', '-1'} : "));
        std::cin >> mode;

        if (mode != "-1")
        {
            label = "";
            speedsStats.reset();
            elevationGradientsStats.reset();
            heartRatesStats.reset();

            if (mode == "train")
            {
                DEBUG_PRINT(TYPE_INFO, STYLE_START, ("Train Mode"));

                fileName = "";
                while (fileName != "-1")
                {
                    DEBUG_PRINT(TYPE_INFO, STYLE_LINE_START, ("File Name {'all', <fileName>, '-1'} : "));
                    std::cin >> fileName;

                    if (fileName != "-1")
                    {
                        if (fileName == "all")
                        {
                            DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Writing Headers of File : 'data/run/train/knime/trainingData.csv'"));
                            result = FileManager::writeStatsHeader("../data/run/train/knime/trainingData.csv");
                        
                            if (result == 0)
                            {
                                DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Getting Content of Folder : 'data/run/train/gpx'"));
                                filesNames = FileManager::getContent("../data/run/train/gpx");

                                DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("%d Files Found", (int)(filesNames.size())));

                                // For each File
                                for (std::string fileName : filesNames)
                                {
                                    // fileName already contains Extension '.gpx'
                                    
                                    result = handleFile(fileName, mode, &label, &speedsStats, &elevationGradientsStats, &heartRatesStats);

                                    if (result != 0)
                                    {
                                        DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("ERROR : While handling File"));
                                    } // if (result != 0)
                                } // for (std::string fileName : filesNames)
                            } // if (result == 0)
                            else // (result != 0)
                            {
                                DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("ERROR : While writing Header of File : 'data/run/train/knime/trainingData.csv'"));
                            } // else // (result != 0)
                        }
                        else // (fileName != "all")
                        {
                            fileName = fileName + ".gpx";
                            
                            result = handleFile(fileName, mode, &label, &speedsStats, &elevationGradientsStats, &heartRatesStats);

                            if (result != 0)
                            {
                                DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("ERROR : While handling File"));
                            } // if (result != 0)
                        } // else // (fileName != "all")
                    } // if (fileName != "-1")
                } // while (fileName != "-1")

                DEBUG_PRINT(TYPE_INFO, STYLE_END, ("Train Mode"));
            } // if (mode == "train")
            else if (mode == "test")
            {
                DEBUG_PRINT(TYPE_INFO, STYLE_START, ("Test Mode"));
                
                fileName = "";
                while (fileName != "-1")
                {
                    DEBUG_PRINT(TYPE_INFO, STYLE_LINE_START, ("File Name {<fileName>, '-1'} : "));
                    std::cin >> fileName;

                    if (fileName != "-1")
                    {
                        fileName = fileName + ".gpx";

                        DEBUG_PRINT(TYPE_INFO, STYLE_LINE, ("Writing Headers of File : 'data/run/test/knime/%s.csv'", fileName.c_str()));
                        result = FileManager::writeStatsHeader("../data/run/test/knime/" + fileName + ".csv");

                        result = handleFile(fileName, mode, &label, &speedsStats, &elevationGradientsStats, &heartRatesStats);

                        if (result != 0)
                        {
                            DEBUG_PRINT(TYPE_ERROR, STYLE_LINE, ("ERROR : While handling File"));
                        } // if (result != 0)
                    } // if (fileName != "-1")
                } // while (fileName != "-1")
            
                DEBUG_PRINT(TYPE_INFO, STYLE_END, ("Test Mode"));
            } // else if (mode == "test")
        } // if (mode != "-1")
    } // while (mode != "-1")

    return 0;
}

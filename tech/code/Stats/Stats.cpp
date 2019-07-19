
# include "Stats.h"

double Stats::getAverage()
{
    return average;
}

double Stats::getMinimum()
{
    return minimum;
}

double Stats::getQuartile1()
{
    return quartile1;
}

double Stats::getMedian()
{
    return median;
}

double Stats::getQuartile3()
{
    return quartile3;
}

double Stats::getMaximum()
{
    return maximum;
}

double Stats::getVariance()
{
    return variance;
}

int Stats::compute(std::vector<double> dataVector)
{
    int result = 1;
    
    elementsNb = dataVector.size();
    std::sort(dataVector.begin(), dataVector.end());

    minimum = dataVector[0];
    quartile1 = dataVector[elementsNb / 4];
    median = dataVector[elementsNb / 2];
    quartile3 = dataVector[3 * elementsNb / 4];
    maximum = dataVector[elementsNb - 1];

    result = 0;

    return result;
}
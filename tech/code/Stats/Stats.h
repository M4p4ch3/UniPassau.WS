
# if (!defined(STATS_H))
# define STATS_H

# include <vector>
# include <algorithm>

class Stats
{
    private:
    
    int elementsNb = 0;
    double average = 0.0;
    double minimum = 0.0;
    double quartile1 = 0.0;
    double median = 0.0;
    double quartile3 = 0.0;
    double maximum = 0.0;
    double variance = 0.0;

    public:

    double getAverage();
    double getMinimum();
    double getQuartile1();
    double getMedian();
    double getQuartile3();
    double getMaximum();
    double getVariance();

    int compute(std::vector<double> dataVector);
};

# endif // !defined(STATS_H)
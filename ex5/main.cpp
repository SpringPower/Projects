#include <iostream>
#include <random>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <limits>
#include <fstream>

using namespace std;

typedef double (* Generator)();
typedef double (* Distrubtion)(Generator);

double randomGenerator()
{
    double dVal = (double)random();

    return dVal/RAND_MAX;
}

double FakeExponential(Generator pfnGenerator)
{
    static const double g_dLoge = log(2.71828182845904523536028747135266249775724709369995);

    double dRand = pfnGenerator();

    // -(1/1)*ln(u) == - log(u)/log(e)
    return - log(dRand)/g_dLoge;
}

double FakePareto(Generator pfnGenerator)
{
    // 1 / (u^(1/1)) == 1/u
    return 1/pfnGenerator();
}

double RealExponential(Generator pfnGenerator)
{
    static std::mt19937_64 tRand;
    static std::exponential_distribution<double> tDist(1);

    (void)pfnGenerator;

    return tDist(tRand);
}
static std::mt19937_64 g_tRandPareto;
double RealPareto(Generator pfnGenerator)
{
    (void)pfnGenerator;

    return 1/(((double)g_tRandPareto()) / std::numeric_limits<long unsigned int>::max());
}

void RunExperiment(
        Generator pfnGenerator,
        Distrubtion pfnDistribution,
        unsigned long nSamples,
        double &rdAverage,
        double &rdSTD)
{
    double dAverage = 0;
    double dSTD = 0;
    std::vector<double> aResults;

    aResults.reserve(nSamples);

    for (unsigned long i=0; i<nSamples; ++i)
    {
        double dResult = pfnDistribution(pfnGenerator);
        dAverage += dResult/nSamples;
        aResults.push_back(dResult);
    }

    for (double dVal: aResults)
    {
        dSTD += ((dVal - dAverage)*(dVal - dAverage)) / nSamples;
    }
    dSTD = sqrt(dSTD);

    rdAverage = dAverage;
    rdSTD = dSTD;
}

void Dump(
        Generator pfnGenerator,
        Distrubtion pfnDistribution,
        unsigned long nSamples,
        std::string strFilename)
{
    fstream file;
    file.open(strFilename, std::fstream::in | std::fstream::out | std::fstream::app);

    for (unsigned long i=0; i<nSamples; ++i)
    {
        file<<pfnDistribution(pfnGenerator)<<"\n";
    }
    file.flush();
    file.close();
}

int main()
{
    unsigned int auiSrandom[] = {2039, 987543, 92934029, 43242938, 2};
    long alSrand48[] = {2039, 987543, 92934029, 43242938, 2};
    unsigned long aulSamples[] = {10, 1000, 100000, 10000000};

    /*printf("exponential\n");
    printf("srandom\n");
    for (auto samples: aulSamples)
    {
        for (auto seed: auiSrandom)
        {
            double dAvg, dStd;

            srandom(seed);

            RunExperiment(randomGenerator, FakeExponential, samples, dAvg, dStd);

            printf("%9lu,%1.3f,%1.3f\n",samples,dAvg, dStd);
        }
    }

    printf("srand48\n");
    for (auto samples: aulSamples)
    {
        for (auto seed: alSrand48)
        {
            double dAvg, dStd;

            srand48(seed);

            RunExperiment(drand48, FakeExponential, samples, dAvg, dStd);

            printf("%9lu,%1.3f,%1.3f\n",samples,dAvg, dStd);
        }
    }

    printf("real\n");
    for (auto samples: aulSamples)
    {
        double dAvg, dStd;

        RunExperiment(randomGenerator, RealExponential, samples, dAvg, dStd);

        printf("%9lu,%1.3f,%1.3f\n",samples,dAvg, dStd);
    }

    printf("pareto\n");
    printf("exponential\n");
    printf("srandom\n");
    for (auto samples: aulSamples)
    {
        for (auto seed: auiSrandom)
        {
            double dAvg, dStd;

            srandom(seed);

            RunExperiment(randomGenerator, FakePareto, samples, dAvg, dStd);

            printf("%9lu,%1.3f,%1.3f\n",samples,dAvg, dStd);
        }
    }

    printf("srand48\n");
    for (auto samples: aulSamples)
    {
        for (auto seed: alSrand48)
        {
            double dAvg, dStd;

            srand48(seed);

            RunExperiment(drand48, FakePareto, samples, dAvg, dStd);

            printf("%9lu,%1.3f,%1.3f\n",samples,dAvg, dStd);
        }
    }

    printf("real\n");
    for (auto samples: aulSamples)
    {
        double dAvg, dStd;

        RunExperiment(randomGenerator, RealPareto, samples, dAvg, dStd);

        printf("%9lu,%1.3f,%1.3f\n",samples,dAvg, dStd);
    }*/

    srand48(92934029);
    Dump(drand48, FakeExponential, 100000, "Exp.csv");
    srand48(92934029);
    Dump(drand48, FakePareto, 100000, "Par.csv");

    return 0;
}


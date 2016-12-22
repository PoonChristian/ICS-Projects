#include "EdgeWeights.hpp"

double distanceInMiles(const RoadSegment& r)
{
    return r.miles;
}

double timeInHours(const RoadSegment& r)
{
    return r.miles / r.milesPerHour;
}


void printTime(double time)
{
    double h = time;
    double m = h * 60;

    int hours = 0;
    int minutes = 0;
    double seconds = m * 60;

    if (m > 60.0)
    {
        hours = static_cast<int>(h);
        minutes = m - hours * 60;
        seconds = seconds - m * 60;

        std::cout << hours << " hrs " << minutes << " mins " <<
        std::setprecision(3) << seconds << " secs";
    }
    else if (seconds > 60.0)
    {
        minutes = static_cast<int>(m);
        seconds = seconds - minutes * 60;

        std::cout << minutes << " mins " << std::setprecision(3) << seconds << " secs";
    }
    else
    {
        std::cout << std::setprecision(3) << seconds << " secs";
    }
}

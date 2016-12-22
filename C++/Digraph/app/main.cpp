// main.cpp
//
// ICS 46 Spring 2016
// Project #4: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.

#include "RoadMapReader.hpp"
#include "TripReader.hpp"
#include "EdgeWeights.hpp"


int main()
{
    InputReader in(std::cin);

    RoadMapReader rin;
    RoadMap roadmap = rin.readRoadMap(in);

    TripReader tin;
    std::vector<Trip> trips = tin.readTrips(in);

    for (int i = 0; i < trips.size(); ++i)
    {
        std::vector<int> directions;
        directions.push_back(trips[i].endVertex);
        int currentVertex = trips[i].endVertex;
        if (trips[i].metric == TripMetric::Distance)
        {
            std::cout << "Shortest distance from " <<
            roadmap.vertexInfo(trips[i].startVertex) <<
            " to " << roadmap.vertexInfo(trips[i].endVertex) << std::endl;

            std::map<int, int> shortestPaths = roadmap.findShortestPaths(trips[i].startVertex, distanceInMiles);
            std::vector<double> distances;
            double totalMiles = 0.0;

            while (currentVertex != trips[i].startVertex)
            {
                directions.push_back(shortestPaths.at(currentVertex));
                currentVertex = shortestPaths.at(currentVertex);
            }

            std::cout << "  Begin at " << roadmap.vertexInfo(directions.back()) << std::endl;
            int fromVertex = directions.back();
            directions.pop_back();

            while (directions.size() > 0)
            {   
                int toVertex = directions.back(); 
                directions.pop_back();

                std::cout << "  Continue to " << roadmap.vertexInfo(toVertex) << " (" <<
                roadmap.edgeInfo(fromVertex, toVertex).miles << " miles)" << std::endl;

                distances.push_back(roadmap.edgeInfo(fromVertex, toVertex).miles);
                fromVertex = toVertex;
            }

            for (int j = 0; j < distances.size(); ++j)
            {
                totalMiles += distances[j];
            }

            std::cout << "Total distance: " << totalMiles << " miles" << std::endl;
        }
        else
        {
            std::cout << "Shortest driving time from " <<
            roadmap.vertexInfo(trips[i].startVertex) <<
            " to " << roadmap.vertexInfo(trips[i].endVertex) << std::endl;

            std::map<int, int> shortestPaths = roadmap.findShortestPaths(trips[i].startVertex, timeInHours);
            std::vector<double> times;
            double totalTime = 0.0;

            while (currentVertex != trips[i].startVertex)
            {
                directions.push_back(shortestPaths.at(currentVertex));
                currentVertex = shortestPaths.at(currentVertex);
            }
            
            std::cout << "  Begin at " << roadmap.vertexInfo(directions.back()) << std::endl;
            int fromVertex = directions.back();
            directions.pop_back();

            while (directions.size() > 0)
            {
                int toVertex = directions.back();
                directions.pop_back();
                double time = timeInHours(roadmap.edgeInfo(fromVertex, toVertex));

                std::cout << "  Continue to " << roadmap.vertexInfo(toVertex) << " (" <<
                roadmap.edgeInfo(fromVertex, toVertex).miles << " miles @ " <<
                roadmap.edgeInfo(fromVertex, toVertex).milesPerHour << "mph = ";
                printTime(time);
                std::cout << ")" << std::endl;

                times.push_back(time);
                fromVertex = toVertex;
            }

            for (int j = 0; j < times.size(); ++j)
            {
                totalTime += times[j];
            }

            std::cout << "Total time: ";
            printTime(totalTime);
            std::cout << std::endl;

        }
        std::cout << std::endl;
    }

    return 0;
}


#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <set>
#include <cmath>
#include <optional>

struct BusStats {
  int stop_count;
  int unique_stop_count;
  double route_distance;
};

struct Coords {
  long double latitude;
  long double longitude;
};

//---------------------Pattern Strategy-----------------------//
class Strategy {
public:
  virtual ~Strategy() = default;
  virtual int ComputeStopsOnRoute(const std::vector<std::string>& stops) const = 0;

  virtual double ComputeDistanceOnRoute(const std::vector<std::string>& stops,
		  const std::unordered_map<std::string, Coords>& stop_to_coords) const  = 0;

  double ComputeDistance(const Coords& lhs, const Coords& rhs) const;

  int ComputeUniqueStopsOnRoute(const std::vector<std::string>& stops) const;
};

class CycleStrategy : public Strategy {
public:
  int ComputeStopsOnRoute(const std::vector<std::string>& stops) const override {
    return stops.size();
  }

  double ComputeDistanceOnRoute(const std::vector<std::string>& stops,
		  const std::unordered_map<std::string, Coords>& stop_to_coords) const override {
    double sum = 0;
	for(auto it = begin(stops); it != prev(end(stops)); ++it) {
	  double dist = ComputeDistance(stop_to_coords.at(*it), stop_to_coords.at(*next(it)));
      sum += dist;
    }
	return sum;
  }
};

class NotCycleStrategy : public Strategy {
public:
  int ComputeStopsOnRoute(const std::vector<std::string>& stops) const override {
    return stops.size() * 2 - 1;
  }

  double ComputeDistanceOnRoute(const std::vector<std::string>& stops,
		  const std::unordered_map<std::string, Coords>& stop_to_coords) const override {
	double sum = 0;
	for(auto it = begin(stops); it != prev(end(stops)); ++it) {
	  sum += ComputeDistance(stop_to_coords.at(*it), stop_to_coords.at(*next(it)));
	}
	return 2 * sum;
  }
};
//---------------------Pattern Strategy-----------------------//


//---------------------Business Logic of Programm----------------//
class RouteManager {
public:
  void SetStopCoords(const std::string& stop_name, Coords coords) {
	  stop_to_coords[stop_name] = coords;
  }

  void SetBusRoute(const std::string& bus_name, const std::vector<std::string>& stops) {
	BusStats stats;
	stats.stop_count = strategy->ComputeStopsOnRoute(stops);
	stats.unique_stop_count = strategy->ComputeUniqueStopsOnRoute(stops);
	stats.route_distance = strategy->ComputeDistanceOnRoute(stops, stop_to_coords);
    bus_stats[bus_name] = stats;
  }

  void SetStrategy(Strategy* strategy_) {
	strategy = strategy_;
  }

  std::optional<BusStats> GetBusStats(const std::string& bus_name) {
	if(bus_stats.count(bus_name)) {
	  return bus_stats.at(bus_name);
	}
	return std::nullopt;
  }

private:
  std::unordered_map<std::string, Coords> stop_to_coords;
  std::unordered_map<std::string, BusStats> bus_stats;
  Strategy* strategy;
};
//---------------------Business Logic of Programm----------------//

//---------------------Tests-----------------------------------//
void TestComputeDistance();
void TestBusStats();
//---------------------Tests-----------------------------------//

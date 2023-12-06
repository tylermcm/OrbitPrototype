#include "satellite.h"

// data holding all of the initial values of all of the gps instances needed



std::vector<gpsInitialVals> gpsData = {
	{{0.0, 26560000.0}, -3880.0, 0.0},
	{{23001634.72, 13280000.0}, -1940.00, 3360.18},
	{{23001634.72, -13280000.0}, 1940.00, 3360.18},
	{{0.0, -26560000.0}, 3880.0, 0.0},
	{{-23001634.72, -13280000.0}, 1940.00, -3360.18},
	{{-23001634.72, 13280000.0}, -1940.00, -3360.18}
};

const std::vector<gpsInitialVals>& Satellite::getGpsData() {
	return gpsData;
}

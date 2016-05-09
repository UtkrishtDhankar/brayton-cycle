#ifndef COMBUSTION_CHAMBER_H
#define COMBUSTION_CHAMBER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double efficiency = 0.98;	// efficiency of combustion
const double c_fuel = 4200000;	// calorific value of fuel in J/kg K.
const double c_air = 1005;	// specific heat of air at const p in J/kg K.

struct combustion_chamber {
	double p;

	double t_in;
	double t_out;

	double req_flow_rate;
};

double calc_fuel_flow_rate(
	double t_in,		// desired outlet temperature of the gas in K
	double t_out,		// inlet temperature of the gas in K
	double gas_flow_rate	// flow rate of the gas in kg/s
);

struct combustion_chamber simulate_combustion_chamber(
	double t_in,		// desired outlet temperature of the gas in K
	double p,		// pressure at which to use combustion chamber
	double t_out,		// inlet temperature of the gas in K
	double gas_flow_rate	// flow rate of the gas in kg/s
);

#endif

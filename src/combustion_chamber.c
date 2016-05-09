#include "combustion_chamber.h"

double efficiency = 0.98;	// efficiency of combustion
double c_fuel = 4200000;	// calorific value of fuel in J/kg K.
double c_air = 1005;	// specific heat of air at const p in J/kg K.

double calc_fuel_flow_rate(
	double t_in,		// desired outlet temperature of the gas in K
	double t_out,		// inlet temperature of the gas in K
	double gas_flow_rate	// flow rate of the gas in kg/s
) {
	return gas_flow_rate * (c_air / c_fuel) * (t_out - t_in) / efficiency;
}

struct combustion_chamber simulate_combustion_chamber(
	double t_in,		// desired outlet temperature of the gas in K
	double p,		// pressure at which to use combustion chamber
	double t_out,		// inlet temperature of the gas in K
	double gas_flow_rate	// flow rate of the gas in kg/s
) {
	struct combustion_chamber cc;

	cc.p = p;
	cc.t_in = t_in;
	cc.t_out = t_out;

	cc.req_flow_rate = calc_fuel_flow_rate(t_in, t_out, gas_flow_rate);

	return cc;
}

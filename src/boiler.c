#include "boiler.h"

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
	struct combustion_chamber b;

	b.p = p;
	b.t_in = t_in;
	b.t_out = t_out;

	b.req_flow_rate = calc_fuel_flow_rate(t_in, t_out, gas_flow_rate);

	return b;
}

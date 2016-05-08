#ifndef BOILER_H
#define BOILER_H

struct boiler {
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

struct boiler simulate_boiler(
	double t_in,		// desired outlet temperature of the gas in K
	double p,		// pressure at which to use boiler
	double t_out,		// inlet temperature of the gas in K
	double gas_flow_rate	// flow rate of the gas in kg/s
);

#endif

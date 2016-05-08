#include "heat-exchanger.h"

/*
   *Calculates the required flow rate for the gas
 */
double calc_fuel_flow_rate(
	double t_in,            // Temperature of gas entering from compressor in K.
	double t_out,           // Temperature of gas leaving the heat exchanger in K.
	double gas_flow_rate    // Flow rate of the gas in kg/s
	)
{
	return gas_flow_rate * (c_air / c_fuel) * (t_out - t_in) / efficiency;
}

/*
   *Simulates the heat-exchanger for the given inputs.
 */
struct boiler simulate_boiler(
	double t_in,            // Temperature of gas entering from compressor in K.
	double p,               // Pressure at which to use the heat exchanger.
	double t_out,           // Temperature of gas leaving the heat exchanger in K.
	double gas_flow_rate    // Flow rate of the gas in kg/s.
	)
{
	struct boiler b;

	b.p = p;
	b.t_in = t_in;
	b.t_out = t_out;

	b.req_flow_rate = calc_fuel_flow_rate(t_in, t_out, gas_flow_rate);

	return b;
}

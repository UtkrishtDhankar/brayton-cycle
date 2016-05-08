#ifndef HEAT_EXCHANGER_H
#define HEAT_EXCHANGER_H

const double efficiency = 0.98; // Efficiency of combustion
const double c_fuel = 4200000;  // Calorific value of fuel in J/kg K.
const double c_air = 1005;      // Specific heat of air at const p in J/kg K.

/*
   *Calculates the required flow rate for the gas
 */
struct boiler {
	double p;               // Pressure of heat exchanger in Pa.

	double t_in;            // Temperature of gas entering the heat exchanger in K.
	double t_out;           // Temperature of gas leaving the heat exchanger in K.

	double req_flow_rate;   //The required flow rate for the gas to flow through the heat exchanger in kg/s.
};

double calc_fuel_flow_rate(
	double t_in,            // Temperature of gas entering the heat exchnager in K.
	double t_out,           // Temperature of gas leaving the heat exchanger in K.
	double gas_flow_rate    // Flow rate of the gas in kg/s
	);

/*
   *Simulates the heat-exchanger for the given inputs.
 */
struct boiler simulate_boiler(
	double t_in,            // Temperature of gas entering from compressor in K.
	double p,               // Pressure at which to use the heat exchanger.
	double t_out,           // Temperature of gas leaving the heat exchanger in K.
	double gas_flow_rate    // Flow rate of the gas in kg/s.
	);

#endif

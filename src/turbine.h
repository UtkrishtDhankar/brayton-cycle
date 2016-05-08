#ifndef TURBINE_H
#define TURBINE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct turbine {
	double p_in;            // the pressure flowing in, in Pascals.
	double p_out;           // the pressure flowing out, in Pascals.

	double t_in;            // the temperature of air flowing in,
				// in Kelvin.
	double t_out;           // the temperature of air flowing out,
				// in Kelvin.

	double w_out;           // the amount of work required in Joules per
				// second.
	double exergy_gain;     // gain in exergy of the gas, in Joules per
				// second.
	double exergy_loss;     // loss of exergy in the stage, in Joules per
				// second.
};

/*
 * Prints the details of the turbine
 */
void print_turbine(struct turbine c);

/*
 * Simulates the turbine for given inputs.
 */
struct turbine *simulate_turbine(
	double p_comp,          // the inlet pressure/outlet pressure from compressor, in Pa.
	double t_inlet,         // the inlet temp, in K.
	double gamma,           // the gamma of the gas.
	double gas_flow_rate,   // the rate at which gas flows in, in kg/s.
	double molecular_mass,  // mass of 1 mol of gas molecules, in kg.
	double stage_efficiency // efficiency of each stage.
);


#endif

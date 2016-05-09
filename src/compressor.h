#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct compressor {
	double p_in; 		// the pressure flowing in, in Pascals.
	double p_out;		// the pressure flowing out, in Pascals.

	double t_in;		// the temperature of air flowing in,
				// in Kelvin.
	double t_out;		// the temperature of air flowing out,
				// in Kelvin.

	double w_req;		// the amount of work required in Joules per
				// second.
	double exergy_gain;	// gain in exergy of the gas, in Joules per
				// second.
	double exergy_loss;	// loss of exergy in the stage, in Joules per
				// second.
};

/*
 * Prints the details of the compressor
 */
void print_compressor(struct compressor c);

/*
 * Computes and returns the number of stages to reach given pressure ratio rp.
 */
int find_num_stages(double desired_rp);

/*
 * Simulates the compressor for given inputs.
 */
struct compressor *simulate_compressor(
	int num_stages,		// the number of stages of the compressor.
	double p_atm,		// the inlet pressure, in Pa.
	double t_inlet,		// the inlet temp, in K.
	double gamma,		// the gamma of the gas.
	double gas_flow_rate,	// the rate at which gas flows in, in kg/s.
	double molecular_mass,	// mass of 1 mol of gas molecules, in kg.
	double stage_efficiency,// efficiency of each stage.
	double desired_rp	// The desired pressure ratio of the compressor
);


#endif

#ifndef TURBINE_H
#define TURBINE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double max_pressure_ratio = 1.2;
const double r_univ = 8.314;                                    // in SI units.
const int num_stages = 8;
const double eta_isen = 0.92;                                   //Isentropic efficiency
const double eta_comb = 0.98;                                   //Efficiency of combustion
const double p_final = 108000;                                  //Final pressure.

struct turbine {
	double p_in;            // the pressure flowing in, in Pascals.
	double p_out;           // the pressure flowing out, in Pascals.

	double t_in;            // the temperature of air flowing in,
	                        // in Kelvin.
	double t_out;           // the temperature of air flowing out,
	                        // in Kelvin.

	double w_req;           // the amount of work required in Joules per
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

#include "turbine.h"

/*
 * Constants used by the turbine model.
 *
 * Numbers in square brackets refer to the reference list in SOURCES.md.
 */

// Universal molar gas constant, in J/(mol K) [1]. Duplicated from
// compressor.c; the two copies should eventually be shared through a single
// header.
static double r_univ = 8.314;

// Number of turbine stages. This is a modelling choice, not a sourced
// constant: it is picked so that the expansion is split into stages of a
// believable size for the pressure ratios simulated. Note that main.c assumes
// this value when it sums the stage work, so the two must be changed together.
static int num_stages = 8;

// Final (exhaust) pressure of the turbine, in Pa.
// NOTE: this is an assumed value, not a sourced property, and it looks wrong:
// 108 000 Pa is above the 100 000 Pa compressor inlet pressure used in main.c,
// which would mean the turbine expands to a pressure higher than the
// compressor inlet. A real exhaust sits at or slightly below atmospheric. It is
// left as it is here because changing it changes the simulation output.
static double p_final = 108000;

/*
 * Prints the details of the turbine
 */
void print_turbine(struct turbine turb)
{
	printf("P_in = %.0f Pa\tT_in = %.2f K\tP_out = %.0f Pa\tT_out = %.2f "
		"K\tW_out = %.2f J/s\tX_loss = %.2f J/s\tX_dest = %.2f J/s\n",
		turb.p_in,
		turb.t_in,
		turb.p_out,
		turb.t_out,
		turb.w_out,
		turb.exergy_loss,
		turb.exergy_dest
		);
}

/*
 * Finds pressure ratio of 1 stage
 */
double press_rat(double p_comp)
{
	return pow(p_final / p_comp, 1.0 / num_stages);
}

/*
 * Simulates the turbine for given inputs.
 */
struct turbine *simulate_turbine(
	double p_comp,          // the inlet pressure/output from compressor, in Pa.
	double t_inlet,         // the inlet temp, in K.
	double gamma,           // the gamma of the gas.
	double gas_flow_rate,   // the rate at which gas flows in, in kg/s.
	double molecular_mass,  // mass of 1 mol of gas molecules, in kg.
	double stage_efficiency // efficiency of each stage.
	)
{
	struct turbine *tb = malloc(num_stages * sizeof(*tb));

	// input pressure and temperature from compressor.
	// input temperature from the compressor.
	double p_prev = p_comp;
	double t_prev = t_inlet;
	double max_pressure_ratio = press_rat(p_comp);

	for (int i = 0; i < num_stages; i++) {
		tb[i].p_in = p_prev;
		tb[i].t_in = t_prev;

		tb[i].p_out = tb[i].p_in * max_pressure_ratio;

		// assuming that turbine is adiabatic
		tb[i].t_out = pow(1 / max_pressure_ratio, (1 - gamma) / gamma)
				* tb[i].t_in;

		p_prev = tb[i].p_out;
		t_prev = tb[i].t_out;

		// Assuming turbine work is integral Vdp, with ineficiencies.
		tb[i].w_out = - (stage_efficiency)
				* (gas_flow_rate / molecular_mass)
				* r_univ * (tb[i].t_out - tb[i].t_in) * gamma / (gamma - 1);

		tb[i].exergy_loss = (1/ stage_efficiency) * tb[i].w_out;
		tb[i].exergy_dest = tb[i].exergy_loss - tb[i].w_out;
	}

	return tb;
}

#include "turbine.h"

static double r_univ = 8.314;		// in SI units.
static int num_stages = 8;
static double p_final = 108000;		//Final pressure.
/*
 * Prints the details of the turbine
 */
void print_turbine(struct turbine turb)
{
	printf("P_in = %.0f Pa\tT_in = %.2f K\tP_out = %.0f Pa\tT_out = %.2f "
		"K\tW_req = %.2f J/s\tX_gain = %.2f J/s\tX_loss = %.2f J/s\n",
		turb.p_in,
		turb.t_in,
		turb.p_out,
		turb.t_out,
		turb.w_req,
		turb.exergy_gain,
		turb.exergy_loss
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
		tb[i].w_req = (1 / stage_efficiency)
				* (gas_flow_rate / molecular_mass)
				* r_univ * (tb[i].t_out - tb[i].t_in) * gamma / (gamma - 1);

		tb[i].exergy_gain = stage_efficiency * tb[i].w_req;
		tb[i].exergy_loss = tb[i].w_req - tb[i].exergy_gain;
	}

	return tb;
}

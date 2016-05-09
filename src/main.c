#include "compressor.h"
#include "boiler.h"
#include "turbine.h"

#include <stdlib.h>
#include <stdio.h>

int main()
{
	double desired_rp, turbine_t_in;
	printf("Enter the compressor pressure ratio and turbine inlet temperature: ");
	scanf("%lf %lf", &desired_rp, &turbine_t_in);


	int c_num_stages = find_num_stages(desired_rp);

	double p_atm = 100000;
	double comp_t_inlet = 273.15 + 15;
	double gamma = 1.4;
	double gas_flow_rate = 1;
	double molecular_mass = 0.025;
	double stage_efficiency = 0.92;

	struct compressor *c_stages =
	simulate_compressor(
		c_num_stages,
		p_atm,
		comp_t_inlet,
		gamma,
		gas_flow_rate,
		molecular_mass,
		stage_efficiency,
		desired_rp);

	struct boiler b = simulate_boiler(
		c_stages[c_num_stages - 1].t_out,
		c_stages[c_num_stages - 1].p_out,
		turbine_t_in,
		gas_flow_rate);
	
	struct turbine *t_stages = simulate_turbine(
		b.p,
		b.t_out,
		gamma,
		gas_flow_rate,
		molecular_mass,
		stage_efficiency);

	printf("\n\n---- The Compressor Stages ----\n");
	for (int i = 0; i < c_num_stages; i++)
		print_compressor(c_stages[i]);

	printf("\n\n---- The Turbine Stages ----\n");
	for (int i = 0; i < 8; i++)
		print_turbine(t_stages[i]);

	double n;
	double w_c = 0;
	double w_t = 0;
	double heat_added;
	double specific_heat = 4200000;

	for (int i = 0; i < c_num_stages; i++)
		w_c += c_stages[i].w_req;
	for (int i = 0; i < 8; i++)
		w_t += t_stages[i].w_out;
	heat_added = specific_heat * b.req_flow_rate;

	n = (w_t - w_c) / heat_added;

	printf("\n\nw_t = %lf\t w_c = %lf\t heat added = %lf\n", w_t, w_c, heat_added);
	printf("efficiency = %lf\n", n);

	free(c_stages);
	free(t_stages);
	return 0;
}

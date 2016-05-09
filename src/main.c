#include "compressor.h"
#include "boiler.h"
#include "turbine.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_usage()
{
	printf("Usage:	./brayton-cycle [option]\n\n"
	       "-v, --verbose\tPrints information about what is being done.\n"
	       "-h, --help\tPrints this usage/help text.\n");
}

int main(int argc, char *argv[])
{
	if (((argc == 2 && (strcmp(argv[1], "--help") == 0
			    || strcmp(argv[1], "-h") == 0)) || argc > 2)
	    || (argc == 2 && !(strcmp(argv[1], "--verbose") == 0
			       || strcmp(argv[1], "-v") == 0))) {
		print_usage();
		return 0;
	}

	double turbine_t_in;

	printf("Enter the Turbine Inlet Temperature (T.I.T) in KELVIN: ");
	scanf("%lf", &turbine_t_in);

	FILE* data_file = fopen("data", "w");

	for (double desired_rp = 14; desired_rp <= 34; desired_rp += 1) {
		int c_num_stages = find_num_stages(desired_rp);

		double p_atm = 100000;
		double comp_t_inlet = 273.15 + 15;
		double gamma = 1.4;
		double gas_flow_rate = 1;
		double molecular_mass = 0.02897;
		double stage_efficiency = 0.92;

		struct compressor *c_stages = simulate_compressor(
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

		if (argc == 2 &&
		    (strcmp(argv[1], "--verbose") == 0
		     || strcmp(argv[1], "-v") == 0)) {
			printf("\n\n%i) Turbine inlet temp = %lf K\t Pressure ratio = %lf\n",
			       ((int)(desired_rp - 14)), turbine_t_in, desired_rp);

			printf("\n\t\t\t---- The Compressor Stages ----\n"
			       "==============================================="
			       "=================================\n");
			for (int i = 0; i < c_num_stages; i++)
				print_compressor(c_stages[i]);

			printf("\n\n\t\t\t---- The Turbine Stages ----\n"
			       "==============================================="
			       "=================================\n");
			for (int i = 0; i < 8; i++)
				print_turbine(t_stages[i]);

			printf("\n\nWork (Turbine) = %lf J/s\n"
			       "Work (Compressor) = %lf J/s\n"
			       "Heat Added = %lf J\n", w_t, w_c, heat_added);
			printf("Efficiency = %lf\n", n);
		}
		fprintf(data_file, "%f %f\n", n, desired_rp);
		
		free(c_stages);
		free(t_stages);
	}

	fclose(data_file);

	return 0;
}

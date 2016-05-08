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

	struct compressor *c_stages =
	simulate_compressor(
		c_num_stages,
		100000,
		273 + 15,
		1.4,
		1,
		0.025,
		0.92);

	struct boiler b = simulate_boiler(
		c_stages[c_num_stages - 1].t_out,
		c_stages[c_num_stages - 1].p_out,
		turbine_t_in,
		1);

	struct turbine *t_stages = simulate_turbine(
		b.p,
		b.t_out,
		1.4,
		1,
		24,
		0.92);

	printf("\n\n---- The Compressor Stages ----\n");
	for (int i = 0; i < c_num_stages; i++)
		print_compressor(c_stages[i]);

	printf("\n\n---- The Turbine Stages ----\n");
	for (int i = 0; i < 8; i++)
		print_turbine(t_stages[i]);

	free(c_stages);
	return 0;
}

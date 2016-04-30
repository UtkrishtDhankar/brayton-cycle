const double efficiency = 0.98;	// efficiency of combustion
const double c_fuel = 4200000;	// calorific value of fuel in J/kg K.
const double c_air = 1005;	// specific heat of air at const p in J/kg K.

struct boiler {
	double p_in;
	double p_out;

	double t_in;
	double t_out;
};

double calc_fuel_flow_rate(
	double t_in,		// desired outlet temperature of the gas in K
	double t_out,		// inlet temperature of the gas in K
	double gas_flow_rate	// flow rate of the gas in kg/s
)
{
	return gas_flow_rate * (c_air / c_fuel) * (t_out - t_in) / efficiency;
}


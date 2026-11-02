#include "combustion_chamber.h"

/*
 * Constants used by the combustion chamber model.
 *
 * Numbers in square brackets refer to the reference list in SOURCES.md. These
 * are properties of the working fluid or of the component, and are held fixed
 * for the whole pressure ratio sweep in main.c.
 */

// Efficiency of combustion. Practical gas turbine combustors achieve 0.98 -
// 0.99 combustion efficiency [5].
double efficiency = 0.98;

// Lower calorific (heating) value of the fuel, in J/kg. 42.0 MJ/kg is a round
// figure for a liquid hydrocarbon fuel such as diesel or kerosene, whose lower
// heating value is 42.6 - 43.0 MJ/kg [6].
// (The unit used to be given here as "J/kg K", which is wrong: a calorific
// value is energy per unit mass, not per unit mass per kelvin.)
double c_fuel = 4200000;

// Specific heat of air at constant pressure, in J/(kg K), at 300 K [3].
// Held constant at its 300 K value (the cold air standard assumption) even
// though the real c_p rises to about 1.15 kJ/(kg K) at turbine inlet
// temperatures; see the note in SOURCES.md.
double c_air = 1005;

double calc_fuel_flow_rate(
	double t_in,		// inlet temperature of the gas in K
	double t_out,		// desired outlet temperature of the gas in K
	double gas_flow_rate	// flow rate of the gas in kg/s
) {
	return gas_flow_rate * (c_air / c_fuel) * (t_out - t_in) / efficiency;
}

struct combustion_chamber simulate_combustion_chamber(
	double t_in,		// inlet temperature of the gas in K
	double p,		// pressure at which to use combustion chamber
	double t_out,		// desired outlet temperature of the gas in K
	double gas_flow_rate	// flow rate of the gas in kg/s
) {
	struct combustion_chamber cc;

	cc.p = p;
	cc.t_in = t_in;
	cc.t_out = t_out;

	cc.req_flow_rate = calc_fuel_flow_rate(t_in, t_out, gas_flow_rate);

	return cc;
}

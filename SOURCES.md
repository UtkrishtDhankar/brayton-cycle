# Sources for the constants used in this simulation

Every numeric constant in `src/` carries a bracketed reference number in its
comment, which points at an entry in the list below. Values that are *not*
physical properties but modelling choices are marked as such, and are listed
separately at the end so they are not mistaken for sourced data.

[1] **Universal molar gas constant** —
    *CODATA Recommended Values of the Fundamental Physical Constants*, NIST,
    2018: $$R = 8.314\,462\,618\ldots\ \mathrm{J\,mol^{-1}\,K^{-1}}$$
    (exact in the 2019 SI, since it is defined through the Boltzmann
    constant). The simulation uses the usual three-decimal rounding, 8.314.
    <https://physics.nist.gov/cgi-bin/cuu/Value?r>

[2] **Molar mass of air** — Y. A. Çengel and M. A. Boles, *Thermodynamics: An
    Engineering Approach*, Appendix 1, Table A-1 (molar mass, gas constant and
    critical-point properties): air $$M = 28.97\ \mathrm{kg/kmol}$$ and
    $$R_\text{air} = 0.2870\ \mathrm{kJ\,kg^{-1}\,K^{-1}}$$.

[3] **Specific heat and ratio of specific heats of air** — Çengel and Boles,
    Table A-2 (ideal-gas specific heats of various common gases), air at
    300 K: $$c_p = 1.005\ \mathrm{kJ\,kg^{-1}\,K^{-1}}$$,
    $$c_v = 0.718\ \mathrm{kJ\,kg^{-1}\,K^{-1}}$$, $$k = \gamma = 1.400$$.

[4] **Axial compressor stage pressure ratio and stage efficiency** —
    M. P. Boyce, *Gas Turbine Engineering Handbook*, chapter 2, Table 1
    ("Axial flow compressor characteristics"): industrial subsonic stages run
    at a pressure ratio of 1.05–1.2 per stage with 88–92 % efficiency per
    stage; transonic aerospace stages run at 1.15–1.6 with 80–85 %.
    The same chapter states the pressure rise per stage is of the order of
    1.1:1 to 1.4:1.
    <https://www.netl.doe.gov/sites/default/files/gas-turbine-handbook/2-0.pdf>

[5] **Component efficiencies** — H. I. H. Saravanamuttoo, G. F. C. Rogers,
    H. Cohen, P. V. Straznicky and A. C. Nix, *Gas Turbine Theory*, 7th ed.,
    Pearson: practical gas turbine component efficiencies of 85–90 % are
    typical (§1); combustion chamber performance is treated in §6.5 and
    turbine stage performance in §7.4.

[6] **Calorific (heating) value of the fuel** — lower heating value of liquid
    hydrocarbon fuels: U.S. conventional diesel 42.79 MJ/kg, low-sulfur diesel
    42.61 MJ/kg, kerosene 43.0 MJ/kg. Sources: *Lower and Higher Heating Values
    of Gas, Liquid and Solid Fuels* (GREET-derived table, University of
    Illinois) and the Engineering ToolBox table "Fossil vs. Alternative Fuels —
    Energy Content".
    <https://www.engineeringtoolbox.com/fossil-fuels-energy-content-d_1298.html>

[7] **Standard atmosphere** — ISO 2533:1975 *Standard Atmosphere*: sea-level
    pressure 101 325 Pa and sea-level temperature 288.15 K (15 °C).

## Values that are modelling choices, not sourced constants

These appear in the code with a comment saying so, so that a reader does not
look for a reference that does not exist:

- `num_stages` in `src/turbine.c` — the number of turbine stages (8). Chosen so
  that the expansion is split into stages of a plausible size for the pressure
  ratios simulated; `src/main.c` also assumes the value 8.
- `gas_flow_rate` in `src/main.c` — 1 kg/s. The cycle is linear in mass flow,
  so this only sets the scale of the absolute work and fuel-flow figures and
  has no effect on the efficiency.
- `p_final` in `src/turbine.c` — 108 000 Pa. This is an assumed exhaust
  pressure, and the value looks wrong: it is *higher* than the 100 000 Pa
  compressor inlet pressure used in `src/main.c`, which would mean the turbine
  expands to above the compressor inlet pressure. A real exhaust sits at or
  slightly below atmospheric. It has been left unchanged here because
  correcting it changes the simulation output.

## Known approximations in the model

- `c_air` is held at its 300 K value throughout. The real $$c_p$$ of air rises
  from 1.005 kJ/(kg·K) at 300 K to roughly 1.15 kJ/(kg·K) at 1500 K, so using
  a constant value under-predicts the fuel flow (and therefore over-predicts
  cycle efficiency) at high turbine inlet temperatures. This is the standard
  cold-air-standard assumption [3].
- `p_atm` is taken as 100 000 Pa (1 bar) rather than the ISO standard
  atmosphere of 101 325 Pa [7]. The difference is 1.3 % in inlet pressure.

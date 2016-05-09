# Brayton Cycle Readme
Brayton Cycle (`brayton-cycle`) is a piece of software written for the IC 142 Engineering Thermodynamics course. It simulates a gas turbine for different turbine inlet temperatures with compressor ratio varying from `14` to `34`.

To use this software, first clone the repo and go into the directory:
```
git clone https://github.com/FanaticalFighter/brayton-cycle.git
cd brayton-cycle
```

Then, compile the software. You'll need the standard `gcc` compiler and `make`. If you're running any modern Unix based operating system, this should either come preinstalled or be quite easy to install. Here's how to compile the project:
```
make
```

Now, to run the software, you simply execute the created executable. On Unix or Unix like systems:
```
./brayton-cycle
```

If you want to see detailed per stage energy and exergy statistics, please run the above with the `-v` option.  

You can run `make clean` to clean your directory of the executable. The executable will generate a file `data` that holds the simulation data for the plot.

To actually generate the plot, you'll need to run the supplied python script. To run this script, you'll need `matplotlib`, the python package, installed. You can see how to install that [here](http://matplotlib.org/index.html). To run this script and generate the plot, run the following command:
```
python plot.py
```

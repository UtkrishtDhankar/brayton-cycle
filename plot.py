import matplotlib.pyplot as plt

f = open("data")

efficiencies = []
pressure_ratios = []

for line in f:
	data = line.split(' ')
	efficiencies.append(float(data[0]))
	pressure_ratios.append(float(data[1]))

plt.plot(pressure_ratios, efficiencies)

plt.xlabel('Pressure Ratio')
plt.ylabel('Efficiency')
plt.title('Efficiency vs Compressor Pressure Ratio graph')
plt.grid(True)
plt.savefig("plot.png")
plt.show()

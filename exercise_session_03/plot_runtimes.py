import matplotlib.pyplot as plt


cores = [5, 30, 64, 90, 110, 120, 128]
times = [0.6674, 0.3493, 0.1585, 0.1248, 0.09418, 0.09368, 0.08847]


speedup = [times[0] / t for t in times]


ideal_speedup = [speedup[0] * (c / cores[0]) for c in cores]

plt.figure(figsize=(7, 5))
plt.plot(cores, speedup, 'o-', label="Measured Speedup", linewidth=2, markersize=6)
plt.plot(cores, ideal_speedup, '--', label="Ideal Linear Speedup", color='gray', linewidth=1.5)

plt.xlabel("Number of Cores", fontsize=12)
plt.ylabel("Speedup", fontsize=12)
plt.title("Speedup vs Number of Cores", fontsize=14)
plt.legend()
plt.grid(True, linestyle='--', alpha=0.6)
plt.tight_layout()
plt.savefig('speedup_plot.png', dpi=300)
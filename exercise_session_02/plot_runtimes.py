import matplotlib.pyplot as plt

threads = [1, 2, 5, 10, 20, 50, 100, 128]
times = [4.438, 4.481, 1.584, 1.221, 0.6168, 0.3499, 0.3426, 0.1211]

baseline_time = times[0]
speedup = [baseline_time / t for t in times]

plt.figure(figsize=(10, 6))
plt.plot(threads, speedup, 'o-', label='speedup')
plt.plot(threads, threads, ':', color='gray', label='line (ideal)')

plt.xlabel('threads')
plt.ylabel('speedup')
plt.grid(True)
plt.legend()
plt.xticks(threads)
plt.savefig('runtimes_plot.png')

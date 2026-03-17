import json
import matplotlib.pyplot as plt
import glob
import re
from collections import defaultdict

def plot_benchmarks():
    results = defaultdict(lambda: {'x': [], 'y': []})

    files = glob.glob("threads_*.json")
    files.sort(key=lambda x: int(re.search(r'threads_(\d+)', x).group(1)))

    if not files:
        return

    for file_path in files:
        thread_count = int(re.search(r'threads_(\d+)', file_path).group(1))

        with open(file_path, 'r') as f:
            data = json.load(f)

            for bench in data.get('benchmarks', []):
                name = bench['name']
                time_ms = bench['real_time'] / 1e6

                results[name]['x'].append(thread_count)
                results[name]['y'].append(time_ms)

    plt.figure(figsize=(10, 7))

    for name, values in results.items():
        plt.plot(values['x'], values['y'], marker='o', label=name, linewidth=1.5)

    plt.yscale('log')
    plt.xlabel("OMP_NUM_THREADS")
    plt.ylabel("Execution Time (ms)")
    plt.xticks(range(1, 13))
    plt.grid(True, which="both", ls="--", alpha=0.5)
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.tight_layout()

    plt.show()

if __name__ == "__main__":
    plot_benchmarks()
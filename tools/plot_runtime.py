"""Draw figures/runtime.png from the CPU times in the README.

    python3 tools/plot_runtime.py
"""
import os

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

INK, MUTED, GRID, AXIS = "#191919", "#666666", "#e7e7e7", "#c2c2c2"
ALGORITHMS = [                       # name, color (fixed order), marker
    ("Insertion sort", "#257de0", "o"),
    ("Merge sort", "#f47230", "s"),
    ("Bottom-up merge sort", "#00b894", "^"),
    ("Quick sort", "#f2a600", "D"),
    ("Randomized quick sort", "#ee7fac", "v"),
]
SIZES = [4000, 16000, 32000, 1000000]
# CPU time in ms, measured on the course Linux server. Columns follow ALGORITHMS.
TIMES = {
    "Random order (case1)": [
        [3.634, 1.576, 2.020, 1.154, 1.549],
        [45.408, 6.216, 8.197, 4.317, 6.063],
        [142.274, 9.656, 11.406, 6.884, 8.856],
        [90115.8, 169.265, 217.556, 117.763, 147.796],
    ],
    "Increasing order (case2)": [
        [0.111, 0.806, 1.274, 0.344, 1.057],
        [0.231, 2.593, 4.269, 0.989, 3.749],
        [0.278, 4.305, 6.488, 1.388, 5.086],
        [1.326, 58.782, 106.385, 28.472, 80.385],
    ],
    "Decreasing order (case3)": [
        [6.263, 0.820, 1.278, 0.334, 1.060],
        [77.339, 2.527, 4.699, 0.992, 3.646],
        [270.217, 3.989, 7.370, 1.864, 5.296],
        [196737, 66.247, 116.027, 28.523, 80.028],
    ],
}

plt.rcParams.update({
    "font.family": "DejaVu Sans", "font.size": 10, "text.color": INK,
    "axes.edgecolor": AXIS, "axes.labelcolor": MUTED, "axes.titlesize": 11, "axes.titleweight": "bold",
    "xtick.color": MUTED, "ytick.color": MUTED, "axes.spines.top": False, "axes.spines.right": False,
})

fig, axes = plt.subplots(1, 3, figsize=(13.5, 4.9), sharey=True)
for ax, (title, rows) in zip(axes, TIMES.items()):
    for k, (name, color, marker) in enumerate(ALGORITHMS):
        ax.plot(SIZES, [r[k] for r in rows], color=color, lw=2, marker=marker, ms=6.5,
                mec="white", mew=1.2, label=name)
    ax.set_xscale("log"); ax.set_yscale("log")
    ax.set_xlabel("Input size (numbers)")
    ax.grid(color=GRID, lw=0.8); ax.set_axisbelow(True)
    ax.set_title(title, loc="left")
axes[0].set_ylabel("CPU time (ms)")
# direct labels where one algorithm separates from the rest
axes[0].annotate("Insertion sort: 90 s", (1e6, 90115.8), xytext=(-10, 5), textcoords="offset points", ha="right", va="bottom", fontsize=9)
axes[1].annotate("Insertion sort: 1.3 ms", (1e6, 1.326), xytext=(4, -17), textcoords="offset points", ha="right", va="top", fontsize=9)
axes[2].annotate("Insertion sort: 197 s", (1e6, 196737), xytext=(-10, 5), textcoords="offset points", ha="right", va="bottom", fontsize=9)
axes[2].annotate("Quick sort: 29 ms", (1e6, 28.523), xytext=(4, -17), textcoords="offset points", ha="right", va="top", fontsize=9)
axes[0].set_ylim(0.05, 2e6)
handles, labels = axes[0].get_legend_handles_labels()
fig.legend(handles, labels, loc="lower center", ncol=5, frameon=False, bbox_to_anchor=(0.5, -0.01))
fig.tight_layout(rect=(0, 0.07, 1, 1))
os.makedirs(os.path.join(ROOT, "figures"), exist_ok=True)
fig.savefig(os.path.join(ROOT, "figures", "runtime.png"), dpi=160)

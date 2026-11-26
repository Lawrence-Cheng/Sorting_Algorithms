# Sorting Algorithms

C++ implementations of five sorting algorithms, with measurements of their running time and memory use on random, sorted, and reverse-sorted inputs of up to one million numbers.

This was Programming Assignment 1 of the Algorithms course (Fall 2025) at National Taiwan University, Department of Electrical Engineering.

## Algorithms

| Option | Algorithm | Notes |
|---|---|---|
| `-IS` | Insertion sort | In place |
| `-MS` | Merge sort | Top-down, recursive |
| `-BMS` | Bottom-up merge sort | Iterative, merges runs of width 1, 2, 4, ... |
| `-QS` | Quick sort | Hoare partition with a median-of-three pivot (first, middle, last) |
| `-RQS` | Randomized quick sort | Hoare partition with a uniformly random pivot |

The `-HS` (heap sort) option exists in the provided skeleton but is not implemented, because the assignment did not require it.

## Results

Measured on the course's Linux server. The cases are:

- **case1**: random order (average case)
- **case2**: increasing order (best case for insertion sort)
- **case3**: decreasing order (worst case for insertion sort)

### CPU time (ms)

| Input | IS | MS | BMS | QS | RQS |
|---|---|---|---|---|---|
| 4000.case1 | 3.634 | 1.576 | 2.020 | 1.154 | 1.549 |
| 4000.case2 | 0.111 | 0.806 | 1.274 | 0.344 | 1.057 |
| 4000.case3 | 6.263 | 0.820 | 1.278 | 0.334 | 1.060 |
| 16000.case1 | 45.408 | 6.216 | 8.197 | 4.317 | 6.063 |
| 16000.case2 | 0.231 | 2.593 | 4.269 | 0.989 | 3.749 |
| 16000.case3 | 77.339 | 2.527 | 4.699 | 0.992 | 3.646 |
| 32000.case1 | 142.274 | 9.656 | 11.406 | 6.884 | 8.856 |
| 32000.case2 | 0.278 | 4.305 | 6.488 | 1.388 | 5.086 |
| 32000.case3 | 270.217 | 3.989 | 7.370 | 1.864 | 5.296 |
| 1000000.case1 | 90,115.8 | 169.265 | 217.556 | 117.763 | 147.796 |
| 1000000.case2 | 1.326 | 58.782 | 106.385 | 28.472 | 80.385 |
| 1000000.case3 | 196,737 | 66.247 | 116.027 | 28.523 | 80.028 |

### Peak memory (KB)

| Input size | IS | MS | BMS | QS | RQS |
|---|---|---|---|---|---|
| 4,000 | 6,080 | 6,216 | 6,224 | 6,080 | 6,080 |
| 16,000 | 6,232 | 6,232 | 6,388 | 6,232 | 6,232 |
| 32,000 | 6,364 | 6,364 | 6,552 | 6,364 | 6,364 |
| 1,000,000 | 12,320 | 16,132 | 18,084 | 12,320 | 12,320 |

Memory was the same across the three cases for each size.

### Growth rate

Slope of the trendline of log(time) against log(input size):

| Case | IS | MS | BMS | QS | RQS |
|---|---|---|---|---|---|
| Random (case1) | 1.368 | 0.628 | 0.624 | 0.623 | 0.610 |
| Increasing (case2) | 0.331 | 0.581 | 0.595 | 0.590 | 0.578 |
| Decreasing (case3) | 1.404 | 0.592 | 0.607 | 0.607 | 0.580 |

### Findings

- **Insertion sort** grows far faster than the others on random and decreasing input, and far slower on increasing input. This matches its O(n²) average and worst cases and its O(n) best case. At one million numbers in decreasing order it takes 197 seconds, and quick sort takes 0.03 seconds.
- **Quick sort stays at O(n lg n) on sorted and reverse-sorted input.** The textbook worst case is O(n²), but the median-of-three pivot avoids bad splits on these inputs.
- **Quick sort is faster than randomized quick sort in every case.** Taking the median of three values costs less than calling the random number generator for each partition.
- **Top-down merge sort is faster than bottom-up merge sort** and uses less memory. The bottom-up version copies both runs into new vectors before each merge, and the top-down version passes index ranges and allocates only one buffer per merge.
- **Insertion sort and both quick sorts sort in place**, so their memory use is the lowest. The merge sorts need O(n) extra space.

## Build and run

```bash
make
./bin/NTU_sort -[IS|MS|BMS|QS|RQS] <input_file> <output_file>
```

Example:

```bash
./bin/NTU_sort -QS 1000.case1.in 1000.case1.out
```

The course's test inputs are not included in this repository. Any file in the format below can be used.

The program prints the CPU time and peak memory of the sorting step. Memory is read from `/proc`, so it is reported only on Linux.

### File format

Input and output files have two header lines followed by one `index number` pair per line:

```
# 5 data points
# index number
0 16
1 13
2 0
3 6
4 7
```

## Repository layout

| Path | Contents |
|---|---|
| `src/sort_tool.cpp`, `src/sort_tool.h` | The sorting algorithms |
| `src/main.cpp` | Argument parsing, file reading and writing, timing |
| `lib/` | Time and memory measurement library |
| `doc/report.pdf` | Report with the measurements, plots, and analysis |
| `PA1.pdf` | Assignment specification |

## Acknowledgements

The program skeleton (`main.cpp`, the `SortTool` class interface) and the `tm_usage` library were provided by the course staff. The sorting functions in `src/sort_tool.cpp` are my own implementation.

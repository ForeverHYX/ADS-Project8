import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# Read the CSV file
df = pd.read_csv("skiplist_performance.csv")

# Operations to analyze: Insert, Search, Delete
operations = ['Insert', 'Search', 'Delete']
colors = ['r', 'g', 'b']
plt.figure(figsize=(10, 6))

# Define the logarithmic fitting function
def logarithmic(x, a, b):
    return a * np.log(x) + b

# Fit and plot for each operation
for op, color in zip(operations, colors):
    op_data = df[df['Operation'] == op]
    
    # Group by size and calculate average time for fitting
    grouped = op_data.groupby('Size')['Time(ms)'].mean()
    
    # Extract sizes and times for fitting
    sizes_for_fit = grouped.index
    times_for_fit = grouped.values
    
    # Perform the curve fitting
    popt, _ = curve_fit(logarithmic, sizes_for_fit, times_for_fit)
    
    # Plot the raw data points (all points, not just the averages)
    plt.scatter(op_data['Size'], op_data['Time(ms)'], label=f'{op} Data', color=color, alpha=0.6, s=30)
    
    # Plot the fitted curve
    plt.plot(sizes_for_fit, logarithmic(sizes_for_fit, *popt), label=f'{op} Fit: a={popt[0]:.2e}, b={popt[1]:.2e}', color=color, linestyle='--')

# Add labels and title
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Size')
plt.ylabel('Time (ms)')
plt.title('SkipList Performance (Insert, Search, Delete) with Logarithmic Fit')
plt.legend()
plt.grid(True)

# Show the plot
plt.show()

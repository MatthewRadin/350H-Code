# File to generate my own input files for the bonus problem 3
# This script was given by CHATGPT

import os
import random

# Create input directory if it doesn't exist
os.makedirs("input", exist_ok=True)

# Sizes and number of trials
sizes = [10, 100, 1000, 10000, 100000]
trials = 100

for size in sizes:
    for trial in range(1, trials + 1):
        filename = f"Bonus Problems/bonus 3/input/input{size}_{trial}.txt"
        with open(filename, "w") as f:
            numbers = [random.randint(1, 1000000) for _ in range(size)]
            f.write(" ".join(map(str, numbers)))

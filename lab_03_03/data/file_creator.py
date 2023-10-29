import os
import random

sizes = [100, 200, 300, 400, 500]
percentages = [1, 10, 25, 50, 75, 100]

for size in sizes:
    for percent in percentages:
        num_elements = size * size
        num_nonzero = num_elements * percent // 100

        matrix_values = [random.randint(1, 100) for _ in range(num_nonzero)]
        vector_values = [random.randint(1, 100) for _ in range(size)]
        
        vector_nonzero = max(1, size * percent // 100)
        nonzero_indices = random.sample(range(size), vector_nonzero)
        for i in range(size):
            if i not in nonzero_indices:
                vector_values[i] = 0

        row_col_pairs = set()
        while len(row_col_pairs) < num_nonzero:
            row = random.randint(0, size - 1)
            col = random.randint(0, size - 1)
            row_col_pairs.add((row, col))

        row_cols = list(row_col_pairs)
        matrix_rows, matrix_cols = zip(*row_cols)

        filename = f"{percent}.txt"
        filepath = os.path.join(str(size), filename)
        os.makedirs(os.path.dirname(filepath), exist_ok=True)

        with open(filepath, 'w') as f:
            f.write(f"{size} {size}\n")
            f.write(f"{num_nonzero}\n")
            for row, col, value in zip(matrix_rows, matrix_cols, matrix_values):
                f.write(f"{row} {col}\n")
                f.write(f"{value}\n")
            f.write(f"{size}\n")
            f.write(f"{vector_nonzero}\n")
            for row, value in enumerate(vector_values):
                if value != 0:
                    f.write(f"{row}\n")
                    f.write(f"{value}\n")

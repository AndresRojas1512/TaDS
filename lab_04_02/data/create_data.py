def create_and_write_file(filename, count):
    with open(filename, 'w') as f:
        for number in range(1, count + 1):
            f.write(str(number) + '\n')

counts = [100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000]
for count in counts:
    filename = f'{count}.txt'
    create_and_write_file(filename, count)

print("Files created successfully.")
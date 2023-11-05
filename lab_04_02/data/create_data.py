def create_and_write_file(filename, count):
    with open(filename, 'w') as f:
        for number in range(1, count + 1):
            f.write(str(number) + '\n')

counts = [100, 500, 1000, 1500, 2000, 2500, 3000]
for count in counts:
    filename = f'{count}.txt'
    create_and_write_file(filename, count)

print("Files created successfully.")
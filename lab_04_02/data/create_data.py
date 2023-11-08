def create_and_write_file(filename, count):
    with open(filename, 'w') as f:
        for number in range(1, count + 1):
            f.write(str(number) + '\n')

counts = [1000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000]
for count in counts:
    filename = f'{count}.txt'
    create_and_write_file(filename, count)

print("Success.")

import os
import random
import string

def create_unique_strings(count, start_with_m_percentage):
    unique_strings = set()
    count_start_with_m = int(count * start_with_m_percentage / 100)
    all_chars = string.ascii_letters + string.digits
    non_m_chars = [c for c in all_chars if c.lower() != 'm']

    while len(unique_strings) < count:
        if len(unique_strings) < count_start_with_m:
            rand_str = 'm' + ''.join(random.choices(all_chars, k=9))
        else:
            rand_str = random.choice(non_m_chars) + ''.join(random.choices(all_chars, k=9))
        unique_strings.add(rand_str)
    return list(unique_strings)

def create_and_write_file(directory, filename, count, start_with_m_percentage):
    unique_strings = create_unique_strings(count, start_with_m_percentage)

    with open(os.path.join(directory, filename), 'w') as file:
        for s in unique_strings:
            file.write(s + '\n')

def create_directory_if_not_exists(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)

counts = [100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000]
percentages = [25, 50, 75, 100]

for count in counts:
    directory = str(count)
    create_directory_if_not_exists(directory)

    for percentage in percentages:
        filename = f'{percentage}.txt'
        create_and_write_file(directory, filename, count, percentage)
import os

def count_words_starting_with_m(filename):
    count = 0
    with open(filename, 'r') as file:
        for line in file:
            if line.lower().startswith('m'):
                count += 1
    return count

counts = [100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000]
percentages = [25, 50, 75, 100]

for count in counts:
    print(count)
    directory = str(count)
    for percentage in percentages:
        filename = os.path.join(directory, f'{percentage}.txt')
        m_count = count_words_starting_with_m(filename)
        print(f'    {percentage}.txt = {m_count} words')

def displayline(line):
    for word in line.split(","):
            print(word.strip())

if __name__ == '__main__':
    filename = "numbers.txt"

    try:
        with open(filename, 'r') as f:
            for line in f:
                displayline(line)
    except IOError as e:
        print("Error")


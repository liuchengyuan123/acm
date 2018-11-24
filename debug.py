import os

def ifsame():
    os.system('produce.exe')
    os.system('out1.exe')
    os.system('out2.exe')

    out1 = []
    out2 = []

    with open('out1.txt', 'rt') as f1:
        for line in f1:
            out1.append(line)

    with open('out2.txt', 'rt') as f2:
        for line in f2:
            out2.append(line)

    if out1 == out2:
        print('Accepted')
        return 1
    else:
        data = []
        with open('in.txt', 'rt') as f:
            for line in f:
                data.append(line)
        len = out1.__len__()
        for i in range(len):
            if out1[i] != out2[i]:
                print(data[i + 1])
        return 0
if __name__ == '__main__':
    for test in range(100):
        if (ifsame() == 0):
            break

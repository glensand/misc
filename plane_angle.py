import numpy as np
import math

arr = []

with open("data.txt", "r") as file:
    for line in file:
        line = line.strip()
        for number in line.split():
            arr.append(float(number))

def compute(p1, p2, p3):
    v1 = p2 - p1
    v2 = p3 - p2
    norm = np.cross(v1, v2)
    norm = norm / np.linalg.norm(norm);
    return norm

p1 = np.array([arr[0], arr[1], arr[2]])
p2 = np.array([arr[3], arr[4], arr[5]])
p3 = np.array([arr[6], arr[7], arr[8]])

p4 = np.array([arr[9], arr[10], arr[11]])
p5 = np.array([arr[12], arr[13], arr[14]])
p6 = np.array([arr[15], arr[16], arr[17]])

n1 = compute(p1, p2, p3)
n2 = compute(p4, p5, p6)

print(n1)
print(n2)

dot = np.dot(n1, n2)
print(dot)

print("angle : ", math.degrees(np.arccos(dot)))
              

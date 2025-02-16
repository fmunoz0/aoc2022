import re

def row_coverage(sensor, beacon, row):
    dist = abs(sensor[0] - beacon[0]) + abs(sensor[1] - beacon[1])
    row_dist = abs(sensor[1] - row)
    if row_dist > dist:
        return set()
    
    covered = set()
    hdist = (dist - row_dist)
    for x in range(-hdist, hdist+1):
        covered.add((sensor[0]+x, row))
    return covered

def read_input():
    sensors = []
    beacons = []
    with open("day15.txt") as f:
        for line in f:
            res = re.findall(r'-?\d+', line)
            assert len(res) == 4
            sensors.append((int(res[0]), int(res[1])))
            beacons.append((int(res[2]), int(res[3])))
    return sensors, beacons

def main():
    sensors, beacons = read_input()
    row = 2000000
    coverage = set()
    for s, b in zip(sensors, beacons):
        coverage.update(row_coverage(s, b, row))
    coverage.difference_update(sensors)
    coverage.difference_update(beacons)
    
    print(len(coverage))
    
main()
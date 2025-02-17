import re

def row_coverage(sensor, beacon, row):
    dist = abs(sensor[0] - beacon[0]) + abs(sensor[1] - beacon[1])
    row_dist = abs(sensor[1] - row)
    if row_dist > dist:
        return None
    hdist = (dist - row_dist)
    return (sensor[0]-hdist, sensor[0]+hdist)

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

# returns True if a contains b
def range_contains(a, b):
    return a[0] <= b[0] and a[1] >= b[1]

def covered_ranges(sensors, beacons, row):
    ranges = []
    for s, b in zip(sensors, beacons):
        r = row_coverage(s, b, row)
        if r and ranges_overlap(r, (0, 4_000_000)):
            add_range(ranges, r)
    return ranges

def add_range(ranges, new):
    overlaped = list(filter(lambda r: ranges_overlap(new, r), ranges))
    
    left = min(overlaped + [new], key=lambda r: r[0])
    right = max(overlaped + [new], key=lambda r: r[1])
    new = (left[0], right[1])
    
    ranges[:] = filter(lambda r: r not in overlaped, ranges)
    
    insert_ordered(ranges, new)
    
def ranges_overlap(a, b):
    return not (a[1] < b[0] or b[1] < a[0])
        
def insert_ordered(ranges, new):
    # find first range to the right of "new"
    res = len(ranges)
    for idx, r in enumerate(ranges):
        assert not ranges_overlap(new, r)
        
        if r[0] > new[1]: # r.left > new.right
            res = idx
            break
            
    ranges.insert(res, new)

def main():
    sensors, beacons = read_input()
    for row in range(4_000_001):
        ranges = covered_ranges(sensors, beacons, row)
        
        if any(range_contains(r, (0, 4_000_000)) for r in ranges):
            continue
        
        print(row)
        print(ranges)
        break
    
main()
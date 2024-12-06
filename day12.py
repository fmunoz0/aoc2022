from collections import deque

def read_file(name):
    f = open(name, "r")
    matrix = []
    startx=0
    starty=0
    endx=0
    endy=0
    for line in f:
        row=[]
        for ch in line.strip():
            if ch == "S":
                ch = "a"
                startx=len(row)
                starty=len(matrix)
            elif ch == "E":
                ch = "z"
                endx = len(row)
                endy = len(matrix)
            row.append(ord(ch)-ord("a"))
        if len(row) > 0:
            matrix.append(row)
    f.close()
    return (matrix,startx,starty,endx,endy)

def visit(matrix, elem, dx, dy, visited, d, backwards):
    x = elem[0]
    y = elem[1] 
    dist = elem[2]
    x2 = x+dx
    y2 = y+dy
    if x2 < 0 or x2 >= len(matrix[0]):
        return
    if y2 < 0 or y2 >= len(matrix):
        return
    if visited[y2][x2]:
        return
    val = matrix[y][x]
    val2 = matrix[y2][x2]
    
    add_elem = False
    if backwards:
        if val <= val2 or val-val2 == 1:
            add_elem = True
    else:
        if val >= val2 or val2 - val == 1:
            add_elem = True
            
    if add_elem:
        visited[y2][x2]=True
        d.append((x2,y2,dist+1))

def create_matrix(cols, rows, val):
    matrix = []
    while len(matrix) < rows:
        row = []
        while len(row) < cols:
            row.append(val)
        matrix.append(row)
    return matrix

def bfs(matrix, startx, starty, endx, endy):
    visited = create_matrix(len(matrix[0]), len(matrix), False)
    
    d = deque()
    visited[starty][startx] = True
    d.append((startx, starty, 0))

    while True:
        elem = d.popleft()
        if elem[0] == endx and elem[1] == endy:
            return elem[2]
        
        visit(matrix, elem, 1, 0, visited, d, False)
        visit(matrix, elem, 0, 1, visited, d, False)
        visit(matrix, elem, 0, -1, visited, d, False)
        visit(matrix, elem, -1, 0, visited, d, False)

def bfs2(matrix, endx, endy):
    visited = create_matrix(len(matrix[0]), len(matrix), False)
    
    d = deque()
    visited[endy][endx] = True
    d.append((endx,endy, 0))

    while True:
        elem = d.popleft()
        if matrix[elem[1]][elem[0]] == 0:
            return elem[2]
        
        visit(matrix, elem, 1, 0, visited, d, True)
        visit(matrix, elem, 0, 1, visited, d, True)
        visit(matrix, elem, 0, -1, visited, d, True)
        visit(matrix, elem, -1, 0, visited, d, True)
        
def main():
    matrix, startx, starty, endx, endy = read_file("day12.txt")
    #result = bfs(matrix, startx, starty, endx, endy)
    result = bfs2(matrix, endx, endy)
    print(result)
    
main()
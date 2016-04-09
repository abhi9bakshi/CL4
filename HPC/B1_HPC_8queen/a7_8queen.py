from xml.dom.minidom import parse
import xml.dom.minidom

board = []
size = 8

def danger(row, col):
    for (i, j) in board:
        if row == i: return True
        if col == j: return True
        if abs(row - i) == abs(col - j): return True

    return False
    
def placequeen(row):
    if row > size:
        print board
    else:
        #move right(column increment)
        for col in range(1, size + 1):
            #skip the row in which queen was placed initially
            if row == x and col == y:
                placequeen(row + 1)
            if not danger(row, col):
                board.append((row, col))
                #move down(row increment)
                placequeen(row + 1)
                board.remove((row,col))

#start here
if __name__ == "__main__":
    # Open XML document using minidom parser
    DOMTree = xml.dom.minidom.parse("input.xml")
    dt = DOMTree.documentElement

	# Get all the elements of name position in collection
    position = dt.getElementsByTagName("position")

	#fetch x and y coordinate of queen and store the elements in variables
    x = int(position[0].getElementsByTagName('x')[0].childNodes[0].data)
    y = int(position[0].getElementsByTagName('y')[0].childNodes[0].data) 

    #place first queen on board
    board.append((x, y))
    placequeen(1)

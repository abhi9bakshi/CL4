import socket, pickle

HOST = 'localhost'
PORT = 50007
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
arr = [7,1,9,12,6,88,11,65]
data_string = pickle.dumps(arr)
s.send(data_string)
s.close()
import socket

UDP_IP = "192.168.100.17"
UDP_PORT = 8888
MESSAGE = "0,0,0,0,1"


sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.sendto(bytes(MESSAGE.encode('utf-8')), (UDP_IP, UDP_PORT))
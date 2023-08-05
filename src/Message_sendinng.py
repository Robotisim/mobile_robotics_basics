import socket
import time

IP_ADDRESS = "192.168.96.98"  # Replace with the ESP32 IP address
UDP_PORT = 1234

def send_message(message):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.sendto(message.encode(), (IP_ADDRESS, UDP_PORT))
    sock.close()

def main():
    message = input("Enter the message to display on ESP32: ")
    send_message(message)
    print("Message sent")

if __name__ == "__main__":
    main()
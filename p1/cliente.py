import socket

ip = "127.0.0.1"
port = 2000
msg = "pene"

print("Target IP: {}\nTarget port: {}\nMessage: <{}>".format(ip, port, msg))

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("127.0.0.1", 2001))

sock.sendto(msg.encode(), (ip, port))

data, addr = sock.recvfrom(1024)


# while True:
#     data, addr = sock.recvfrom(1024)
#     if data:
#         print(data)
#         continue
#     else:
#         print("Hola")

sock.close()

import socket
import time


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("", 2000))

while True:
    try:
        data, addr = sock.recvfrom(1024)
        data = data.decode()
        msg_day = time.strftime("%A, %d %B %Y")
        msg_time = time.strftime("%H:%M:%S")
        print(data, addr[0])
        if data == "DAY":
            msg = msg_day
        elif data == "TIME":
            msg = msg_time
        elif data == "DAYTIME":
            msg = "{}; {}".format(msg_day, msg_time)
        # print("Received message: <{}>".format(data.decode()))
        else:
            continue
        print(sock.sendto(msg.encode(), (addr[0], 2001)))

    except KeyboardInterrupt:
        sock.close()
        exit()

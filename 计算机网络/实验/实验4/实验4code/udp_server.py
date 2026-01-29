import socket
import random
# 参数socket.AF_INET表示使用IPv4，参数socket.SOCK_DGRAM表示使用UDP
serverSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
serverSocket.bind(('', 10000))
while True:
    rand = random.randint(0, 10)
    message, address = serverSocket.recvfrom(1024)
    print("接收的消息{}\n".format(message))
    print("接收的地址{}\n".format(address))
    message = message.upper()
    #自定义0，1，2，3数据丢失
    if rand < 4:
        print("数据包丢失")
        continue
    serverSocket.sendto(message, address)
     # address = ('192.168.56.1', 8080)
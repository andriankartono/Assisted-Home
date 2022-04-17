import socket
import os
from _thread import *
import sys
import time
import asyncio
import websockets
import json

class Server():
    
    def __init__(self, host="localhost", port=10004):
        self.ServerSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.ServerSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        #self.ServerSocket.settimeout(5)
        self.host = host
        self.port = port
        self.port2 = 10003
        self.ThreadCount = 0
        self.data = {}
        self.changed = None
        self.website_conn = None
        
        try:
            self.ServerSocket.bind((self.host, self.port))
        except socket.error as e:
            print(str(e))

        print('Waitiing for a Connection..')
        self.ServerSocket.listen()
        
        start_new_thread(self.one_minute_check, ())
        start_new_thread(self.webserver, ())


    def webserver(self):
        while True:
            async def server(websocket, path):
                async for message in websocket:
                    while True:
                        if self.changed is not None:
                            data_website = self.data.copy()
                            data_website_json = json.dumps(data_website)
                            await websocket.send(data_website_json)
                            print('msg sent to website: ', self.data[self.changed][0])
                            print('---------------')
                            self.changed = None

    
            
            loop_ = asyncio.new_event_loop()
            asyncio.set_event_loop(loop_)
            start_server = websockets.serve(server, self.host, self.port2)
            loop_.run_until_complete(start_server)
            loop_.run_forever()


    def one_minute_check(self):
        while True:
            now = time.time()
            if self.changed is None:
                data_copied = self.data.copy()
                for key in data_copied:
                    old_data, time_stamp = self.data[key]
                    if now - time_stamp > 60 and old_data[-1] != '2':
                        new_data = old_data[:-1] + '2'
                        self.data[key] = (new_data, time_stamp)
                        self.changed = key
                        break # sonst wird changed überschrieben
        
    def send_to_webpage(self):
        while True:
            if self.changed is not None:
                # hier senden self.data[self.changed]
                print('---------------')
                print('hier wirds gesendet an die web page')
                print('zuletzt geaendert:')
                print('adress: ', self.changed)

                if self.website_conn is not None:
                    self.website_conn.sendall(str.encode(self.data[self.changed][0]))
                    print('msg sent to website: ', self.data[self.changed][0])
                print('---------------')
                self.changed = None

    def threaded_client(self, connection, address):
        connection.send(str.encode('Welcome to the server123'))
        while True:
            data = connection.recv(2048)
            if not data:
                break
            reply = 'Data received from ' + address[0]+' is: ' + data.decode('utf-8')
            print(data.decode('utf-8'))
            if len(data.decode('utf-8').split(' ')) > 4:# and self.website_conn is None:
                self.website_conn = connection
                print('connected to website')
                connection.sendall(str.encode(reply))
                continue
            time_stamp = time.time()
            self.changed  = address[0] + ' ' + str(address[1])
            # check if changed
            if self.changed in self.data:
                if self.data[self.changed] == data.decode('utf-8'):
                    self.changed = None
                    print('no changes')
            time_stamp = time.time()
            self.data[address[0] + ' ' + str(address[1])] = (data.decode('utf-8'), time_stamp)
            print(reply)
            connection.send(str.encode(reply))
        connection.close()
        print('connection closed')

    def run(self):
        while True:
            Client, address = self.ServerSocket.accept()
            print('Connected to: ' + address[0] + ':' + str(address[1]))
            start_new_thread(self.threaded_client, (Client, address))
            self.ThreadCount += 1
            print('Thread Number: ' + str(self.ThreadCount))
        self.ServerSocket.close()
        
def main():
    my_server = Server()
    try:
        my_server.run()    
    except KeyboardInterrupt:
        print('Interrupted')
        my_server.ServerSocket.close()
        print(my_server.data)
        sys.exit(0)
    
    
if __name__ == "__main__":
    main()

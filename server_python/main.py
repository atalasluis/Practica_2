
import socket
import threading

from config import HOST, PORT
from client_registry import ClientRegistry
from logic_controller import LogicController
from client_handler import ClientHandler


class TCPServer:

    def __init__(self):
        self.registry = ClientRegistry()
        self.logic = LogicController()

    def iniciar(self):
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.bind((HOST, PORT))
        server.listen(5)

        print(f"🚀 Servidor en {HOST}:{PORT}")

        while True:
            conn, addr = server.accept()

            handler = ClientHandler(conn, addr, self.registry, self.logic)
            hilo = threading.Thread(target=handler.manejar)
            hilo.start()


if __name__ == "__main__":
    servidor = TCPServer()
    servidor.iniciar()
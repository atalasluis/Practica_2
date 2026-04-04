#python test_client.py
import socket
import threading
import time

HOST = "127.0.0.1"
PORT = 12345


def cliente_actuador():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))

    print("[ACTUADOR] Conectado")
    s.sendall(b"ACTUADOR\n")

    while True:
        data = s.recv(1024)
        if not data:
            break
        print("[ACTUADOR] Recibido:", data.decode().strip())

    s.close()


def cliente_sensor():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))

    print("[SENSOR] Conectado")
    s.sendall(b"SENSOR\n")

    distancias = [10, 30, 60]

    for d in distancias:
        mensaje = f"DIST:{d}\n"
        print("[SENSOR] Enviando:", mensaje.strip())
        s.sendall(mensaje.encode())
        time.sleep(2)

    s.close()


if __name__ == "__main__":
    threading.Thread(target=cliente_actuador).start()
    time.sleep(1)
    threading.Thread(target=cliente_sensor).start()
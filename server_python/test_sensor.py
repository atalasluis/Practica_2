import socket
import time

HOST = "192.168.0.107"  # IP de tu laptop (NO 127.0.0.1)
PORT = 12345

def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))

    print("[TEST SENSOR] Conectado")
    s.sendall(b"SENSOR\n")

    try:
        while True:
            distancia = int(input("Distancia a enviar: "))
            mensaje = f"DIST:{distancia}\n"

            print(f"[TEST SENSOR] Enviando: {mensaje.strip()}")
            s.sendall(mensaje.encode())

    except KeyboardInterrupt:
        print("\n[TEST SENSOR] Cerrando conexión")
        s.close()

if __name__ == "__main__":
    main()

#python test_sensor.py
#
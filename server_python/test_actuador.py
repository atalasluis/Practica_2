import socket

HOST = "192.168.0.102"  # IP de tu laptop
PORT = 12345

def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))

    print("[TEST ACTUADOR] Conectado al servidor")

    # Identificarse como actuador
    s.sendall(b"ACTUADOR\n")

    try:
        while True:
            data = s.recv(1024)

            if not data:
                print("[TEST ACTUADOR] Conexión cerrada")
                break

            buffer = data.decode()

            for mensaje in buffer.split("\n"):
                mensaje = mensaje.strip()
                if mensaje:
                    procesar_comando(mensaje)

    except KeyboardInterrupt:
        print("\n[TEST ACTUADOR] Cerrando conexión")
        s.close()


def procesar_comando(cmd):
    if cmd == "RED":
        print("[ACTUADOR] 🔴 LED ROJO")
    elif cmd == "YELLOW":
        print("[ACTUADOR] 🟡 LED AMARILLO")
    elif cmd == "GREEN":
        print("[ACTUADOR] 🟢 LED VERDE")
    else:
        print(f"[ACTUADOR] ⚠️ Comando desconocido: {cmd}")


if __name__ == "__main__":
    main()


#python test_actuador.py
#
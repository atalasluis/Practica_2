class ClientHandler:

    def __init__(self, conn, addr, registry, logic):
        self.conn = conn
        self.addr = addr
        self.registry = registry
        self.logic = logic
        self.tipo = None

    def manejar(self):
        print(f"[+] Conectado: {self.addr}")

        try:
            while True:
                data = self.conn.recv(1024)

                if not data:
                    break

                buffer = data.decode()

                for mensaje in buffer.split("\n"):
                    mensaje = mensaje.strip()
                    if mensaje:
                        print(f"[{self.addr}] -> {mensaje}")
                        self.procesar_mensaje(mensaje)

        except Exception as e:
            print(f"[ERROR] {self.addr}: {e}")

        finally:
            print(f"[-] Desconectado: {self.addr}")
            self.conn.close()

    def procesar_mensaje(self, mensaje):

        if mensaje == "SENSOR":
            self.tipo = "sensor"
            self.registry.registrar_sensor(self.conn)

        elif mensaje == "ACTUADOR":
            self.tipo = "actuador"
            self.registry.registrar_actuador(self.conn)

        elif mensaje.startswith("DIST:"):
            distancia = int(mensaje.split(":")[1])

            comando = self.logic.procesar_distancia(distancia)
            print(f"[LOGICA] {distancia} → {comando}")

            self.registry.enviar_a_actuador(comando)
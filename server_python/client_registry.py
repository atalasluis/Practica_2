
class ClientRegistry:

    def __init__(self):
        self.sensor = None
        self.actuador = None

    def registrar_sensor(self, conn):
        self.sensor = conn
        print("[INFO] Sensor registrado")

    def registrar_actuador(self, conn):
        self.actuador = conn
        print("[INFO] Actuador registrado")

    def enviar_a_actuador(self, mensaje):
        if self.actuador:
            try:
                self.actuador.sendall((mensaje + "\n").encode())
            except:
                print("[ERROR] No se pudo enviar al actuador")
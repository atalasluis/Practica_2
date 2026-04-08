class LogicController:

    def procesar_distancia(self, distancia):
        if distancia < 10:
            return "DANGER"
        elif distancia < 20:
            return "RED"
        elif distancia < 50:
            return "YELLOW"
        elif distancia < 80:
            return "GREEN"
import tkinter as tk
from tkinter import ttk
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import time
import requests

class RiverMonitorGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("River Monitoring GUI")

        # Labels for existing data
        self.label_state = tk.Label(root, text="State:")
        self.label_state.grid(row=0, column=0, sticky="w")

        self.label_valveOpening = tk.Label(root, text="Valve Opening:")
        self.label_valveOpening.grid(row=1, column=0, sticky="w")

        self.state_var = tk.StringVar()
        self.label_state_value = tk.Label(root, textvariable=self.state_var)
        self.label_state_value.grid(row=0, column=1, sticky="w")

        self.valveOpeningVar = tk.StringVar()
        self.label_valveOpening_value = tk.Label(root, textvariable=self.valveOpeningVar)
        self.label_valveOpening_value.grid(row=1, column=1, sticky="w")


        # Graph setup
        self.figure = Figure(figsize=(12, 6), dpi=100)
        self.canvas = FigureCanvasTkAgg(self.figure, master=root)
        self.canvas.get_tk_widget().grid(row=4, column=0, columnspan=2)

        self.ax = self.figure.add_subplot(1, 1, 1)
        self.figure.subplots_adjust(bottom=0.2)

        self.update_values()

    def update_values(self):
        try:
            response = requests.get("http://localhost:{}/api/river".format(PORT))
            data = response.json()

            
            #self.state_var.set(data["state"])
            pippo = data["state"]
            if pippo == "NORMAL":
                self.valveOpeningVar.set("25%")
                self.state_var.set(pippo)
            elif pippo == "ALLARM-TOO-HIGH":
                self.valveOpeningVar.set("50%")
                self.state_var.set(pippo)
            elif pippo == "ALLARM-TOO-LOW":
                self.valveOpeningVar.set("0%")
                self.state_var.set(pippo)
            elif pippo == "ALLARM-TOO-HIGH-CRITIC":
                self.valveOpeningVar.set("100%")
                self.state_var.set(pippo)
            elif pippo == "PRE-ALLARM-TOO-HIGH":
                self.valveOpeningVar.set("25%")
                self.state_var.set(pippo)
            else: 
                self.valveOpeningVar.set(pippo + "%")
                self.state_var.set("MANUAL")
                
            # Update the graph
            self.update_graph(self.ax, self.canvas, data)

        except Exception as e:
            print("Error fetching data:", e)

        self.root.after(1000, self.update_values)

    def update_graph(self, ax, canvas, data):
        lines = ax.get_lines()
        if lines:
            x = lines[0].get_xdata().tolist()  # Ottiene le coordinate x esistenti
            y = lines[0].get_ydata().tolist()  # Ottiene le coordinate y esistenti
        else:
            x = []
            y = []

        # Aggiorna solo gli ultimi 10 punti
        if len(x) >= 50:
            x.pop(0)  # Rimuove il punto più vecchio
            y.pop(0)
        x.append(time.strftime('%H:%M:%S'))  # Aggiunge il nuovo timestamp
        y.append(data['waterLevel'])  # Aggiunge il nuovo livello dell'acqua

        ax.clear()
        ax.set_title('Dati dal Server')
        ax.set_xlabel('Orario')
        ax.set_ylabel('Livello acqua')
        ax.set_ylim(0, 20)  # Fissa la scala dell'asse y da 0 a 100
        for tick in ax.get_xticklabels():
            tick.set_rotation(45)
        ax.plot(x, y, marker='o')
        canvas.draw()


PORT = 8080  # Port where your HTTP server is running

root = tk.Tk()
app = RiverMonitorGUI(root)
root.mainloop()

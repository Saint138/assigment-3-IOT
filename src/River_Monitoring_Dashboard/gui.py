import tkinter as tk
from tkinter import ttk
from tkinter import messagebox
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import random
import time

# dal backend arrivano 4 valori:
# "state"(String)
# "waterLevel"(int)
# "dashboard"(boolean)
# "automatic"(boolean)

# Simula una richiesta HTTP per ottenere dati
def request_data(url):
    data = {
        'tempo': time.strftime('%H:%M:%S'),
        'altezza': random.uniform(0, 100),  # Altezza casuale tra 0 e 100
        'livello acqua': random.uniform(0, 100),  # Valore casuale di livello acqua tra 0 e 100
        'abilitato': random.choice([True, False])  # Valore casuale di abilitazione
    }
    return data

""" def request_data(url):
    try:
        response = requests.get(url)
        response.raise_for_status()
        return response.json()
    except requests.exceptions.RequestException as e:
        print(f"Errore nella richiesta: {str(e)}")
        return None """

def periodic_request(urlReceive, interval, figure, canvas, ax, app):
    data = request_data(urlReceive)
    if data:
        update_graph(ax, canvas, data)

    app.after(interval, periodic_request, urlReceive, interval, figure, canvas, ax, app)

def update_graph(ax, canvas, data):
    lines = ax.get_lines()
    if lines:
        x = lines[0].get_xdata().tolist()  # Ottiene le coordinate x esistenti
        y = lines[0].get_ydata().tolist()  # Ottiene le coordinate y esistenti
    else:
        x = []
        y = []

    # Aggiorna solo gli ultimi 10 punti
    if len(x) >= 10:
        x.pop(0)  # Rimuove il punto più vecchio
        y.pop(0)
    x.append(data['tempo'])  # Aggiunge il nuovo punto
    y.append(data['livello acqua'])

    ax.clear()
    ax.set_title('Dati dal Server')
    ax.set_xlabel('Orario')
    ax.set_ylabel('Livello acqua')
    for tick in ax.get_xticklabels():
        tick.set_rotation(45)
    ax.plot(x, y, marker='o')
    canvas.draw()


def main():
    app = tk.Tk()
    app.title("River Monitoring Dashboard")

    figure = Figure(figsize=(8, 4), dpi=100)
    canvas = FigureCanvasTkAgg(figure, master=app)
    canvas.get_tk_widget().pack()
    ax = figure.add_subplot(1, 1, 1)
    figure.subplots_adjust(bottom=0.2)

    urlReceive = "http://192.168.150.205:8080/api/data"
    interval = 1000  # Ogni secondo
    periodic_request(urlReceive, interval, figure, canvas, ax, app)

    app.mainloop()

if __name__ == "__main__":
    main()

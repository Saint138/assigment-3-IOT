import tkinter as tk
from tkinter import ttk
from tkinter import messagebox
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import requests
import random
import time

def request_data(url):
    # Simulazione di dati di test
    data = []
    for i in range(10):
        data.append({
            'tempo': f'Timestamp {i}',
            'altezza': random.uniform(0, 100),  # Altezza casuale tra 0 e 100
            'apertura': random.uniform(0, 100),  # Valore casuale di apertura tra 0 e 100
            'abilitato': random.choice([True, False])  # Valore casuale di abilitazione
        })
    return data

""" def request_data(url):
    try:
        response = requests.get(url)
        response.raise_for_status()
        return response.json()
    except requests.exceptions.RequestException as e:
        print(f"Errore nella richiesta: {str(e)}")
        return None """

def periodic_request(urlReceive, interval, figure, canvas, servomotorLabel, stateLabel, app, ax, slider):
    data = request_data(urlReceive)
    if data:
        update_graph(ax, canvas, data)
        update_label(servomotorLabel, 'Apertura', data)
        update_label(stateLabel, 'Stato', data)             #modificare con switch
        update_slider_state(slider, data)

    app.after(interval * 1000, periodic_request, urlReceive, interval, figure, canvas, servomotorLabel, stateLabel, app, ax, slider)


def update_graph(ax, canvas, data):
    x = [point['tempo'] for point in data if 'tempo' in point and 'altezza' in point]
    y = [point['altezza'] for point in data if 'tempo' in point and 'altezza' in point]

    ax.clear()
    ax.set_title('Dati dal Server')
    ax.set_xlabel('Orario')
    ax.set_ylabel('Altezza')
    for tick in ax.get_xticklabels():
        tick.set_rotation(45)
    ax.plot(x, y, marker='o')
    canvas.draw()

def update_label(label, field, data):
    val = next((point[field] for point in data if field in point), None)
    if val is not None:
        label.set(f"{field}: {val}")

def toggle_slider_state(slider, button):
    current_state = slider.cget('state')
    if current_state == 'normal':
        slider.configure(state='disabled')
        button.configure(text='Abilita Barra')
    else:
        slider.configure(state='normal')
        button.configure(text='Disabilita Barra')

def update_slider_state(slider, data):
    abilitato = next((point['abilitato'] for point in data if 'abilitato' in point), None)
    if abilitato is not None:
        if abilitato:
            slider.configure(state='normal')
        else:
            slider.configure(state='disabled')

def main():
    app = tk.Tk()
    app.title("River Monitoring Dashboard")

    figure = Figure(figsize=(8, 4), dpi=100)
    canvas = FigureCanvasTkAgg(figure, master=app)
    canvas.get_tk_widget().pack()
    ax = figure.add_subplot(1, 1, 1)
    figure.subplots_adjust(bottom=0.2)

    servomotorLabel = tk.StringVar()
    servomotorLabel.set("Apertura: N/A")
    labelServo = tk.Label(app, textvariable=servomotorLabel, font=("Helvetica", 12), fg="blue")
    labelServo.pack(pady=10)

    stateLabel = tk.StringVar()
    stateLabel.set("Stato: N/A")
    labelState = tk.Label(app, textvariable=stateLabel, font=("Helvetica", 12), fg="blue")
    labelState.pack(pady=10)

    urlReceive = "http://192.168.150.205:8080/api/data"
    interval = 2
    slider = tk.Scale(app, from_=0, to=100, orient=tk.HORIZONTAL, label="Apertura Valvola")
    slider.configure(length=300, sliderlength=30, sliderrelief=tk.RAISED)
    slider.pack(pady=10)
    toggle_button = tk.Button(app, text="Abilita Barra", command=lambda: toggle_slider_state(slider, toggle_button))
    toggle_button.config(width=15, height=2, relief=tk.RIDGE)
    toggle_button.pack(pady=10)

    periodic_request(urlReceive, interval, figure, canvas, servomotorLabel, stateLabel, app, ax, slider)

    app.mainloop()

if __name__ == "__main__":
    main()

import tkinter as tk
from tkinter import ttk
from tkinter import messagebox
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import random
import time
import requests

# Flag per abilitare la modalità di test
TEST_MODE = True

def request_data(url):
    if TEST_MODE:
        # Se siamo in modalità di test, generiamo dati casuali
        data = {
            'state': "TODO",  # TODO: In modalità test, lo stato è impostato come TODO
            'waterLevel': random.randint(0, 100),  # Livello dell'acqua casuale tra 0 e 100
            'dashboard': True,  # Dashboard in modalità test è sempre attiva
            'automatic': True  # Modalità automatica in modalità test è sempre attiva
        }
        return data
    else:
        # Altrimenti, effettuiamo una richiesta HTTP reale
        try:
            response = requests.get(url)
            response.raise_for_status()
            return response.json()
        except requests.exceptions.RequestException as e:
            print(f"Errore nella richiesta: {str(e)}")
            return None

def main():
    app = tk.Tk()
    app.title("River Monitoring Dashboard")

    figure = Figure(figsize=(8, 4), dpi=100)
    canvas = FigureCanvasTkAgg(figure, master=app)
    canvas.get_tk_widget().pack()
    ax = figure.add_subplot(1, 1, 1)
    figure.subplots_adjust(bottom=0.3)

    urlReceive = "http://192.168.150.205:8080/api/data"
    urlSend = "http://192.168.150.205:8080/api/river"  # Indirizzo per inviare dati al backend
    interval = 1000  # Ogni secondo

    stato_label = tk.Label(app, text="Stato: ")
    stato_label.pack()

    modalita_label = tk.Label(app, text="Modalità: ")
    modalita_label.pack()

    def periodic_request():
        data = request_data(urlReceive)
        if data:
            update_graph(ax, canvas, data)
            update_labels(data)

        app.after(interval, periodic_request)

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
        x.append(time.strftime('%H:%M:%S'))  # Aggiunge il nuovo timestamp
        y.append(data['waterLevel'])  # Aggiunge il nuovo livello dell'acqua

        ax.clear()
        ax.set_title('Dati dal Server')
        ax.set_xlabel('Orario')
        ax.set_ylabel('Livello acqua')
        ax.set_ylim(0, 100)  # Fissa la scala dell'asse y da 0 a 100
        for tick in ax.get_xticklabels():
            tick.set_rotation(45)
        ax.plot(x, y, marker='o')
        canvas.draw()

    def update_labels(data):
        stato_label.config(text="Stato: " + ("TODO" if TEST_MODE else data['state']))  # Imposta il testo della label stato
        modalita_label.config(text="Modalità: " + ("TODO" if TEST_MODE else ("Automatic" if data['automatic'] else "Manual")))  # Imposta il testo della label modalità

    def toggle_manual_function():
        if manual_function_button["text"] == "Funzione manuale non attiva":
            manual_function_button["text"] = "Funzione manuale attiva"
            manual_input_slider.config(state="normal")
        else:
            manual_function_button["text"] = "Funzione manuale non attiva"
            manual_input_slider.config(state="disabled")

    def on_manual_input_changed(event):
        if manual_function_button["text"] == "Funzione manuale attiva":
            value = round(manual_input_slider.get())
            send_data_to_backend(urlSend, value)
            print("Valore della barra:", value)  # Stampiamo il valore della barra sul terminale
    
    def send_data_to_backend(url, value):
        if not TEST_MODE:
            # Invia dati al backend solo se non siamo in modalità di test
            try:
                response = requests.post(url, json={'value': value})
                response.raise_for_status()
                print("Dati inviati con successo al backend")
            except requests.exceptions.RequestException as e:
                print(f"Errore nell'invio dei dati al backend: {str(e)}")

    # Bottone per attivare/disattivare la funzione manuale
    manual_function_button = tk.Button(app, text="Funzione manuale non attiva", command=toggle_manual_function)
    manual_function_button.pack()

    # Barra di input a scorrimento per la funzione manuale
    manual_input_slider = ttk.Scale(app, from_=0, to=100, orient=tk.HORIZONTAL, command=on_manual_input_changed, length=300)
    manual_input_slider.pack()

    manual_input_slider.config(state="disabled")  # Imposta la barra di input come disabilitata inizialmente

    app.after(interval, periodic_request)  # Avvio del polling dei dati dal backend

    app.mainloop()

if __name__ == "__main__":
    main()

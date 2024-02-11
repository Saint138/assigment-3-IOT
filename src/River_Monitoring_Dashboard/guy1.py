import tkinter as tk
import requests

class RiverMonitorGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("River Monitoring GUI")
        
        self.label_state = tk.Label(root, text="Arduino State:")
        self.label_state.grid(row=0, column=0, sticky="w")
        
        self.label_waterlevel = tk.Label(root, text="Water Level:")
        self.label_waterlevel.grid(row=1, column=0, sticky="w")
        
        self.label_dashboard = tk.Label(root, text="Dashboard Message:")
        self.label_dashboard.grid(row=2, column=0, sticky="w")
        
        self.label_automatic = tk.Label(root, text="Automatic:")
        self.label_automatic.grid(row=3, column=0, sticky="w")
        
        self.state_var = tk.StringVar()
        self.label_state_value = tk.Label(root, textvariable=self.state_var)
        self.label_state_value.grid(row=0, column=1, sticky="w")
        
        self.waterlevel_var = tk.StringVar()
        self.label_waterlevel_value = tk.Label(root, textvariable=self.waterlevel_var)
        self.label_waterlevel_value.grid(row=1, column=1, sticky="w")
        
        self.dashboard_var = tk.StringVar()
        self.label_dashboard_value = tk.Label(root, textvariable=self.dashboard_var)
        self.label_dashboard_value.grid(row=2, column=1, sticky="w")
        
        self.automatic_var = tk.StringVar()
        self.label_automatic_value = tk.Label(root, textvariable=self.automatic_var)
        self.label_automatic_value.grid(row=3, column=1, sticky="w")
        
        self.update_values()
    
    def update_values(self):
        try:
            response = requests.get("http://localhost:{}/api/river".format(PORT))
            data = response.json()
            self.state_var.set(data["state"])
            self.waterlevel_var.set(data["waterLevel"])
            self.dashboard_var.set(data["dashboard"])
            self.automatic_var.set(data["automatic"])
        except Exception as e:
            print("Error fetching data:", e)
        
        self.root.after(1000, self.update_values)

PORT = 8080  # Port where your HTTP server is running

root = tk.Tk()
app = RiverMonitorGUI(root)
root.mainloop()

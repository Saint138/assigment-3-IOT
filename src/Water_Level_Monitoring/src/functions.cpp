#include "functions.h"

// Inizializzazione della variabile statica
int functions::waterLevel = 0;

void functions::waterDetectionTask(void* parameter) {
    Sonar* sonar = (Sonar*) parameter;
    for (;;) {
        int currentWaterLevel = sonar->toInt();
        // Aggiorna la variabile waterLevel
        if (currentWaterLevel == -1) {
            // Gestisci l'errore come preferisci, ad esempio stampando un messaggio di errore
            Serial.println("Errore nella lettura del livello dell'acqua");
        } else {
            // Aggiorna la variabile waterLevel solo se non c'è stato un errore
            waterLevel = currentWaterLevel;
        }
    }
}


int functions::getWaterLevel() {
    return waterLevel;
}

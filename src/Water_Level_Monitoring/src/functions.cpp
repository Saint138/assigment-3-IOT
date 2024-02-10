#include "functions.h"

// Inizializzazione della variabile statica
int functions::waterLevel = 0;

void functions::waterDetectionTask(void* parameter) {
    TaskParams* params = (TaskParams*)parameter;
    int* frequencyPtr = params->frequencyPtr;
    Sonar* sonar = params->sonar;
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
        
        // Attendi per la frequenza specificata
        vTaskDelay(*frequencyPtr / portTICK_PERIOD_MS);
    }
}


int functions::getWaterLevel() {
    return waterLevel;
}

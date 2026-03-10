#ifndef ABITUDINERICORRENTE_H
#define ABITUDINERICORRENTE_H

#include "Attivita.h"

// definisco frequenza (specifica per questa classe)
class Frequenza {
public: //pubblico per l'accesso esterno
    static const int Giornaliera = 0;
    static const int Settimanale = 1;
    static const int Mensile = 2;
};

class AbitudineRicorrente : public Attivita {
public:
    // Costruttore
    AbitudineRicorrente(const QString& titolo, const QString& descrizione, const QDate& scadenza, int frequenza, int contatoreStreak = 0);

    // Distruttore
    ~AbitudineRicorrente() override = default;


    // --- Implementazione metodi polimorfi

    // Serializzazione: salva i dati specifici (frequenza e streak)
    QJsonObject toJson() const override;

    // Deserializzazione: carica i dati specifici
    void fromJsonObject(const QJsonObject& json) override;

    // calcola l'esperienza in base alla streak
    int calcolaXP() const override;


    // --- Metodi Specifici

    int frequenza() const { return m_frequenza; }
    int contatoreStreak() const { return m_contatoreStreak; }

    // Metodo per incrementare la streak (logica di business)
    void incrementaStreak() { m_contatoreStreak++; }

private:
    int m_frequenza;
    int m_contatoreStreak; //contatore completamenti consecutivi
};

#endif

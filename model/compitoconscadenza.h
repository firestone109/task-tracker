#ifndef COMPITOCONSCADENZA_H
#define COMPITOCONSCADENZA_H

#include "Attivita.h"
#include <QTime>

//definisco classe per priorità attività
class Priorita {
public:
    static const int Bassa = 0;
    static const int Media = 1;
    static const int Alta = 2;
};

class CompitoConScadenza : public Attivita {
public:
    //costruttore
    CompitoConScadenza(const QString& titolo, const QString& descrizione, const QDate& scadenza, const QTime& ora, int priorita);

    //distruttore (override non necessario)
    ~CompitoConScadenza() override = default;


    // --- Implementazione dei Metodi Polimorfi (override)

    // Serializzazione: salva i dati specifici (ora e priorità)
    QJsonObject toJson() const override;

    // Deserializzazione: carica i dati specifici
    void fromJsonObject(const QJsonObject& json) override;

    // Logica RPG: calcola l'esperienza in base alla priorità
    int calcolaXP() const override;


    // --- Metodi Specifici

    QTime oraScadenza() const { return m_oraScadenza; }
    int priorita() const { return m_priorita; } // restituisce int

private:
    QTime m_oraScadenza;
    int m_priorita;
};

#endif

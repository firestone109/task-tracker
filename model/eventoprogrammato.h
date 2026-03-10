#ifndef EVENTOPROGRAMMATO_H
#define EVENTOPROGRAMMATO_H

#include "Attivita.h"
#include <QString>

class EventoProgrammato : public Attivita {
public:
    //costruttore
    EventoProgrammato(const QString& titolo, const QString& descrizione, const QDate& scadenza, const QString& luogo, int durataOre);

    //distruttore
    ~EventoProgrammato() override = default;


    // --- Implementazione dei metodi polimorfi (override)

    // Serializzazione: salva i dati specifici (luogo e durata)
    QJsonObject toJson() const override;

    // Deserializzazione: carica i dati specifici
    void fromJsonObject(const QJsonObject& json) override;

    // calcola l'esperienza in base alla durata
    int calcolaXP() const override;

    // --- Metodi Specifici

    QString luogo() const { return m_luogo; }
    int durataOre() const { return m_durataOre; }

private:
    QString m_luogo;
    int m_durataOre; //durata in ore
};

#endif

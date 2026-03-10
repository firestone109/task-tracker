#include "CompitoConScadenza.h"
#include "Attivita.h"
#include <QJsonValue>

//costruttore
CompitoConScadenza::CompitoConScadenza(const QString& titolo, const QString& descrizione, const QDate& scadenza, const QTime& ora, int priorita)
    : Attivita(titolo, descrizione, scadenza), // chiama il costruttore della classe base e crea stto-obj
    m_oraScadenza(ora),
    m_priorita(priorita) // priorita int
{}

// --- Implementazione Polimorfa di toJson()

QJsonObject CompitoConScadenza::toJson() const {
    // Chiama il metodo base per ottenere gli attributi comuni
    QJsonObject json = toJsonBase();

    // Aggiunge gli attributi specifici
    json["tipo"] = "CompitoConScadenza";
    json["oraScadenza"] = m_oraScadenza.toString(Qt::ISODate);
    json["priorita"] = m_priorita;

    return json;
}


// --- Implementazione Polimorfa di fromJsonObject()
void CompitoConScadenza::fromJsonObject(const QJsonObject& json) {
    // 1. Chiama il metodo base per caricare gli attributi comuni
    fromJsonObjectBase(json);

    // 2. Carica gli attributi specifici
    m_oraScadenza = QTime::fromString(json["oraScadenza"].toString(), Qt::ISODate);
    // Carica l'int per la priorità
    m_priorita = json["priorita"].toInt();
}


// --- Implementazione Polimorfa di calcolaXP()
int CompitoConScadenza::calcolaXP() const {
    //XP calcolata in base alla priorità e allo stato
    int baseXP = 50;
    int moltiplicatore = 1;

    if (m_stato == StatoAttivita::Completed) {
        if (m_priorita == Priorita::Bassa) {
            moltiplicatore = 1;
        } else if (m_priorita == Priorita::Media) {
            moltiplicatore = 2;
        } else if (m_priorita == Priorita::Alta) {
            moltiplicatore = 4;
        }
        return baseXP * moltiplicatore;
    }

    //se non è completato, non dà XP
    return 0;
}

#include "EventoProgrammato.h"
#include "Attivita.h" // Per StatoAttivita
#include <QJsonValue>

// Costruttore
EventoProgrammato::EventoProgrammato(const QString& titolo, const QString& descrizione, const QDate& scadenza, const QString& luogo, int durataOre)
    : Attivita(titolo, descrizione, scadenza), // crea sotto-obj
    m_luogo(luogo),
    m_durataOre(durataOre)
{}

// ---Implementazione polimorfa di toJson()
QJsonObject EventoProgrammato::toJson() const {
    //chiama il metodo base per ottenere gli attributi comuni
    QJsonObject json = toJsonBase();

    //aggiunge gli attributi specifici
    json["tipo"] = "EventoProgrammato"; // Campo cruciale per la Factory Pattern
    json["luogo"] = m_luogo;
    json["durataOre"] = m_durataOre;

    return json;
}

// --- Implementazione polimorfa di fromJsonObject()
void EventoProgrammato::fromJsonObject(const QJsonObject& json) {
    // chiama il metodo base per caricare gli attributi comuni
    fromJsonObjectBase(json);

    //carica gli attributi specifici
    m_luogo = json["luogo"].toString();
    m_durataOre = json["durataOre"].toInt();
}

// --- Implementazione polimorfa di calcolaXP()
int EventoProgrammato::calcolaXP() const {
    //XP calcolata in base alla durata
    int baseXPPerOra = 20;

    if (m_stato == StatoAttivita::Completed) {
        return baseXPPerOra * m_durataOre;
    }

    //se non è completato, non dà XP
    return 0;
}

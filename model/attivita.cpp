#include "Attivita.h"
#include <QJsonValue>

//costruttore
Attivita::Attivita(const QString& titolo, const QString& descrizione, const QDate& scadenza)
    : m_titolo(titolo),    //lista iniz. membri
    m_descrizione(descrizione),
    m_dataScadenza(scadenza),

    // Inizializza m_stato con la costante int ToDo
    m_stato(StatoAttivita::ToDo)
{}

// Implementazione del metodo helper per la serializzazione di base
QJsonObject Attivita::toJsonBase() const {
    QJsonObject json;
    json["titolo"] = m_titolo;
    json["descrizione"] = m_descrizione;
    // Salva la data in formato ISO per una facile lettura
    json["dataScadenza"] = m_dataScadenza.toString(Qt::ISODate);
    // m_stato è già un int, quindi lo salviamo direttamente
    json["stato"] = m_stato;
    return json;
}

// Implementazione del metodo helper per la deserializzazione di base
void Attivita::fromJsonObjectBase(const QJsonObject& json) {
    m_titolo = json["titolo"].toString();
    m_descrizione = json["descrizione"].toString();
    // Carica la data dal formato ISO
    m_dataScadenza = QDate::fromString(json["dataScadenza"].toString(), Qt::ISODate);
    // Carica l'int per lo stato
    m_stato = json["stato"].toInt();
}

// I metodi toJson(), fromJsonObject() e calcolaXP() sono virtuali puri implementati nelle classi derivate.



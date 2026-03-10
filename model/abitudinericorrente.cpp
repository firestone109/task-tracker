#include "AbitudineRicorrente.h"
#include "Attivita.h"
#include <QJsonValue>

// Costruttore
AbitudineRicorrente::AbitudineRicorrente(const QString& titolo, const QString& descrizione, const QDate& scadenza, int frequenza, int contatoreStreak)
    : Attivita(titolo, descrizione, scadenza), // chiama il costruttore della classe base e crea sotto-obj
    m_frequenza(frequenza),
    m_contatoreStreak(contatoreStreak)
{}

// --- Implementazione polimorfa di toJson()
QJsonObject AbitudineRicorrente::toJson() const {
    // Chiama il metodo base per ottenere gli attributi comuni
    QJsonObject json = toJsonBase();

    // Aggiunge gli attributi specifici di AbitudineRicorrente
    json["tipo"] = "AbitudineRicorrente"; // Identificatore per la Factory Pattern
    json["frequenza"] = m_frequenza;
    json["contatoreStreak"] = m_contatoreStreak;

    return json;
}

// --- Implementazione polimorfa di fromJsonObject()
void AbitudineRicorrente::fromJsonObject(const QJsonObject& json) {
    // 1. Chiama il metodo base per caricare gli attributi comuni
    fromJsonObjectBase(json);

    // 2. Carica gli attributi specifici
    m_frequenza = json["frequenza"].toInt();
    m_contatoreStreak = json["contatoreStreak"].toInt();
}

// --- Implementazione Polimorfa di calcolaXP()

int AbitudineRicorrente::calcolaXP() const {
    //XP calcolata in base alla streak
    int baseXP = 10; // XP base per ogni completamento
    int bonusStreak = 0;

    if (m_stato == StatoAttivita::Completed) {
        // calcola un bonus progressivo per la streak
        // 10 XP per ogni punto di streak oltre il primo
        if (m_contatoreStreak > 1) {
            bonusStreak = (m_contatoreStreak - 1) * 10;
        }

        // XP totale è la base più il bonus.
        return baseXP + bonusStreak;
    }

    // se l'attività non è stata completata, non dà XP.
    return 0;
}

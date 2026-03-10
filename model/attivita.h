#ifndef ATTIVITA_H
#define ATTIVITA_H

#include <QString>
#include <QDate>
#include <QJsonObject>

class StatoAttivita {            //valori per indicare stato delle attività
public:
    static const int ToDo = 0;
    static const int InProgress = 1;
    static const int Completed = 2;
};

class Attivita {
public:
    virtual ~Attivita() = default;  //distruttore di def. per polimorfismo

    //metodi polimorfi PURI
    virtual QJsonObject toJson() const = 0;
    virtual void fromJsonObject(const QJsonObject& json) = 0;
    virtual int calcolaXP() const = 0;

    //costruttore e metodi
    Attivita(const QString& titolo, const QString& descrizione, const QDate& scadenza);

    //getter e Setter (Vincolo 5)
    QString titolo() const { return m_titolo; }
    QString descrizione() const { return m_descrizione; }
    QDate dataScadenza() const { return m_dataScadenza; }
    int stato() const { return m_stato; }

    void setStato(int stato) { m_stato = stato; }


protected:
    //attributi comuni a tutte le attività
    QString m_titolo;
    QString m_descrizione;
    QDate m_dataScadenza;
    int m_stato;

    //metod helper per la serializzazione degli attributi comuni
    QJsonObject toJsonBase() const;

    //metodo helper per la deserializzazione degli attributi comuni
    void fromJsonObjectBase(const QJsonObject& json);
};


#endif // ATTIVITA_H

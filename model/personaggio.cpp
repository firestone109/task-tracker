#include "Personaggio.h"

Personaggio::Personaggio(QObject *parent)
    : QObject(parent),
    m_livello(1),
    m_xpCorrente(0),
    m_xpTotale(0),
    m_xpPerProssimoLivello(100) // 100 XP per il livello 2
{
}

void Personaggio::controllaLivello() {
    while (m_xpCorrente >= m_xpPerProssimoLivello) {
        m_xpCorrente -= m_xpPerProssimoLivello;
        m_livello++;
        // ogni livello richiede *1.5 xp rispetto al precedente
        m_xpPerProssimoLivello = static_cast<int>(m_xpPerProssimoLivello * 1.5);
    }
}

void Personaggio::aggiungiEsperienza(int xp) {
    if (xp > 0) {
        m_xpCorrente += xp;
        m_xpTotale += xp;
        controllaLivello();
        emit statoCambiato(); // Notifica la GUI
    }
}

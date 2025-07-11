
#include "MatamStory.h"

#include "Utilities.h"

MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) : m_factory(Factory::factoryInstance()), m_numberOfFaintedPlayers(0) {

    /*===== TODO: Open and read events file =====*/
    m_events = m_factory.createEvents(eventsStream);
    m_numberOfEvents = m_events.size();
    /*==========================================*/

    /*===== TODO: Open and Read players file =====*/
    m_players = m_factory.createPlayers(playersStream);
    m_numberOfPlayers = m_players.size();
    for (auto& player : m_players) {
        m_sortedPlayers.push_back(player.get());
    }
    /*============================================*/

    this->m_turnIndex = 1;
}

void MatamStory::playTurn(Player& player) {
    unsigned int eventIndex = (m_turnIndex - 1) % m_numberOfEvents;
    std::unique_ptr<Event>& curEvent = m_events.at(eventIndex);

    printTurnDetails(m_turnIndex, player, *curEvent);

    const string& outcome = curEvent->applyEvent(player);

    printTurnOutcome(outcome);

    /**
     * Steps to implement (there may be more, depending on your design):
     * 1. Get the next event from the events list
     * 2. Print the turn details with "printTurnDetails"
     * 3. Play the event
     * 4. Print the turn outcome with "printTurnOutcome"
    */

    m_turnIndex++;
}

void MatamStory::playRound() {

    printRoundStart();

    /*===== TODO: Play a turn for each player =====*/
    for (auto& player : m_players) {
        if (!player->isPlayerFainted()) {
            playTurn(*player);
        }
    }
    /*=============================================*/

    printRoundEnd();

    printLeaderBoardMessage();

    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/
    std::sort(m_sortedPlayers.begin(), m_sortedPlayers.end(), [](auto const &player1, auto const &player2) {
        return *player1 > *player2;
    });
    int entryNumber = 1;
    for (const Player* player : m_sortedPlayers) {
        printLeaderBoardEntry(entryNumber, *player);
        entryNumber++;
    }

    /*=======================================================================================*/

    printBarrier();
}

bool MatamStory::isGameOver() {
    /*===== TODO: Implement the game over condition =====*/
    int faintCounter = 0;
    for (const auto& player : m_players) {
        if (player->getLevel() == Player::MAX_LEVEL) {
            return true;
        }
        if (player->isPlayerFainted()) {
            faintCounter++;
        }
    }
    m_numberOfFaintedPlayers = faintCounter;
    if (faintCounter == m_numberOfPlayers) {
        return true;
    }
    return false;
    /*===================================================*/
}

void MatamStory::play() {
    printStartMessage();
    /*===== TODO: Print start message entry for each player using "printStartPlayerEntry" =====*/
    int index = 1;
    for (const auto& player : m_players) {
        printStartPlayerEntry(index, *player);
        index++;
    }
    /*=========================================================================================*/
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    /*===== TODO: Print either a "winner" message or "no winner" message =====*/
    if (m_numberOfFaintedPlayers == m_numberOfPlayers) {
        printNoWinners();
    } else {
        printWinner(*m_sortedPlayers.front());
    }
    /*========================================================================*/
}

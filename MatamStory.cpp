
#include "MatamStory.h"
#include "Utilities.h"
#include "Events/StreamAdapter.h"

//get sorted indexes helper
std::vector<int> MatamStory::getSortedIndexes() const {
    int playerSize = this->players.size();
    std::vector<int> indexVector(playerSize);
    for (int i = 0; i < playerSize; i++) {
        indexVector[i] = i;
    }
    // sort indexes by player > operator
    std::sort(indexVector.begin(), indexVector.end(), [&](int a, int b) {
        return *players[a] > *players[b];
    });
    return indexVector;
}


MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {
    try {
        const StreamAdapter streamAdapter;
        this->events = streamAdapter.getEventsViaStream(eventsStream);
        this->players = streamAdapter.getPlayersViaStream(playersStream);
    } catch (std::exception& e) {
        throw;
    }
    this->currEventIndex = 0;
    this->m_turnIndex = 1;
}

//get next event implementation
Event& MatamStory::getNextEvent(){
    int eventsNum = this->events.size();
    if (this->currEventIndex == eventsNum) {
        //reset index
        this->currEventIndex = 0;
    }
    Event& event = *this->events[currEventIndex];
    // increment currEventIndex
    ++this->currEventIndex;
    return event;
}


void MatamStory::playTurn(Player& player) {

    //get next event
    Event& currEvent = this->getNextEvent();
    //print turn details
    printTurnDetails(m_turnIndex, player,currEvent);
    //play event
    string outcomeMessage = currEvent.apply(player);
    //print results
    printTurnOutcome(outcomeMessage);

    m_turnIndex++;
}

void MatamStory::playRound() {

    printRoundStart();

    for (const std::unique_ptr<Player> &playerPtr : this->players) {
        // use reference
        Player& player = *playerPtr;
        if (player.getHealthPoints() > 0) {
            this->playTurn(player);
        }
    }

    printRoundEnd();

    printLeaderBoardMessage();

    std::vector<int> indexVector = this->getSortedIndexes();

    int playerIdx = 1;
    for (int idxIter: indexVector ) {
        printLeaderBoardEntry(playerIdx, *this->players[idxIter]);
        playerIdx++;
    }

    printBarrier();
}

bool MatamStory::isGameOver() const {

    // Check if any player has reached level 10
    for (const std::unique_ptr<Player> &player : players) {
        if (player->getLevel() == 10) {
            return true;
        }
    }

    // Check if all players have fainted
    for (const std::unique_ptr<Player> &player : players) {
        if (player->getHealthPoints() > 0) {
            // Game continues if at least one player is still alive
            return false;
        }
    }
    // all players fainted
    return true;
}

void MatamStory::play() {
    printStartMessage();
    int playerNum = 1;
    for (const std::unique_ptr<Player> &playerPtr : players) {
        // use reference
        Player& player = *playerPtr;
        printStartPlayerEntry(playerNum, player);
        playerNum++;
    }
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();

    for (const std::unique_ptr<Player>& playerPtr : players) {
        // use reference
        Player& player = *playerPtr;
        if (player.getLevel() == 10) {
            // the winner is the player atop the leaderboard
            std::vector<int> indexVector = this->getSortedIndexes();
            printWinner(*this->players[indexVector[0]]);
            return;
        }
    }

    printNoWinners();
}
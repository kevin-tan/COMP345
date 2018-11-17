#pragma once
#include "Game.h" //I HAVE CHANGED THIS/////////////////////////////////////////////////////////////////////////////////////////////

class GameStatsViewer : public IObserver {
public:
	GameStatsViewer(ISubject* subject);
	virtual~GameStatsViewer();

	void update() override;
	void get_game_stats() const;

};


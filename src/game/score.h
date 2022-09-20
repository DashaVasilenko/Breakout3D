#ifndef SCORE_H
#define SCORE_H

#include <string>

#include "../core/types.h"
#include "../renderer/font.h"
#include "lives.h"

class Level;

class Score {
public:
    inline static Score* GetInstance() { if (!instance) instance = new Score(); return instance; }

	inline void SetTowerSize(i32 cnt) { towerSize = cnt; }
	inline void SetScore(i32 cnt) { score = cnt; }
	inline void AddScore(i32 cnt) { score += cnt; }
	inline void DestroyBrick() { towerSize--; }
	inline i32 GetTowerSize() { return towerSize; }

	void Init(Level* level);
	void Draw();

    ~Score();

private:
	Bubble::Font fontBig;
	Bubble::Font fontSmall;
    static Score* instance;
	Level* level = nullptr;
	i32 score = 0;
	i32 towerSize = 0;
    Score() {}
};

#endif

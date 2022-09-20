#ifndef LIVES_H
#define LIVES_H

#include <string>

#include "../core/types.h"
#include "../renderer/font.h"

class Level;

class Lives {
public:
    inline static Lives* GetInstance() { if (!instance) instance = new Lives(); return instance; }

	inline i32 GetLives() const { return lives; }
	inline void SetLives(i32 cnt) { lives = cnt; }
    inline void SubtractLife() { lives--; }
	inline void AddLives(i32 cnt) { lives += cnt; }
	inline i32 GetLives() { return lives; }

	void Init(Level* level);
	void Draw();

    ~Lives();

private:
	Bubble::Font fontBig;
	Bubble::Font fontSmall;
    static Lives* instance;
	Level* level = nullptr;
	i32 lives = 3;
    Lives() {}
};

#endif
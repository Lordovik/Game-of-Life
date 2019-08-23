#ifndef CELL_H
#define CELL_H

#pragma once

enum class direction
{
	to_die, to_rise, nan
};

class Cell
{
public:
	Cell(const int x = -1, const int y = -1, const bool dead = true);//true if dead
	~Cell();

	bool is_dead() const;
	bool is_alive() const;
	void die();
	void rise();
	int x() const;
	int y() const;
	direction dir;
	void release();

private:
	int x_;
	int y_;
	bool dead_;
};

#endif
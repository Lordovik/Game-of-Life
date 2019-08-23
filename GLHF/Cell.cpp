#include "stdafx.h"
#include "Cell.h"


Cell::Cell(const int x, const int y, const bool dead)
{
	x_ = x;
	y_ = y;
	dead_ = dead;
	dir = direction::nan;
}


Cell::~Cell()
{
}

bool Cell::is_dead() const
{
	return dead_;
}

bool Cell::is_alive() const
{
	return !dead_;
}

void Cell::die()
{
	dir = direction::to_die;
}

void Cell::rise()
{
	dir = direction::to_rise;
}

int Cell::x() const
{
	return x_;
}

int Cell::y() const
{
	return y_;
}

void Cell::release()
{
	if (dir == direction::to_rise)
		dead_ = false;
	else if (dir == direction::to_die)
		dead_ = true;
	dir = direction::nan;
}

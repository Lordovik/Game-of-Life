#ifndef FIELD_H
#define FIELD_H

#pragma once
#include "Cell.h"

class Field
{
public:
	Field(const int width = 3, const int height = 2);
	Field(Field &d);
	~Field();

	Cell const * operator[](const unsigned int i) const;

	int width() const;
	int height() const;
	void place_cell(Cell &cell);
	void kill(const int x, const int y);
	void revive(const int x, const int y);
	bool is_alive(const int x, const int y) const;
	bool is_dead(const int x, const int y) const;
	void transform_cell(const int x, const int y);
	void release_cells();
	void release_cell(const int x, const int y);

private:
	int width_;
	int height_;
	Cell ** cells;
};

#endif
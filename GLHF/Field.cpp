#include "stdafx.h"
#include "Field.h"


Field::Field(const int width, const int height)
{
	width_ = width;
	height_ = height;

	cells = new Cell*[height];
	for(auto i = 0; i < height; i++)
	{
		cells[i] = new Cell[width];
		for (auto j = 0; j < width; j++)
			cells[i][j] = Cell(j, i);
	}
}

Field::Field(Field& d)
{
	width_ = d.width_;
	height_ = d.height_;
	cells = new Cell*[height_];
	for (auto i = 0; i < height_; i++)
	{
		cells[i] = new Cell[width_];
		for (auto j = 0; j < width_; j++)
			cells[i][j] = d[i][j];
	}
}


Field::~Field()
{
	for (int i = 0; i < height_; i++)
		delete[] cells[i];
	delete[] cells;
}

Cell const * Field::operator[](const unsigned i) const
{
	return cells[i];
}

int Field::width() const
{
	return width_;
}

int Field::height() const
{
	return height_;
}

void Field::place_cell(Cell& cell)
{
	const auto x = cell.x();
	const auto y = cell.y();
	cells[y][x] = cell;
}

void Field::kill(const int x, const int y)
{
	cells[y][x].die();
}

void Field::revive(const int x, const int y)
{
	cells[y][x].rise();
}

bool Field::is_alive(const int x, const int y) const
{
	return cells[y][x].is_alive();
}

bool Field::is_dead(const int x, const int y) const
{
	return cells[y][x].is_dead();
}

void Field::transform_cell(const int x, const int y)
{
	Cell * curr = &cells[y][x];
	auto counter = 0;
	for (auto hor = x - 1; hor <= x + 1; hor++)
	{
		for (auto ver = y - 1; ver <= y + 1; ver++)
		{
			if (hor >= 0 && ver >= 0 && hor < width_ && ver < height_)
			{
				if (x != hor || y != ver)
				{
					if (this->is_alive(hor, ver))
					{
						counter++;
						if (counter > 3)
							break;
					}
				}
			}
		}
	}
	if(curr->is_alive() && (counter > 3 || counter < 2))
	{
		this->kill(x, y);
	}
	else if(curr->is_dead() && counter == 3)
	{
		this->revive(x, y);
	}
}

void Field::release_cells()
{
	for(auto i = 0; i < height_;i++)
	{
		for(auto j = 0; j < width_; j++)
		{
			cells[i][j].release();
		}
	}
}

void Field::release_cell(const int x, const int y)
{
	cells[y][x].release();
}


#pragma once
#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "djalib_text.h"

namespace djalib
{
	class Point
	{
		// instance variables:
		int _x;                         // the x-coordinate of the point.
		int _y;                         // the y-coordinate of the point.

	public:
		Point() :
			_x(0), _y(0) {
			// pass.
		}
		Point(int x, int y) :
			_x(x), _y(y) {
			// pass.
		}
		Point(const Point& point) :
			_x((int)point.getX()), _y((int)point.getY()) {
			// pass.
		}

	public:
		int getX() const {
			return _x;
		}
		int getY() const {
			return _y;
		}

		std::string toString() const {
			return
				"(" +
				djalib::integerToString(_x) +
				", " +
				djalib::integerToString(_y) +
				")";
		}

	public:
		bool operator ==(const Point& p2) const {
			return
				(_x == p2._x) &&
				(_y == p2._y);
		}
		bool operator !=(const Point& p2) const {
			return
				(_x != p2._x) ||
				(_y != p2._y);
		}

	public:
		friend std::ostream& operator <<(std::ostream& os, const djalib::Point& pt);

	};

}

#endif

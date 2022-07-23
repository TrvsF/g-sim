#pragma once
#ifndef SIZE_H_
#define SIZE_H_

struct Size
{
	float width;
	float height;
	float depth;

	Size(float _width = 0, float _height = 0, float _depth = 0)
		:	width(_width), height(_height), depth(_depth) {}

};

inline Size operator + (const Size& lhs, const Size& rhs)
{
	return Size(lhs.width + rhs.width, lhs.height + rhs.height, lhs.depth + rhs.depth);
}

inline Size operator - (const Size& lhs, const Size& rhs)
{
	return Size(lhs.width - rhs.width, lhs.height - rhs.height, lhs.depth - rhs.depth);
}

inline Size operator * (const Size& lhs, float factor)
{
	return Size(lhs.width * factor, lhs.height * factor, lhs.depth * factor);
}

inline Size operator / (const Size& lhs, float factor)
{
	return Size(lhs.width / factor, lhs.height / factor, lhs.depth / factor);
}

const Size SIZE_ZERO = { 0, 0, 0 };

#endif // !SIZE_H_
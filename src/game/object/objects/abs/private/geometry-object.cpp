#include "../geometry-object.h"

namespace object
{
	GeometryObject::GeometryObject(GameObject* object, int sides)
		: GameObject(object)
	{
		// dont be silly
		if (sides < 3)
		{
			sides = 3;
		}

		// generate random points
		std::vector<Vector2D> points;
		float width = GetSize().width;
		float height = GetSize().height;
		for (int i = 0; i < sides; i++)
		{
			points.push_back( { maths::GetRandomFloat(0, width), maths::GetRandomFloat(0, height) } );
		}
		create_tris(points);
	}

	GeometryObject::GeometryObject(GameObject* object, std::vector<Vector2D> points)
		: GameObject(object)
	{
		create_tris(points);
	}

	void GeometryObject::create_tris(std::vector<Vector2D> points)
	{
		float xtot = 0;
		float ytot = 0;
		int size = 0;
		for (Vector2D point : points)
		{
			xtot += point.x;
			ytot += point.y;
			size++;
		}
		Vector2D midpoint = { xtot / size, ytot / size };

		std::vector<Triangle*> tris;
		Vector2D last = points.back();
		for (Vector2D point : points)
		{
			Triangle t = Triangle::Create(point, last, midpoint);
			tris.push_back(new Triangle(t));
			last = point;
		}
		
		// TODO : offset based on pos (maybe pass verts?)
		renderer::Renderer::Get()->LoadTris(tris);
	}
}
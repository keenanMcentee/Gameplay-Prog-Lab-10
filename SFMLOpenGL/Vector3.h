#include <string>
#include <math.h>
using namespace std;
namespace customVector
{
	//Keenan McEntee
	class Vector3
	{
	private:
		
		const float PI = 3.14159;
	public:
		float x;
		float y;
		float z;

		float getZ();
		void setZ(float num);

		float getY();
		void setY(float num);

		float getX();
		void setX(float num);

		Vector3(); /// default constructor, makes null vector
		Vector3(float x1, float y1, float z1); //Constructor  taking values for x, y and z
		Vector3(string textX, string textY, string textZ); //Constructor taking in 3 strings and converting them to floats.
		Vector3 &operator=(const Vector3 &rhs);
		Vector3 Equals(Vector3 v2);
		const bool Vector3::operator==(const Vector3& v) const;
	    const bool Vector3::operator!=(const Vector3& v) const;
		Vector3 &operator +(const Vector3& v);
		const Vector3 operator-(const Vector3& v) const;
		const Vector3 operator*(const Vector3& v) const;
		const Vector3 operator*(double &number) const;
		const Vector3 operator*(float &number) const;
		double DotProduct(Vector3 v2);
		double Component(Vector3 v2);
		double AngleBetween(Vector3 v2);
		double Length();
		Vector3 CrossProduct(Vector3 v2);
		Vector3 Unit();
		Vector3 ParralelComponent(Vector3 v2);
		Vector3 PerpendicularComponent(Vector3 v2);
		Vector3 Scale(double scale);
		Vector3 Scale(float scale);
		Vector3 FlipX();
		Vector3 FlipY();
		std::string ToString();
	};
};
#include "Vector3.h"
namespace customVector
{
	float Vector3::getZ()
	{
		return z;
	}
	void Vector3::setZ(float num)
	{
		z = num;
	}

	float Vector3::getY() {
		return y;
	}
	void Vector3::setY(float num) {
		y = num;
	}

	float Vector3::getX() {
		return x;
	}
	void Vector3::setX(float num) {
		x = num;
	}

	Vector3::Vector3() {
		x = 0;
		y = 0;
		z = 0;
	} /// default constructor, makes null vector
	Vector3::Vector3(float x1, float y1, float z1) {
		x = x1;
		y = y1;
		z = z1;
	} //Constructor  taking values for x, y and z
	Vector3::Vector3(string textX, string textY, string textZ) {
		x = std::stof(textX);
		y = std::stof(textY);
		z = std::stof(textZ);
	} //Constructor taking in 3 strings and converting them to floats.
	Vector3 & Vector3::operator=(const Vector3 &rhs)
	{
		return Vector3(rhs.x, rhs.y, rhs.z);
	}
	Vector3 Vector3::Equals(Vector3 v2) {
		return Vector3(x = v2.x , y = v2.y , z = v2.z);
	}
	const bool Vector3::operator==(const Vector3& v) const {
		return (x == v.x && y == v.y && z == v.z);
	}
	const bool Vector3::operator!=(const Vector3& v) const {
		return !(Vector3(x, y, z) == v);
	}
    Vector3 & Vector3::operator +(const Vector3& v) {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	const Vector3 Vector3::operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	const Vector3 Vector3::operator*(const Vector3& v) const {
		return Vector3(x * v.x, y* v.y, z * v.z);
	}
	const Vector3 Vector3::operator*(double &number) const {
		return Vector3(x * (float)number, y * (float)number, z * (float)number);
	}
	const Vector3 Vector3::operator*(float &number) const {
		return Vector3(x * number, y * number, z * number);
	}
	double Vector3::DotProduct(Vector3 v2) {
		double dotProd = ((x * v2.x) + (y * v2.y) + (z * v2.z));
		return dotProd;
	}
	double Vector3::Component(Vector3 v2) {
		double dotProd = DotProduct(v2);
		double lenghtB = v2.Length();

		double component = (dotProd / (lenghtB * lenghtB));

		return component;
	}
	double Vector3::AngleBetween(Vector3 v2) {
		double lengthA = Length();
		double lengthB = v2.Length();
		double dotProd = DotProduct(v2);

		double angle = std::acos(dotProd / (lengthA * lengthB));
		double angleInDeg = angle * 180 / PI;
		return angleInDeg;
	}
	double Vector3::Length() {
		return std::sqrt((x*x) + (y*y) + (z*z));
	}
	Vector3 Vector3::CrossProduct(Vector3 v2) {
		return Vector3((y * v2.z) - (z * v2.y), (z * v2.x) - (x * v2.z), (x * v2.y) - (y * v2.x));

	}
	Vector3 Vector3::Unit() {
		double magnitude = (double)Length();
		return Vector3((float)(x / magnitude), (float)(y / magnitude), (float)(z / magnitude));

	}
	Vector3 Vector3::ParralelComponent(Vector3 v2) {
		double scalar = Component(v2);
		return Vector3((float)(x * scalar), (float)(y * scalar), (float)(z * scalar));
	}
	Vector3 Vector3::PerpendicularComponent(Vector3 v2) {
		double component = Component(v2);

		return Vector3((float)(v2.x - (component * x)), (float)(v2.y - (component * y)), (float)(v2.z - (component * z)));

	}
	Vector3 Vector3::Scale(double scale) {
		return Scale((float)scale);
	}
	Vector3 Vector3::Scale(float scale) {
		return Vector3((x * scale), (y * scale), (z * scale));
	}
	Vector3 Vector3::FlipX() {
		return Vector3(-x, y, z);
	}
	Vector3 Vector3::FlipY() {
		return Vector3(x, -y, z);
	}
	std::string Vector3::ToString()
	{
		
		return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
	}
}
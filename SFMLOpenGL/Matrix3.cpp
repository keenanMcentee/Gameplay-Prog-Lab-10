#include "Matrix3.h"

namespace customMatrix
{
	// Constructor 1 create a zero matrix
	Matrix::Matrix()
	{
		A11 = 0.0;
		A12 = 0.0;
		A13 = 0.0;
		A21 = 0.0;
		A22 = 0.0;
		A23 = 0.0;
		A31 = 0.0;
		A32 = 0.0;
		A33 = 0.0;
	}

	// Constructor 2
	Matrix::Matrix(customVector::Vector3 Row1, customVector::Vector3 Row2, customVector::Vector3 Row3)
	{  // To allow 3 rows of vectors to be declared as a matrix
		A11 = Row1.getX();
		A12 = Row1.getY();
		A13 = Row1.getZ();
		A21 = Row2.getX();
		A22 = Row2.getY();
		A23 = Row2.getZ();
		A31 = Row3.getX();
		A32 = Row3.getY();
		A33 = Row3.getZ();
	}
	// Constructor 3
	Matrix::Matrix(double _A11, double _A12, double _A13,
		double _A21, double _A22, double _A23,
		double _A31, double _A32, double _A33)
	{// to allow nine double values
		A11 = _A11;
		A12 = _A12;
		A13 = _A13;
		A21 = _A21;
		A22 = _A22;
		A23 = _A23;
		A31 = _A31;
		A32 = _A32;
		A33 = _A33;
	}
	Matrix Matrix::Equals(Matrix m)
	{
		return Matrix(A11 = m.A11,
			A12 = m.A12,
			A13 = m.A13,
			A21 = m.A21,
			A22 = m.A22,
			A23 = m.A23,
			A31 = m.A31,
			A32 = m.A32,
			A33 = m.A33);
	}
	Matrix Matrix::Equals(customVector::Vector3 Row1, customVector::Vector3 Row2, customVector::Vector3 Row3)
	{
		return Matrix(A11 = Row1.getX(),
		A12 = Row1.getY(),
		A13 = Row1.getZ(),
		A21 = Row2.getX(),
		A22 = Row2.getY(),
		A23 = Row2.getZ(),
		A31 = Row3.getX(),
		A32 = Row3.getY(),
		A33 = Row3.getZ());

	}
	Matrix Matrix::Equals(double _A11, double _A12, double _A13,
		double _A21, double _A22, double _A23,
		double _A31, double _A32, double _A33)
	{
		return Matrix(A11 = _A11,
			A12 = _A12,
			A13 = _A13,
			A21 = _A21,
			A22 = _A22,
			A23 = _A23,
			A31 = _A31,
			A32 = _A32,
			A33 = _A33);
	}

	const customVector::Vector3 Matrix::operator*(const customVector::Vector3& v) const
	{// An overloaded operator * to return the  product of the matrix by a vector
		return customVector::Vector3(A11 * v.x + A12 * v.y + A13 * v.z,
			A21 * v.x + A22 * v.y + A23 * v.z,
			A31 * v.x + A32 * v.y + A33 * v.z);
	}

	const Matrix Matrix::Transpose()const
	{// a method to transpose a given matrix
		return Matrix(A11, A21, A31,
			A12, A22, A32,
			A13, A23, A33);
	}
	const Matrix Matrix::operator +(const Matrix& m)const
	{// An overloaded operator + to return the  sum of two matrix 
		return Matrix(A11 + m.A11, A12 + m.A12, A13 + m.A13,
			A21 + m.A21, A22 + m.A22, A23 + m.A23,
			A31 + m.A31, A32 + m.A32, A33 + m.A33);
	}
	const Matrix Matrix::operator -(const Matrix& m) const
	{// An overloaded operator * to return the  difference of two matrix
		return Matrix(A11 - m.A11, A12 - m.A12, A13 - m.A13,
			A21 - m.A21, A22 - m.A22, A23 - m.A23,
			A31 - m.A31, A32 - m.A32, A33 - m.A33);
	}

	const Matrix Matrix::operator *(const double& x) const
	{// An overloaded operator * to return the  product of the matrix by a scalar
		Matrix answer = Matrix();
		answer.A11 = A11 * x;
		answer.A12 = A12 * x;
		answer.A13 = A13 * x;

		answer.A21 = A21 * x;
		answer.A22 = A22 * x;
		answer.A23 = A23 * x;

		answer.A31 = A31 * x;
		answer.A32 = A32 * x;
		answer.A33 = A33 * x; ;

		return answer;
	}
	Matrix Matrix::operator*(Matrix &m)
	{// An overloaded operator * to return the  product of two matrix
		Matrix answer = Matrix();
		answer.A11 = Row(0).DotProduct(m.Column(0));
		answer.A12 = Row(0).DotProduct(m.Column(1));
		answer.A13 = Row(0).DotProduct(m.Column(2));

		answer.A21 = Row(1).DotProduct(m.Column(0));
		answer.A22 = Row(1).DotProduct(m.Column(1));
		answer.A23 = Row(1).DotProduct(m.Column(2));

		answer.A31 = Row(2).DotProduct(m.Column(0));
		answer.A32 = Row(2).DotProduct(m.Column(1));
		answer.A33 = Row(2).DotProduct(m.Column(2));

		
		return answer;
	}


	const double Matrix::Determinant() const
	{// method to return the determinant of a 3x3 matrix
	 //                     aei      -     ahf                  + dhc                     - gec                      +    gbh                    -     dbi   
		return A11 * A22 * A33 - A11 * A32 * A23 + A21 * A32 * A13 - A31 * A22 * A13 + A31 * A12 * A23 - A21 * A12 * A33;
	}

	customVector::Vector3 Matrix::Row(int i)
	{
		// a method to return as Row as Vector3 0 == first row, default == last row
		switch (i)
		{
		case 0:
			return customVector::Vector3(A11, A12, A13);
		case 1:
			return customVector::Vector3(A21, A22, A23);
		case 2:
		default:
			return customVector::Vector3(A31, A32, A33);
		}
	}

	customVector::Vector3 Matrix::Column(int i)
	{// a method to return as column as Vector3 0 == first column, default == last column
		switch (i)
		{
		case 0:
			return customVector::Vector3(A11, A21, A31);
		case 1:
			return customVector::Vector3(A12, A22, A32);
		case 2:
		default:
			return customVector::Vector3(A13, A23, A33);
		}
	}


	Matrix Matrix::Inverse(Matrix M1)
	{
		// method to return the inverse of a matrix if exists else zero vector
		double det = M1.Determinant();
		if (det == 0)
			return Matrix();
		else
		{
			double scale = 1 / det;
			Matrix answer = Matrix();
			answer.A11 = scale * (A22 * A33 - A23 * A32); // ei-fh
			answer.A12 = scale * (A13 * A32 - A12 * A33); // ch-bi
			answer.A13 = scale * (A12 * A23 - A13 * A22); // ch-bi

			answer.A21 = scale * (A23 * A31 - A21 * A33); // fg-di
			answer.A22 = scale * (A11 * A33 - A13 * A31); // ai-cg
			answer.A23 = scale * (A13 * A21 - A11 * A23); // cd-af


			answer.A31 = scale * (A21 * A32 - A22 * A31); // dh-eg
			answer.A32 = scale * (A12 * A31 - A11 * A32); // bg-ah
			answer.A33 = scale * (A11 * A22 - A12 * A21); // ae-bd

			return answer;
		}

	}

	Matrix Matrix::Rotation(float _angle)
	{
		double radians = PI / 180 * _angle;
		Matrix answer = Matrix();
		answer.A11 = std::cos(radians);
		answer.A12 = std::sin(radians);
		answer.A13 = 0;
		answer.A21 = -std::sin(radians);
		answer.A22 = std::cos(radians);
		answer.A23 = 0;
		answer.A31 = 0;
		answer.A32 = 0;
		answer.A33 = 1;

		return answer;
	}


	Matrix Matrix::Translate(float dx, float dy)
	{
		Matrix answer = Matrix();
		answer.A11 = 1;
		answer.A12 = 0;
		answer.A13 = 0;
		answer.A21 = 0;
		answer.A22 = 1;
		answer.A23 = 0;
		answer.A31 = dx;
		answer.A32 = dy;
		answer.A33 = 1;

		return answer;
	}

	Matrix Matrix::Scale(float dx, float dy)
	{
		Matrix answer = Matrix();
		answer.A11 = (double)dx / 100;
		answer.A12 = 0;
		answer.A13 = 0;
		answer.A21 = 0;
		answer.A22 = (double)dy / 100;
		answer.A23 = 0;
		answer.A31 = 0;
		answer.A32 = 0;
		answer.A33 = 1;

		return answer;
	}

	Matrix Matrix::operator -(Matrix& M1)
	{
		return M1 * -1;
	}

	Matrix Matrix::RotationX(float _angle)
	{
		double radians = PI / 180 * _angle;
		Matrix answer = Matrix();
		answer.A11 = 1;
		answer.A12 = 0;
		answer.A13 = 0;
		answer.A21 = 0;
		answer.A22 = std::cos(radians);
		answer.A23 = -std::sin(radians);
		answer.A31 = 0;
		answer.A32 = std::sin(radians);
		answer.A33 = std::cos(radians);

		return answer;
	}
	Matrix Matrix::RotationY(float _angle)
	{
		double radians = PI / 180 * _angle;
		Matrix answer = Matrix();
		answer.A11 = std::cos(radians);
		answer.A12 = 0;
		answer.A13 = std::sin(radians);
		answer.A21 = 0;
		answer.A22 = 1;
		answer.A23 = 0;
		answer.A31 = std::sin(radians);
		answer.A32 = 0;
		answer.A33 = std::cos(radians);

		return answer;
	}
	Matrix Matrix::RotationZ(float _angle)
	{
		double radians = PI / 180 * _angle;
		Matrix answer = Matrix::Matrix();
		answer.A11 = std::cos(radians);
		answer.A12 = -std::sin(radians);
		answer.A13 = 0;
		answer.A21 = std::sin(radians);
		answer.A22 = std::cos(radians);
		answer.A23 = 0;
		answer.A31 = 0;
		answer.A32 = 0;
		answer.A33 = 1;

		return answer;
	}

	Matrix Matrix::Scale3D(int dx)
	{
		Matrix answer = Matrix();
		answer.A11 = (double)dx / 100;
		answer.A12 = 0;
		answer.A13 = 0;
		answer.A21 = 0;
		answer.A22 = (double)dx / 100;
		answer.A23 = 0;
		answer.A31 = 0;
		answer.A32 = 0;
		answer.A33 = (double)dx / 100;

		return answer;
	}
}


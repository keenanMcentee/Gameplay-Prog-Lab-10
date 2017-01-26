#include "Vector3.h"

namespace customMatrix
{
	class Matrix
	{
		private:
			const float PI = 3.14159;
	public:
		Matrix();
		Matrix(customVector::Vector3 Row1, customVector::Vector3 Row2, customVector::Vector3 Row3);
		Matrix(double _A11, double _A12, double _A13,
			double _A21, double _A22, double _A23,
			double _A31, double _A32, double _A33);
		Matrix Equals(Matrix m);
		Matrix Equals(customVector::Vector3 Row1, customVector::Vector3 Row2, customVector::Vector3 Row3);
		Matrix Equals(double _A11, double _A12, double _A13, double _A21, double _A22, double _A23, double _A31, double _A32, double _A33);

		const customVector::Vector3 operator*(const customVector::Vector3& v) const;
		const Matrix operator +(const Matrix& m)const;
		const Matrix operator -(const Matrix& m)const;

		Matrix operator -(Matrix& M1);
		const Matrix operator *(const double& x)const;
		const Matrix Transpose()const;
		Matrix operator*(Matrix& m);
		customVector::Vector3 Row(int i);
		customVector::Vector3 Column(int i);
		const double Determinant() const;
		Matrix Matrix::RotationX(float _angle);
		Matrix Matrix::RotationY(float _angle);
		Matrix Matrix::RotationZ(float _angle);
		Matrix Matrix::Scale3D(int dx);
		Matrix Matrix::Scale(float dx, float dy);
		Matrix Matrix::Translate(float dx, float dy);
		Matrix Matrix::Rotation(float _angle);
		double A11;
		double A12;
		double A13;
		double A21;
		double A22;
		double A23;
		double A31;
		double A32;
		double A33;
		customVector::Vector3 vect;
		Matrix Inverse(Matrix M1);
	};
};
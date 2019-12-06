/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 11/12/2019, 20:53
*@Last Modify: 11/17/2019, 23:35
*@Desc: 工具类头文件，存放一些通用数据结构或方法
*********************************************************/
#pragma once

namespace Bur {
#define max(a, b) ((a)>(b)?(a):(b))

	template<typename T>
	class vec2 {
	public:
		vec2(T a, T b) :x(a), y(b) {}
		~vec2() {}

		friend vec2 operator+ (const vec2& lhs, const vec2& rhs) {
			return vec2(lhs.x + rhs.x, lhs.y + rhs.y);
		}

		friend T operator* (const vec2& lhs, const vec2& rhs) {
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}

		friend T operator* (const T val, const vec2& v) {
			return val * v.x + val * v.y;
		}

		friend T operator* (const vec2& v, const T val) {
			return val * v.x + val * v.y;
		}

		friend std::ostream& operator<< (std::ostream &out, const vec2 &v)
		{
			out << "(" << v.x << "," << v.y << ")";
			return out;
		}

	public:
		T x;
		T y;
	};

	template<typename T>
	class vec3 {
	public:
		vec3(T a, T b, T c) :x(a), y(b), z(c) {}
		~vec3() {}

		friend vec3 operator+ (const vec3& lhs, const vec3& rhs) {
			return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
		}

		friend T operator* (const vec3& lhs, const vec3& rhs) {
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
		}

		friend T operator* (const T val, const vec3& v) {
			return val * v.x + val * v.y + val * v.z;
		}

		friend T operator* (const vec3& v, const T val) {
			return val * v.x + val * v.y + val * v.z;
		}

		friend std::ostream& operator<<(std::ostream &out, const vec3 &v)
		{
			out << "(" << v.x << "," << v.y << "," << v.z << ")";
			return out;
		}

	public:
		T x;
		T y;
		T z;
	};

	template<typename T>
	class quaternion {
	public:
		quaternion(T a, T b, T c, T d) :x(a), y(b), z(c), w(d) {}
		~quaternion() {}

		quaternion* operator +(quaternion& v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return this;
		}

	public:
		T x;
		T y;
		T z;
		T w;
	};

	template<typename T>


}
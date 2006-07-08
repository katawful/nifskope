/***** BEGIN LICENSE BLOCK *****

BSD License

Copyright (c) 2005, NIF File Format Library and Tools
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the NIF File Format Library and Tools projectmay not be
   used to endorse or promote products derived from this software
   without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

***** END LICENCE BLOCK *****/

#ifndef NIFTYPES_H
#define NIFTYPES_H

#include <QColor>
#include <QIODevice>
#include <QVariant>

#include "math.h"

#ifndef PI
#ifdef M_PI
#define PI M_PI
#else
#define PI 3.1416
#endif
#endif

class NifModel;
class QModelIndex;
class QDataStream;

class Vector2
{
public:
	Vector2()
	{
		xy[0] = xy[1] = 0.0;
	}
	Vector2( float x, float y )
	{
		xy[0] = x; xy[1] = y;
	}
	Vector2 & operator+=( const Vector2 & v )
	{
		xy[0] += v.xy[0];
		xy[1] += v.xy[1];
		return *this;
	}
	Vector2 operator+( const Vector2 & v ) const
	{
		Vector2 w( *this );
		return ( w += v );
	}
	Vector2 & operator-=( const Vector2 & v )
	{
		xy[0] -= v.xy[0];
		xy[1] -= v.xy[1];
		return *this;
	}
	Vector2 operator-( const Vector2 & v ) const
	{
		Vector2 w( *this );
		return ( w -= v );
	}
	Vector2 operator-() const
	{
		return Vector2() - *this;
	}
	Vector2 & operator*=( float s )
	{
		xy[0] *= s;
		xy[1] *= s;
		return *this;
	}
	Vector2 operator*( float s ) const
	{
		Vector2 w( *this );
		return ( w *= s );
	}
	Vector2 & operator/=( float s )
	{
		xy[0] /= s;
		xy[1] /= s;
		return *this;
	}
	Vector2 operator/( float s ) const
	{
		Vector2 w( *this );
		return ( w /= s );
	}
	
	bool operator==( const Vector2 & v ) const
	{
		return xy[0] == v.xy[0] && xy[1] == v.xy[1];
	}
	
	float & operator[]( unsigned int i )
	{
		Q_ASSERT( i < 2 );
		return xy[i];
	}
	const float & operator[]( unsigned int i ) const
	{
		Q_ASSERT( i < 2 );
		return xy[i];
	}
	
	const float * data() const
	{
		return xy;
	}
	
protected:
	float	xy[2];
	
	friend class NifIStream;
	friend class NifOStream;
};

class Vector3
{
public:
	Vector3()
	{
		xyz[ 0 ] = xyz[ 1 ] = xyz[ 2 ] = 0.0;
	}
	Vector3( float x, float y, float z )
	{
		xyz[0] = x;
		xyz[1] = y;
		xyz[2] = z;
	}
	explicit Vector3( const class Vector4 & );
	
	Vector3 & operator+=( const Vector3 & v )
	{
		xyz[0] += v.xyz[0];
		xyz[1] += v.xyz[1];
		xyz[2] += v.xyz[2];
		return *this;
	}
	Vector3 & operator-=( const Vector3 & v )
	{
		xyz[0] -= v.xyz[0];
		xyz[1] -= v.xyz[1];
		xyz[2] -= v.xyz[2];
		return *this;
	}
	Vector3 & operator*=( float s )
	{
		xyz[ 0 ] *= s;
		xyz[ 1 ] *= s;
		xyz[ 2 ] *= s;
		return *this;
	}
	Vector3 & operator/=( float s )
	{
		xyz[ 0 ] /= s;
		xyz[ 1 ] /= s;
		xyz[ 2 ] /= s;
		return *this;
	}
	Vector3 operator+( Vector3 v ) const
	{
		Vector3 w( *this );
		return w += v;
	}
	Vector3 operator-( Vector3 v ) const
	{
		Vector3 w( *this );
		return w -= v;
	}
	Vector3 operator-() const
	{
		return Vector3() - *this;
	}
	Vector3 operator*( float s ) const
	{
		Vector3 v( *this );
		return v *= s;
	}
	Vector3 operator/( float s ) const
	{
		Vector3 v( *this );
		return v /= s;
	}
	
	bool operator==( const Vector3 & v ) const
	{
		return xyz[0] == v.xyz[0] && xyz[1] == v.xyz[1] && xyz[2] == v.xyz[2];
	}
	
	float & operator[]( unsigned int i )
	{
		Q_ASSERT( i < 3 );
		return xyz[i];
	}
	const float & operator[]( unsigned int i ) const
	{
		Q_ASSERT( i < 3 );
		return xyz[i];
	}
	
	float length() const
	{
		return sqrt( xyz[0]*xyz[0] + xyz[1]*xyz[1] + xyz[2]*xyz[2] );
	}
	
	float squaredLength() const
	{
		return xyz[0]*xyz[0] + xyz[1]*xyz[1] + xyz[2]*xyz[2];
	}
	
	void normalize()
	{
		float m = length();
		if ( m > 0.0 )
			m = 1.0 / m;
		else
			m = 0.0F;
		xyz[0] *= m;
		xyz[1] *= m;
		xyz[2] *= m;
	}
	
	static float dotproduct( const Vector3 & v1, const Vector3 & v2 )
	{
		return v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2];
	}
	static Vector3 crossproduct( const Vector3 & a, const Vector3 & b )
	{
		return Vector3( a[1]*b[2] - a[2]*b[1], a[2]*b[0] - a[0]*b[2], a[0]*b[1] - a[1]*b[0] );
	}
	
	static float angle( const Vector3 & v1, const Vector3 & v2 )
	{
		float dot = dotproduct( v1, v2 );
		if ( dot > 1.0 )
			return 0.0;
		else if ( dot < - 1.0 )
			return (float)PI;
		else if ( dot == 0.0 )
			return (float)(PI/2);
		else
			return acos( dot );
	}
	
	void boundMin( const Vector3 & v )
	{
		if ( v[0] < xyz[0] ) xyz[0] = v[0];
		if ( v[1] < xyz[1] ) xyz[1] = v[1];
		if ( v[2] < xyz[2] ) xyz[2] = v[2];
	}
	void boundMax( const Vector3 & v )
	{
		if ( v[0] > xyz[0] ) xyz[0] = v[0];
		if ( v[1] > xyz[1] ) xyz[1] = v[1];
		if ( v[2] > xyz[2] ) xyz[2] = v[2];
	}
	
	const float * data() const { return xyz; }
	
	QString toHtml() const
	{
		return QString( "X %1 Y %2 Z %3<br>length %4" ).arg( xyz[0] ).arg( xyz[1] ).arg( xyz[2] ).arg( length() );
	}
	
protected:
	float xyz[3];
	
	friend class NifIStream;
	friend class NifOStream;
};

class Vector4
{
public:
	Vector4()
	{
		xyzw[ 0 ] = xyzw[ 1 ] = xyzw[ 2 ] = xyzw[ 3 ] = 0.0;
	}
	Vector4( float x, float y, float z, float w )
	{
		xyzw[ 0 ] = x;
		xyzw[ 1 ] = y;
		xyzw[ 2 ] = z;
		xyzw[ 3 ] = w;
	}
	Vector4 & operator+=( const Vector4 & v )
	{
		xyzw[0] += v.xyzw[0];
		xyzw[1] += v.xyzw[1];
		xyzw[2] += v.xyzw[2];
		xyzw[3] += v.xyzw[3];
		return *this;
	}
	Vector4 & operator-=( const Vector4 & v )
	{
		xyzw[0] -= v.xyzw[0];
		xyzw[1] -= v.xyzw[1];
		xyzw[2] -= v.xyzw[2];
		xyzw[3] -= v.xyzw[3];
		return *this;
	}
	Vector4 & operator*=( float s )
	{
		xyzw[ 0 ] *= s;
		xyzw[ 1 ] *= s;
		xyzw[ 2 ] *= s;
		xyzw[ 3 ] *= s;
		return *this;
	}
	Vector4 & operator/=( float s )
	{
		xyzw[ 0 ] /= s;
		xyzw[ 1 ] /= s;
		xyzw[ 2 ] /= s;
		xyzw[ 3 ] /= s;
		return *this;
	}
	Vector4 operator+( Vector4 v ) const
	{
		Vector4 w( *this );
		return w += v;
	}
	Vector4 operator-( Vector4 v ) const
	{
		Vector4 w( *this );
		return w -= v;
	}
	Vector4 operator-() const
	{
		return Vector4() - *this;
	}
	Vector4 operator*( float s ) const
	{
		Vector4 v( *this );
		return v *= s;
	}
	Vector4 operator/( float s ) const
	{
		Vector4 v( *this );
		return v /= s;
	}
	
	bool operator==( const Vector4 & v ) const
	{
		return xyzw[0] == v.xyzw[0] && xyzw[1] == v.xyzw[1] && xyzw[2] == v.xyzw[2] && xyzw[3] == v.xyzw[3];
	}
	
	float & operator[]( unsigned int i )
	{
		Q_ASSERT( i < 4 );
		return xyzw[i];
	}
	const float & operator[]( unsigned int i ) const
	{
		Q_ASSERT( i < 4 );
		return xyzw[i];
	}
	
	float length() const
	{
		return sqrt( xyzw[0]*xyzw[0] + xyzw[1]*xyzw[1] + xyzw[2]*xyzw[2] + xyzw[3]*xyzw[3] );
	}
	
	float squaredLength() const
	{
		return xyzw[0]*xyzw[0] + xyzw[1]*xyzw[1] + xyzw[2]*xyzw[2] + xyzw[3]*xyzw[3];
	}
	
	void normalize()
	{
		float m = length();
		if ( m > 0.0 )
			m = 1.0 / m;
		else
			m = 0.0F;
		xyzw[0] *= m;
		xyzw[1] *= m;
		xyzw[2] *= m;
		xyzw[3] *= m;
	}
	
	static float dotproduct( const Vector4 & v1, const Vector4 & v2 )
	{
		return v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2]+v1[3]*v2[3];
	}
	
	static float angle( const Vector4 & v1, const Vector4 & v2 )
	{
		float dot = dotproduct( v1, v2 );
		if ( dot > 1.0 )
			return 0.0;
		else if ( dot < - 1.0 )
			return (float)PI;
		else if ( dot == 0.0 )
			return (float)PI/2;
		else
			return (float)acos( dot );
	}
	
	const float * data() const { return xyzw; }
	
	QString toHtml() const
	{
		return QString( "X %1 Y %2 Z %3 W %4<br>length %5" ).arg( xyzw[0] ).arg( xyzw[1] ).arg( xyzw[2] ).arg( xyzw[3] ).arg( length() );
	}
	
protected:
	float xyzw[4];
	
	friend class NifIStream;
	friend class NifOStream;
};

inline Vector3::Vector3( const Vector4 & v4 )
{
	xyz[0] = v4[0];
	xyz[1] = v4[1];
	xyz[2] = v4[2];
}

class Quat
{
public:
	Quat()
	{
		memcpy( wxyz, identity, 16 );
	}
	float & operator[]( unsigned int i )
	{
		Q_ASSERT( i < 4 );
		return wxyz[ i ];
	}
	const float & operator[]( unsigned int i ) const
	{
		Q_ASSERT( i < 4 );
		return wxyz[ i ];
	}
	Quat & operator*=( float s )
	{
		for ( int c = 0; c < 4; c++ )
			wxyz[ c ] *= s;
		return *this;
	}
	Quat operator*( float s ) const
	{
		Quat q( *this );
		return ( q *= s );
	}
	Quat & operator+=( const Quat & q )
	{
		for ( int c = 0; c < 4; c++ )
			wxyz[ c ] += q.wxyz[ c ];
		return *this;
	}
	Quat operator+( const Quat & q ) const
	{
		Quat r( *this );
		return ( r += q );
	}
	static float dotproduct( const Quat & q1, const Quat & q2 )
	{
		return q1[0]*q2[0]+q1[1]*q2[1]+q1[2]*q2[2]+q1[3]*q2[3];
	}

	QString toHtml() const
	{
		return QString( "W %1<br>X %2<br>Y %3<br>Z %4" ).arg( wxyz[0], 0, 'f', 4 ).arg( wxyz[1], 0, 'f', 4 ).arg( wxyz[2], 0, 'f', 4 ).arg( wxyz[3], 0, 'f', 4 );
	}
	
protected:
	float	wxyz[4];
	static const float identity[4];
	
	friend class NifIStream;
	friend class NifOStream;
};

class Matrix
{
public:
	Matrix()
	{
		memcpy( m, identity, 36 );
	}
	Matrix operator*( const Matrix & m2 ) const
	{
		Matrix m3;
		for ( int r = 0; r < 3; r++ )
			for ( int c = 0; c < 3; c++ )
				m3.m[r][c] = m[r][0]*m2.m[0][c] + m[r][1]*m2.m[1][c] + m[r][2]*m2.m[2][c];
		return m3;
	}
	Vector3 operator*( const Vector3 & v ) const
	{
		return Vector3(
			m[0][0]*v[0] + m[0][1]*v[1] + m[0][2]*v[2],
			m[1][0]*v[0] + m[1][1]*v[1] + m[1][2]*v[2],
			m[2][0]*v[0] + m[2][1]*v[1] + m[2][2]*v[2] );
	}
	float & operator()( unsigned int c, unsigned int d )
	{
		Q_ASSERT( c < 3 && d < 3 );
		return m[c][d];
	}
	float operator()( unsigned int c, unsigned int d ) const
	{
		Q_ASSERT( c < 3 && d < 3 );
		return m[c][d];
	}
	
	Matrix inverted() const;
	
	void fromQuat( const Quat & q );
	Quat toQuat() const;
	
	void fromEuler( float x, float y, float z );
	bool toEuler( float & x, float & y, float & z ) const;
	
	static Matrix euler( float x, float y, float z )
	{
		Matrix m; m.fromEuler( x, y, z );
		return m;
	}
	
	QString toHtml() const;

protected:
	float m[3][3];
	static const float identity[9];
	
	friend class NifIStream;
	friend class NifOStream;
};

class Matrix4
{
public:
	Matrix4()
	{
		memcpy( m, identity, 64 );
	}
	Matrix4 operator*( const Matrix4 & m2 ) const
	{
		Matrix4 m3;
		for ( int r = 0; r < 4; r++ )
			for ( int c = 0; c < 4; c++ )
				m3.m[r][c] = m[r][0]*m2.m[0][c] + m[r][1]*m2.m[1][c] + m[r][2]*m2.m[2][c] + m[r][3]*m2.m[3][c];
		return m3;
	}
	Vector3 operator*( const Vector3 & v ) const
	{
		return Vector3(
			m[0][0]*v[0] + m[0][1]*v[1] + m[0][2]*v[2] + m[0][3],
			m[1][0]*v[0] + m[1][1]*v[1] + m[1][2]*v[2] + m[1][3],
			m[2][0]*v[0] + m[2][1]*v[1] + m[2][2]*v[2] + m[2][3] );
	}
	float & operator()( unsigned int c, unsigned int d )
	{
		Q_ASSERT( c < 4 && d < 4 );
		return m[c][d];
	}
	float operator()( unsigned int c, unsigned int d ) const
	{
		Q_ASSERT( c < 4 && d < 4 );
		return m[c][d];
	}
	
	Matrix rotation() const;
	Vector3 translation() const;
	Vector3 scale() const;
	
	void decompose( Vector3 & trans, Matrix & rot, Vector3 & scale ) const;
	void compose( const Vector3 & trans, const Matrix & rot, const Vector3 & scale );
	
	//Matrix44 inverted() const;
	
	QString toHtml() const;
	
	const float * data() const { return (float *) m; }

protected:
	float m[4][4];
	static const float identity[16];
	
	friend class NifIStream;
	friend class NifOStream;
};

class Transform
{
public:
	Transform( const NifModel * nif, const QModelIndex & transform );
	Transform()	{ scale = 1.0; }
	
	static bool canConstruct( const NifModel * nif, const QModelIndex & parent );
	
	void writeBack( NifModel * nif, const QModelIndex & transform ) const;
	
	friend Transform operator*( const Transform & t1, const Transform & t2 );
	
	Vector3 operator*( const Vector3 & v ) const
	{
		return rotation * v * scale + translation;
	}
	
	Matrix4 toMatrix4() const;
	
	Matrix rotation;
	Vector3 translation;
	float scale;

	friend QDataStream & operator<<( QDataStream & ds, const Transform & t );
	friend QDataStream & operator>>( QDataStream & ds, Transform & t );
	
	QString toString() const;
};

class Triangle
{
public:
	Triangle() { v[0] = v[1] = v[2] = 0; }
	Triangle( quint16 a, quint16 b, quint16 c ) { set( a, b, c ); }
	
	quint16 & operator[]( unsigned int i )
	{
		Q_ASSERT( i < 3 );
		return v[i];
	}
	const quint16 & operator[]( unsigned int i ) const
	{
		Q_ASSERT( i < 3 );
		return v[i];
	}
	void set( quint16 a, quint16 b, quint16 c )
	{
		v[0] = a; v[1] = b; v[2] = c;
	}
	inline quint16 v1() const { return v[0]; }
	inline quint16 v2() const { return v[1]; }
	inline quint16 v3() const { return v[2]; }
	
	Triangle operator+( quint16 d )
	{
		Triangle t( *this );
		t.v[0] += d;
		t.v[1] += d;
		t.v[2] += d;
		return t;
	}

protected:
	quint16 v[3];
	friend class NifIStream;
	friend class NifOStream;
};

inline float clamp01( float a )
{
	if ( a < 0 )	return 0;
	if ( a > 1 )	return 1;
	return a;
}

class Color3
{
public:
	Color3() { rgb[0] = rgb[1] = rgb[2] = 1.0; }
	explicit Color3( const QColor & c ) { fromQColor( c ); }
	Color3( float r, float g, float b ) { setRGB( r, g, b ); }
	
	float & operator[]( unsigned int i )
	{
		Q_ASSERT( i < 3 );
		return rgb[i];
	}
	
	const float & operator[]( unsigned int i ) const
	{
		Q_ASSERT( i < 3 );
		return rgb[i];
	}
	
	Color3 operator*( float x ) const
	{
		Color3 c( *this );
		c.rgb[0] *= x;
		c.rgb[1] *= x;
		c.rgb[2] *= x;
		return c;
	}
	
	Color3 & operator+=( const Color3 & o )
	{
		for ( int x = 0; x < 3; x++ )
			rgb[x] += o.rgb[x];
		return *this;
	}
	
	Color3 & operator-=( const Color3 & o )
	{
		for ( int x = 0; x < 3; x++ )
			rgb[x] -= o.rgb[x];
		return *this;
	}
	
	Color3 operator+( const Color3 & o ) const
	{
		Color3 c( *this );
		return ( c += o );
	}
	
	Color3 operator-( const Color3 & o ) const
	{
		Color3 c( *this );
		return ( c -= o );
	}
	
	float red() const { return rgb[0]; }
	float green() const { return rgb[1]; }
	float blue() const { return rgb[2]; }
	
	void setRed( float r ) { rgb[0] = r; }
	void setGreen( float g ) { rgb[1] = g; }
	void setBlue( float b ) { rgb[2] = b; }
	
	void setRGB( float r, float g, float b ) { rgb[0] = r; rgb[1] = g; rgb[2] = b; }
	
	QColor toQColor() const
	{
		return QColor::fromRgbF( clamp01( rgb[0] ), clamp01( rgb[1] ), clamp01( rgb[2] ) );
	}
	
	void fromQColor( const QColor & c )
	{
		rgb[0] = c.redF();
		rgb[1] = c.greenF();
		rgb[2] = c.blueF();
	}
	
	const float * data() const { return rgb; }
	
protected:
	float rgb[3];
	
	friend class NifIStream;
	friend class NifOStream;
};

class Color4
{
public:
	Color4() { rgba[0] = rgba[1] = rgba[2] = rgba[3] = 1.0; }
	Color4( const Color3 & c, float alpha = 1.0 ) { rgba[0] = c[0]; rgba[1] = c[1]; rgba[2] = c[2]; rgba[3] = alpha; }
	explicit Color4( const QColor & c ) { fromQColor( c ); }
	Color4( float r, float g, float b, float a ) { setRGBA( r, g, b, a ); }
	
	float & operator[]( unsigned int i )
	{
		Q_ASSERT( i < 4 );
		return rgba[ i ];
	}
	
	const float & operator[]( unsigned int i ) const
	{
		Q_ASSERT( i < 4 );
		return rgba[ i ];
	}
	
	Color4 operator*( float x ) const
	{
		Color4 c( *this );
		c.rgba[0] *= x;
		c.rgba[1] *= x;
		c.rgba[2] *= x;
		c.rgba[3] *= x;
		return c;
	}
	
	Color4 & operator+=( const Color4 & o )
	{
		for ( int x = 0; x < 4; x++ )
			rgba[x] += o.rgba[x];
		return *this;
	}
	
	Color4 & operator-=( const Color4 & o )
	{
		for ( int x = 0; x < 4; x++ )
			rgba[x] -= o.rgba[x];
		return *this;
	}
	
	Color4 operator+( const Color4 & o ) const
	{
		Color4 c( *this );
		return ( c += o );
	}
	
	Color4 operator-( const Color4 & o ) const
	{
		Color4 c( *this );
		return ( c -= o );
	}
	
	float red() const { return rgba[0]; }
	float green() const { return rgba[1]; }
	float blue() const { return rgba[2]; }
	float alpha() const { return rgba[3]; }
	
	void setRed( float r ) { rgba[0] = r; }
	void setGreen( float g ) { rgba[1] = g; }
	void setBlue( float b ) { rgba[2] = b; }
	void setAlpha( float a ) { rgba[3] = a; }
	
	void setRGBA( float r, float g, float b, float a ) { rgba[ 0 ] = r; rgba[ 1 ] = g; rgba[ 2 ] = b; rgba[ 3 ] = a; }

	QColor toQColor() const
	{
		return QColor::fromRgbF( clamp01( rgba[0] ), clamp01( rgba[1] ), clamp01( rgba[2] ), clamp01( rgba[3] ) );
	}
	
	void fromQColor( const QColor & c )
	{
		rgba[0] = c.redF();
		rgba[1] = c.greenF();
		rgba[2] = c.blueF();
		rgba[3] = c.alphaF();
	}
	
	const float * data() const { return rgba; }
	
	Color4 blend( float alpha ) const
	{
		Color4 c( *this );
		c.setAlpha( c.alpha() * alpha );
		return c;
	}

protected:
	float rgba[4];
	
	friend class NifIStream;
	friend class NifOStream;
};

class NifValue
{
public:
	enum Type
	{
		tBool = 0,
		tByte = 1,
		tWord = 2,
		tFlags = 3,
		tStringOffset = 4,
		tBlockTypeIndex = 5,
		tInt = 6,
		tLink = 7,
		tUpLink = 8,
		tFloat = 9,
		tString = 10,
		tText = 11,
		tShortString = 12,
		tFilePath = 13,
		tHeaderString = 14,
		tColor3 = 15,
		tColor4 = 16,
		tVector3 = 17,
		tQuat = 18,
		tQuatXYZW = 19,
		tMatrix = 20,
		tMatrix4 = 21,
		tVector2 = 22,
		tVector4 = 23,
		tTriangle = 24,
		tFileVersion = 25,
		tByteArray = 26,
		tStringPalette = 27,
      tShort = 28,
      tUInt = 29,

		tNone = 0xff
	};
	
	template <typename T> static Type typeId();
	
	static void initialize();
	static Type type( const QString & typId );
	static bool registerAlias( const QString & alias, const QString & internal );
	
	NifValue() { typ = tNone; }
	NifValue( Type t );
	NifValue( const NifValue & other );
	
	~NifValue();
	
	void clear();
	void changeType( Type );
	
	void operator=( const NifValue & other );
	
	Type type() const { return typ; }
	
	static bool isValid( Type t ) { return t != tNone; }
	static bool isLink( Type t ) { return t == tLink || t == tUpLink; }
	
	bool isValid() const { return typ != tNone; }
	bool isColor() const { return typ == tColor3 || typ == tColor4; }
	bool isCount() const { return (typ >= tBool && typ <= tInt) || (typ >= tShort && typ <= tUInt); }
	bool isFlags() const { return typ == tFlags; }
	bool isFloat() const { return typ == tFloat; }
	bool isLink() const { return typ == tLink || typ == tUpLink; }
	bool isMatrix() const { return typ == tMatrix; }
	bool isMatrix4() const { return typ == tMatrix4; }
	bool isQuat() const { return typ == tQuat || typ == tQuatXYZW; }
	bool isString() const { return typ >= tString && typ <= tHeaderString; }
	bool isVector4() const { return typ == tVector4; }
	bool isVector3() const { return typ == tVector3; }
	bool isVector2() const { return typ == tVector2; }
	bool isTriangle() const { return typ == tTriangle; }
	bool isByteArray() const { return typ == tByteArray || typ == tStringPalette; }
	bool isFileVersion() const { return typ == tFileVersion; }
	
	QColor toColor() const;
	quint32 toCount() const;
	float toFloat() const;
	qint32 toLink() const;
	quint32 toFileVersion() const;

	QString toString() const;
	QVariant toVariant() const;
	
	bool setCount( quint32 );
	bool setFloat( float );
	bool setLink( int );
	bool setFileVersion( quint32 );
	
	bool fromString( const QString & );
	bool fromVariant( const QVariant & );
	
	template <typename T> bool ask( T * t = 0 ) const;
	template <typename T> T get() const;
	template <typename T> bool set( const T & x );

protected:
	Type typ;
	
	union Value
	{
		quint8	u08;
		quint16 u16;
		quint32 u32;
		qint32	i32;
		float	f32;
		void *	data;
	} val;
	
	template <typename T> T getType( Type t ) const;
	template <typename T> bool setType( Type t, T v );
	
	static QHash<QString,Type>	typeMap;
	
	friend class NifIStream;
	friend class NifOStream;
};

inline quint32 NifValue::toCount() const { if ( isCount() ) return val.u32; return 0; }
inline float NifValue::toFloat() const { if ( isFloat() ) return val.f32; else return 0.0; }
inline qint32 NifValue::toLink() const { if ( isLink() ) return val.i32; else return -1; }
inline quint32 NifValue::toFileVersion() const { if ( isFileVersion() ) return val.u32; else return 0; }

inline bool NifValue::setCount( quint32 c ) { if ( isCount() ) { val.u32 = c; return true; } else return false; }
inline bool NifValue::setFloat( float f ) { if ( isFloat() ) { val.f32 = f; return true; } else return false; }
inline bool NifValue::setLink( int l ) { if ( isLink() ) { val.i32 = l; return true; } else return false; }
inline bool NifValue::setFileVersion( quint32 v ) { if ( isFileVersion() ) { val.u32 = v; return true; } else return false; }

template <typename T> inline T NifValue::getType( Type t ) const
{
	if ( typ == t )
		return *static_cast<T*>( val.data );
	else
		return T();
}

template <typename T> inline bool NifValue::setType( Type t, T v )
{
	if ( typ == t )
	{
		*static_cast<T*>( val.data ) = v;
		return true;
	}
	return false;
}

template <> inline bool NifValue::get() const { return toCount(); }
template <> inline qint32 NifValue::get() const { return toCount(); }
template <> inline quint32 NifValue::get() const { return toCount(); }
template <> inline qint16 NifValue::get() const { return toCount(); }
template <> inline quint16 NifValue::get() const { return toCount(); }
template <> inline quint8 NifValue::get() const { return toCount(); }
template <> inline float NifValue::get() const { return toFloat(); }
template <> inline QColor NifValue::get() const { return toColor(); }
template <> inline QVariant NifValue::get() const { return toVariant(); }

template <> inline Matrix NifValue::get() const { return getType<Matrix>( tMatrix ); }
template <> inline Matrix4 NifValue::get() const { return getType<Matrix4>( tMatrix4 ); }
template <> inline Vector4 NifValue::get() const { return getType<Vector4>( tVector4 ); }
template <> inline Vector3 NifValue::get() const { return getType<Vector3>( tVector3 ); }
template <> inline Vector2 NifValue::get() const { return getType<Vector2>( tVector2 ); }
template <> inline Color3 NifValue::get() const { return getType<Color3>( tColor3 ); }
template <> inline Color4 NifValue::get() const { return getType<Color4>( tColor4 ); }
template <> inline Triangle NifValue::get() const { return getType<Triangle>( tTriangle ); }
template <> inline QString NifValue::get() const
{
	if ( isString() )
		return *static_cast<QString*>( val.data );
	else
		return QString();
}
template <> inline QByteArray NifValue::get() const
{
	if ( isByteArray() )
		return *static_cast<QByteArray*>( val.data );
	else
		return QByteArray();
}
template <> inline Quat NifValue::get() const
{
	if ( isQuat() )
		return *static_cast<Quat*>( val.data );
	else
		return Quat();
}

template <> inline bool NifValue::set( const bool & b ) { return setCount( b ); }
template <> inline bool NifValue::set( const int & i ) { return setCount( i ); }
template <> inline bool NifValue::set( const quint32 & i ) { return setCount( i ); }
template <> inline bool NifValue::set( const qint16 & i ) { return setCount( i ); }
template <> inline bool NifValue::set( const quint16 & i ) { return setCount( i ); }
template <> inline bool NifValue::set( const quint8 & i ) { return setCount( i ); }
template <> inline bool NifValue::set( const float & f ) { return setFloat( f ); }
template <> inline bool NifValue::set( const Matrix & x ) { return setType( tMatrix, x ); }
template <> inline bool NifValue::set( const Matrix4 & x ) { return setType( tMatrix4, x ); }
template <> inline bool NifValue::set( const Vector4 & x ) { return setType( tVector4, x ); }
template <> inline bool NifValue::set( const Vector3 & x ) { return setType( tVector3, x ); }
template <> inline bool NifValue::set( const Vector2 & x ) { return setType( tVector2, x ); }
template <> inline bool NifValue::set( const Color3 & x ) { return setType( tColor3, x ); }
template <> inline bool NifValue::set( const Color4 & x ) { return setType( tColor4, x ); }
template <> inline bool NifValue::set( const Triangle & x ) { return setType( tTriangle, x ); }
template <> inline bool NifValue::set( const QString & x )
{
	if ( isString() )
	{
		*static_cast<QString*>( val.data ) = x;
		return true;
	}
	return false;
}
template <> inline bool NifValue::set( const QByteArray & x )
{
	if ( isByteArray() )
	{
		*static_cast<QByteArray*>( val.data ) = x;
		return true;
	}
	return false;
}
template <> inline bool NifValue::set( const Quat & x )
{
	if ( isQuat() )
	{
		*static_cast<Quat*>( val.data ) = x;
		return true;
	}
	return false;
}

template <> inline bool NifValue::ask( bool * ) const { return isCount(); }
template <> inline bool NifValue::ask( int * ) const { return isCount(); }
template <> inline bool NifValue::ask( short * ) const { return isCount(); }
template <> inline bool NifValue::ask( float * ) const { return isFloat(); }
template <> inline bool NifValue::ask( Matrix * ) const { return type() == tMatrix; }
template <> inline bool NifValue::ask( Matrix4 * ) const { return type() == tMatrix4; }
template <> inline bool NifValue::ask( Quat * ) const { return isQuat(); }
template <> inline bool NifValue::ask( Vector4 * ) const { return type() == tVector4; }
template <> inline bool NifValue::ask( Vector3 * ) const { return type() == tVector3; }
template <> inline bool NifValue::ask( Vector2 * ) const { return type() == tVector2; }
template <> inline bool NifValue::ask( Color3 * ) const { return type() == tColor3; }
template <> inline bool NifValue::ask( Color4 * ) const { return type() == tColor4; }
template <> inline bool NifValue::ask( Triangle * ) const { return type() == tTriangle; }
template <> inline bool NifValue::ask( QString * ) const { return isString(); }
template <> inline bool NifValue::ask( QByteArray * ) const { return isByteArray(); }

class BaseModel;

class NifIStream
{
public:
	NifIStream( BaseModel * m, QIODevice * d ) : model( m ), device( d ) { init(); }
	
	bool read( NifValue & );

private:
	BaseModel * model;
	QIODevice * device;
	
	void init();
	
	bool bool32bit;
};

class NifOStream
{
public:
	NifOStream( const BaseModel * n, QIODevice * d ) : model( n ), device( d ) { init(); }
	
	bool write( const NifValue & );

private:
	const BaseModel * model;
	QIODevice * device;
	
	void init();
	
	bool bool32bit;
};


Q_DECLARE_METATYPE( NifValue );

#endif

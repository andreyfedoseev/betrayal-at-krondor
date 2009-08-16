/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Copyright (C) 2005-2009 Guido de Jong <guidoj@users.sf.net>
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
static const float PI  = M_PI;
static const float PI2 = M_PI + M_PI;

static const unsigned int ANGLE_BITS = 8;
static const unsigned int ANGLE_SIZE = 1 << ANGLE_BITS;
static const unsigned int ANGLE_MASK = ANGLE_SIZE - 1;

class Angle
{
    private:
        int m_angle;
        static bool m_initialized;
        static float m_cosTbl[ANGLE_SIZE];
        static float m_sinTbl[ANGLE_SIZE];
        static float m_tanTbl[ANGLE_SIZE];
    public:
        Angle ( const int a );
        ~Angle();
        int Get() const;
        void Set ( const int a );
        float GetCos() const;
        float GetSin() const;
        float GetTan() const;
        Angle& operator= ( const Angle &a );
        Angle& operator+= ( const Angle &a );
        Angle& operator-= ( const Angle &a );
        Angle operator+ ( const Angle &a );
        Angle operator- ( const Angle &a );
        bool operator== ( const Angle &a ) const;
        bool operator!= ( const Angle &a ) const;
        bool operator< ( const Angle &a ) const;
        bool operator> ( const Angle &a ) const;
        bool operator<= ( const Angle &a ) const;
        bool operator>= ( const Angle &a ) const;
};

class Vector2D
{
    private:
        int m_x;
        int m_y;
    public:
        Vector2D();
        Vector2D ( const int x, const int y );
        Vector2D ( const Vector2D &p );
        virtual ~Vector2D();
        Vector2D& operator= ( const Vector2D &p );
        Vector2D& operator+= ( const Vector2D &p );
        Vector2D& operator-= ( const Vector2D &p );
        Vector2D& operator*= ( const int f );
        Vector2D& operator/= ( const int f );
        Vector2D& operator*= ( const float f );
        Vector2D& operator/= ( const float f );
        Vector2D operator+ ( const Vector2D &p );
        Vector2D operator- ( const Vector2D &p );
        Vector2D operator* ( const int f );
        Vector2D operator/ ( const int f );
        Vector2D operator* ( const float f );
        Vector2D operator/ ( const float f );
        bool operator== ( const Vector2D &p ) const;
        bool operator!= ( const Vector2D &p ) const;
        bool operator< ( const Vector2D &p ) const;
        bool operator> ( const Vector2D &p ) const;
        bool operator<= ( const Vector2D &p ) const;
        bool operator>= ( const Vector2D &p ) const;
        int GetX() const;
        int GetY() const;
        void SetX ( const int x );
        void SetY ( const int y );
        unsigned int GetRho() const;
        int GetTheta() const;
};

class Vector3D
{
    private:
        int m_x;
        int m_y;
        int m_z;
    public:
        Vector3D();
        Vector3D ( const int x, const int y, const int z );
        Vector3D ( const Vector3D &p );
        Vector3D ( const Vector2D &p );
        virtual ~Vector3D();
        Vector3D& operator= ( const Vector3D &p );
        Vector3D& operator+= ( const Vector3D &p );
        Vector3D& operator-= ( const Vector3D &p );
        Vector3D& operator= ( const Vector2D &p );
        Vector3D& operator+= ( const Vector2D &p );
        Vector3D& operator-= ( const Vector2D &p );
        Vector3D& operator*= ( const int f );
        Vector3D& operator/= ( const int f );
        Vector3D& operator*= ( const float f );
        Vector3D& operator/= ( const float f );
        Vector3D operator+ ( const Vector3D &p );
        Vector3D operator- ( const Vector3D &p );
        Vector3D operator+ ( const Vector2D &p );
        Vector3D operator- ( const Vector2D &p );
        Vector3D operator* ( const int f );
        Vector3D operator/ ( const int f );
        Vector3D operator* ( const float f );
        Vector3D operator/ ( const float f );
        bool operator== ( const Vector3D &p ) const;
        bool operator!= ( const Vector3D &p ) const;
        bool operator< ( const Vector3D &p ) const;
        bool operator> ( const Vector3D &p ) const;
        bool operator<= ( const Vector3D &p ) const;
        bool operator>= ( const Vector3D &p ) const;
        int GetX() const;
        int GetY() const;
        int GetZ() const;
        void SetX ( const int x );
        void SetY ( const int y );
        void SetZ ( const int z );
        unsigned int GetRho() const;
        int GetTheta() const;
};

class Rectangle
{
    private:
        int m_x;
        int m_y;
        int m_width;
        int m_height;
    public:
        Rectangle ( const int x, const int y, const int w, const int h );
        Rectangle ( const Rectangle &r );
        virtual ~Rectangle();
        Rectangle& operator= ( const Rectangle &r );
        bool operator== ( const Rectangle &r );
        bool operator!= ( const Rectangle &r );
        bool operator< ( const Rectangle &r );
        bool operator> ( const Rectangle &r );
        bool operator<= ( const Rectangle &r );
        bool operator>= ( const Rectangle &r );
        int GetXPos() const;
        int GetYPos() const;
        int GetXCenter() const;
        int GetYCenter() const;
        int GetWidth() const;
        int GetHeight() const;
        void SetXPos ( const int x );
        void SetYPos ( const int x );
        void SetWidth ( const int w );
        void SetHeight ( const int h );
        bool IsInside ( const Vector2D &p );
};

#endif

#ifndef PARTICLE_H
#define PARTICLE_H

#include "vector2.h"

class Particle
{
public:
	Vector2 m_position;
	Vector2 m_velicity;
	Vector2 m_acceleration;
	float m_age;

};

#endif
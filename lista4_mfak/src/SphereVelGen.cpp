#include "SphereVelGen.h"

void SphereVelGen::Generate(double dt, ParticleData* p, size_t startId, size_t endId)
{
	float phi, theta, v, r;
	for (size_t i = startId; i < endId; ++i)
	{
		phi = glm::linearRand(-M_PI, M_PI);
		theta = glm::linearRand(-M_PI, M_PI);
		v = glm::linearRand(m_minVel, m_maxVel);

		r = v * sinf(phi);
		p->particles[i].get()->velocity.z = v * cosf(phi);
		p->particles[i].get()->velocity.x = r * cosf(theta);
		p->particles[i].get()->velocity.y = r * sinf(theta);
	}
}
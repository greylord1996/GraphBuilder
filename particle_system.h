#include "vector2f.h"
#include <vector>
#include <iostream>




class Particle
{
public:
	void Integrate(float dt)
	{
		Vector2f currPos = pos;
		pos = pos + (pos - prevPos) + acceleration * dt * dt;
		prevPos = currPos;

	}
	float radius;
	Vector2f pos;
	Vector2f acceleration;
	Vector2f prevPos;

};

class Link
{
public:
	Link(){}
	Link(Particle* p0, Particle* p1, float stiffness) 
	{
			this->p0 = p0;
			this->p1 = p1;
			this->stiffness = stiffness;
			this->defLength = (p0->pos - p1->pos).Length();
	}
	
	void Solve()
	{
		Vector2f delta = p1->pos - p0->pos;
		float deform = delta.Length() - this->defLength;
		p0->pos = p0->pos + delta.Norma() * deform * (0.5f) * stiffness;
		p1->pos = p1->pos + delta.Norma() * deform * (-0.5f) * stiffness;

	}
	Particle* p0;
	Particle* p1;
	float stiffness;
	float defLength;

};


class VolumeLink
{
public:
	VolumeLink() {}
	VolumeLink(const std::vector<Particle*>&  vec/*, float atmosphericPressure, */)
	{
		for (int i = 0; i < vec.size(); i++)
			this->volumeParticles.push_back(vec[i]);
		this->initialVolume = Square();
	}

	float Square()
	{
		float volume = 0;
		const int count = volumeParticles.size();

		for (std::size_t i = 0; i < volumeParticles.size(); i++)
		{
			volume += (volumeParticles[(i + 1) % volumeParticles.size()]->pos ^ volumeParticles[i]->pos * 0.5f);
		}
		return volume;
	}

	void VolumeSolve()
	{
		float currVolume = Square();
		float pressureDiff = initialPressure * initialVolume / currVolume - atmosphericPressure;
		
		for (size_t i = 0; i < volumeParticles.size(); i++)
		{
			Vector2f delta = volumeParticles[(i + 1) % volumeParticles.size()]->pos - volumeParticles[i]->pos;
			Vector2f force = Vector2f(-delta.y, delta.x) * pressureDiff * (-1); 
			volumeParticles[(i + 1) % volumeParticles.size()]->pos = force + volumeParticles[(i + 1) % volumeParticles.size()]->pos;
			volumeParticles[i]->pos = force + volumeParticles[i]->pos;
		}


	}

private:
	std::vector<Particle*> volumeParticles;
	float initialVolume ;
	float initialPressure = 0.0005f;
	float atmosphericPressure = 0.0005f;

};




class ParticleSystem
{

private:
	std::vector<Particle*> particles;
	std::vector<Link> links;
	VolumeLink volumeLink;
	std::vector<VolumeLink> volumelinks;

public:
	ParticleSystem()
	{
		
	}
	
	void Update()
	{
		for (size_t particleIndex = 0; particleIndex < particles.size(); particleIndex++)
		{
			particles[particleIndex]->Integrate(0.05f);

			float floorLevel = 600.0f;

			if (particles[particleIndex]->pos.y > floorLevel)
			{
				particles[particleIndex]->pos.y = floorLevel;
			}

			/*for (size_t linkIndex = 0; linkIndex < links.size(); linkIndex++)
			{
				links[linkIndex].Solve();
			}*/

			for (size_t linkIndex = 0; linkIndex < links.size(); linkIndex++)
			{
				links[linkIndex].Solve();
			}
		}

		/*for (size_t linkIndex = 0; linkIndex < links.size(); linkIndex++)
		{
			links[linkIndex].Solve();
		}*/

		
			volumeLink.VolumeSolve();
		

	}


	Particle* GetParticle(int particleIndex)
	{
		return particles[particleIndex];
	}

	size_t GetParticleCount()
	{
		return particles.size();
	}

	Particle* AddParticle(Vector2f pos, float radius)
	{
		Particle* newbie = new Particle;
//		Vector2f currPos;
		newbie->pos = pos;
		newbie->prevPos = pos;

		newbie->acceleration = Vector2f(0.0f, 2.5f);
		newbie->radius = radius;
		particles.push_back(newbie);
		return particles.back();
	}

	void AddLink(Particle* p0, Particle* p1, float stiffness)
	{
		links.push_back(Link(p0, p1, stiffness));
	}

	void AddVolumeLink()
	{
		this->volumeLink = VolumeLink(this->particles);
	}
};
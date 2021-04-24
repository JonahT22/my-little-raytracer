#pragma once
#include "Scene.h"

#include <iostream>
using namespace glm;
using namespace std;

// Main render loop
glm::vec3 Scene::ComputeRayColor(Ray3D ray)
{
	HitResult hit;
	for (auto object : allObjects) {
		if (object->Hit(ray, hit)) {
			// If hit was successfull (i.e. found a new tMin), store a reference to the object
			hit.hitObject = object;
		}
	}

	// Check if the ray actually hit anything
	if (hit.hitObject != nullptr) {
		// Calculate the hit's properties, now that we know that this hit is the closest one 
		// (this way, we only have to do these calculations once)

		// New position from tMin (TODO: is storing the hit loc necessary?)
		hit.loc = ray.FindLocAtTime(hit.t);

		// During intersection checks, hit.nor is filled with local-space normal. Now, convert to world space
		hit.nor = normalize(hit.hitObject->GetInverseTranspose() * hit.nor);

		// Color with normals
		// Normal -> color conversion taken from assigment handout
		double r = (0.5 * hit.nor.x + 0.5);
		double g = (0.5 * hit.nor.y + 0.5);
		double b = (0.5 * hit.nor.z + 0.5);
		return vec3(r, g, b);
	}
	// Background color
	else return glm::vec3(0, 0, 0);
}

void Scene::BuildSceneFromFile(std::string filename)
{
}
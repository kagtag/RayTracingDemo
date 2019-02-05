#include"SmoothUVMeshTriangle.h"

SmoothUVMeshTriangle::SmoothUVMeshTriangle()
	:SmoothMeshTriangle()
{}

SmoothUVMeshTriangle::SmoothUVMeshTriangle(Mesh* mesh, int i0, int i1, int i2)
	:SmoothMeshTriangle(mesh, i0, i1, i2)
{}

bool
SmoothUVMeshTriangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	Point3D v0(mesh_ptr->vertices[index0]);
}
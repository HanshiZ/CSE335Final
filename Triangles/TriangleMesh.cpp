/**
 * \file TriangleMesh.cpp
 *
 * \author 
 */

#include "pch.h"
#include "TriangleMesh.h"
#include "Vertex.h"


using namespace Gdiplus;

/**
 * Get the number of triangles in the mesh.
 * \return Number of triangles
 */
int CTriangleMesh::GetNumTriangles()
{ 
    // Placeholder, not the valid return value
    return 0;
}


/**
 * Get one of the mesh triangles.
 * \param n Triangle index, 0 to number of triangles-1.
 * \returns Triangle object.
 */
std::shared_ptr<CTriangle> CTriangleMesh::GetTriangle(int n)
{
    // Placeholder, not the valid return value
    return nullptr;
}





/**
 * Draw the triangle mesh.
 * \param graphics GDI+ graphics object to draw on.
 */
void CTriangleMesh::Draw(Gdiplus::Graphics* graphics)
{
}

/**
 * Create a vertex.
 * \param x Vertex X location
 * \param y Vertex Y location
 * \return Added vertex object
 */
std::shared_ptr<CVertex> CTriangleMesh::AddVertex(int x, int y)
{
    // Placeholder, not the valid return value
    return nullptr;
}


/**
 * Create a triangle.
 * \param v1 First vertex
 * \param v2 Second vertex
 * \param v3 Third vertex
 * \param color Color to draw the triangle
 * \return CTriangle object.
 */
std::shared_ptr<CTriangle> CTriangleMesh::AddTriangle(std::shared_ptr<CVertex> v1,
    std::shared_ptr<CVertex> v2,
    std::shared_ptr<CVertex> v3,
    Gdiplus::Color color)
{
    // Placeholder, not the valid return value
    return nullptr;
}

/**
 * Create a filled triangle.
 * \param v1 First vertex
 * \param v2 Second vertex
 * \param v3 Third vertex
 * \param color Color to draw the triangle
 * \return CTriangle object.
 */
std::shared_ptr<CTriangle> CTriangleMesh::AddFilledTriangle(std::shared_ptr<CVertex> v1,
    std::shared_ptr<CVertex> v2,
    std::shared_ptr<CVertex> v3,
    Gdiplus::Color color)
{
    // Placeholder, not the valid return value
    return nullptr;
}


/**
 * System class that defines a triangle mesh.
 *
 * \file TriangleMesh.h
 */

#pragma once

#include <memory>
#include <vector>

#include "Triangle.h"

class CVertex;
class CTriangle;
class CFilledTriangle;

/**
 * Abstraction of a triangle mesh.
 */
class CTriangleMesh
{
public:
    CTriangleMesh() {}
    ~CTriangleMesh() {}

    /** Copy constructor disabled */
    CTriangleMesh(const CTriangleMesh&) = delete;
    /** Assignment operator disabled */
    void operator=(const CTriangleMesh&) = delete;

    void Draw(Gdiplus::Graphics* graphics);

    std::shared_ptr<CVertex> AddVertex(int x, int y);

    std::shared_ptr<CTriangle> AddTriangle(std::shared_ptr<CVertex> v1,
        std::shared_ptr<CVertex> v2, std::shared_ptr<CVertex> v3, Gdiplus::Color color);
    std::shared_ptr<CTriangle> AddFilledTriangle(std::shared_ptr<CVertex> v1,
        std::shared_ptr<CVertex> v2, std::shared_ptr<CVertex> v3, Gdiplus::Color color);

    int GetNumTriangles();
    std::shared_ptr<CTriangle> GetTriangle(int n);
};


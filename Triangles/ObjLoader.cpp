/**
 * \file ObjLoader.cpp
 *
 * \author Charles Owen
 */

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "ObjLoader.h"
#include "TriangleMesh.h"

using namespace std;
using namespace Gdiplus;


/**
 * OBJ file format loader.
 *
 * Loads an OBJ file into a CTriangleMesh object.
 *
 * \param random Random number generator to use.
 */
CObjLoader::CObjLoader(std::mt19937* random) : mRandom(random)
{
    mColor = Color(24, 69, 59);
}


/**
 * Load an OBJ file, returning a triangle mesh object
 * \param filename File to load
 * \returns CTriangleMesh object.
 */
std::shared_ptr<CTriangleMesh> CObjLoader::Load(std::wstring filename)
{
    // Create the mesh
    auto mesh = std::make_shared<CTriangleMesh>();


    // Open the file
    ifstream file(filename.c_str());
    
    std::string line;
    while (std::getline(file, line))
    {
        if (line.length() > 0) 
        {
            switch (line[0])
            {
            case 'v':
                AddVertex(mesh, line);
                break;

            case 'f':
                AddTriangle(mesh, line);
                break;
            }
        int xx = 0;
        }

    }

    return mesh;
}


/**
 * Add a vertex from the OBJ file.
 * \param mesh Mesh to add the triangle to
 * \param line Line from the file
 */
void CObjLoader::AddVertex(std::shared_ptr<CTriangleMesh> mesh, const std::string& line)
{
    stringstream str(line);
   
    char c;
    double x, y, z;
    str >> c >> x >> y >> z;

    auto vertex = mesh->AddVertex((int)(x*mScale), -(int)(z*mScale));
    mVertices.push_back(vertex);
}


/**
 * Add a triangle from the OBJ file.
 * \param mesh Mesh to add the triangle to
 * \param line Line from the file
 */
void CObjLoader::AddTriangle(std::shared_ptr<CTriangleMesh> mesh, const std::string& line)
{
    stringstream str(line);

    char c;
    unsigned int v1, v2, v3;
    str >> c >> v1 >> v2 >> v3;

    auto color = mColor;
    if (mRandomColors)
    {
        uniform_int_distribution<> distribution(0, 255);
        color = Color((BYTE)distribution(*mRandom), (BYTE)distribution(*mRandom), (BYTE)distribution(*mRandom));
    }

    if (v1 > 0 && v1 < mVertices.size() &&
        v2 > 0 && v2 < mVertices.size() &&
        v3 > 0 && v3 < mVertices.size())
    {
        auto vv1 = mVertices[v1-1];
        auto vv2 = mVertices[v2-1];
        auto vv3 = mVertices[v3-1];

        if (mFilled) 
        {
            auto triangle = mesh->AddFilledTriangle(vv1, vv2, vv3, color);
        }
        else
        {
            auto triangle = mesh->AddTriangle(vv1, vv2, vv3, color);
        }
    }

}
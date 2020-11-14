/**
 * \file ChildView.cpp
 *
 * \author Charles Owen
 */

#include "pch.h"
#include "framework.h"
#include "Triangles.h"
#include "ChildView.h"
#include "DoubleBufferDC.h"
#include "TriangleMesh.h"
#include "ObjLoader.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

/**
 * Constructor
 */
CChildView::CChildView()
{
	std::random_device rd;	// Generates a random seed
	mRandom.seed(rd());		// Seed the random number generator

	// Create an initial, empty triangle mesh.
	mMesh = make_shared<CTriangleMesh>();

	// 
	// It is possible to load OBJ files here or call any of the 
	// example functions:
	//
	// OnExamples1triangle();
	// OnExamples1Filledtriangle();
	// OnExamplesBox();
	// OnExamples3triangles();
	// MeshFile(L"files/m.obj");
	// MeshFile(L"files/michigan.obj");
	//
}

/**
 * Destructor
 */
CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_MESHES_EMPTY, &CChildView::OnExamplesEmpty)
	ON_COMMAND(ID_MESHES_1TRIANGLE, &CChildView::OnExamples1triangle)
	ON_COMMAND(ID_MESHES_1FILLEDTRIANGLE, &CChildView::OnExamples1filledtriangle)
    ON_COMMAND(ID_MESHES_M, &CChildView::OnMeshesM)
	ON_COMMAND(ID_MESHES_MSU, &CChildView::OnMeshesMsu)
	ON_COMMAND(ID_MESHES_LINES, &CChildView::OnMeshesLines)
	ON_UPDATE_COMMAND_UI(ID_MESHES_LINES, &CChildView::OnUpdateMeshesLines)
	ON_COMMAND(ID_MESHES_FILLED, &CChildView::OnMeshesFilled)
	ON_COMMAND(ID_MESHES_RANDOMCOLORS, &CChildView::OnMeshesRandomcolors)
	ON_UPDATE_COMMAND_UI(ID_MESHES_RANDOMCOLORS, &CChildView::OnUpdateMeshesRandomcolors)
	ON_UPDATE_COMMAND_UI(ID_MESHES_FILLED, &CChildView::OnUpdateMeshesFilled)
	ON_COMMAND(ID_MESHES_MICHIGAN, &CChildView::OnMeshesMichigan)
	ON_COMMAND(ID_EXAMPLES_BOX, &CChildView::OnExamplesBox)
    ON_COMMAND(ID_EXAMPLES_3TRIANGLES, &CChildView::OnExamples3triangles)
END_MESSAGE_MAP()

using namespace Gdiplus;


/**
 * Called before the window is created
 * \param cs Create structure
 * \returns true if successful
 */
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}


/**
 * Called to paint the window.
 */
void CChildView::OnPaint() 
{
	CPaintDC paintDC(this);     // device context for painting
	CDoubleBufferDC dc(&paintDC); // device context for painting

	Graphics graphics(dc.m_hDC);    // Create GDI+ graphics context

	mNotDrawnYet = false;

	mMesh->Draw(&graphics);

	//for (auto triangle : *mMesh)
	//{
	//	triangle->Draw(&graphics);
	//}
}


/**
 * Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context
 * \returns FALSE
 */
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

/**
 * A safe version of Invalidate(). 
 *
 * You can't call Invalidate before the window is 
 * created, so you can't call it in a constructor. To
 * make it possible to call the menu handlers in the 
 * constructor we create this function that won't actually
 * call Invalidate until after the first time the window
 * is drawn.
 */
void CChildView::SafeInvalidate()
{
	if (mNotDrawnYet)
	{
		return;
	}

	Invalidate();
}



/**
 * Example mesh: Empty, not triangles
 */
void CChildView::OnExamplesEmpty()
{
	NoMeshFile();

	auto mesh = std::make_shared<CTriangleMesh>();
	mMesh = mesh;

	SafeInvalidate();
}

/**
 * Example mesh: One triangle
 */
void CChildView::OnExamples1triangle()
{
	NoMeshFile();

	// Create the three vertices
	auto mesh = std::make_shared<CTriangleMesh>();
	mMesh = mesh;

	auto v1 = mesh->AddVertex(200, 100);
	auto v2 = mesh->AddVertex(300, 200);
	auto v3 = mesh->AddVertex(100, 200);

	auto triangle = mesh->AddTriangle(v1, v2, v3, Color::DarkGreen);
	SafeInvalidate();
}


/**
 * Example of one filled triangle.
 */
void CChildView::OnExamples1filledtriangle()
{
	NoMeshFile();

	// Create the three vertices
	auto mesh = std::make_shared<CTriangleMesh>();
	mMesh = mesh;

	auto v1 = mesh->AddVertex(100, 100);
	auto v2 = mesh->AddVertex(300, 100);
	auto v3 = mesh->AddVertex(200, 200);

	auto triangle = mesh->AddFilledTriangle(v1, v2, v3, Color::DarkBlue);
	SafeInvalidate();
}



/**
 * Example of two triangles making a box.
 */
void CChildView::OnExamplesBox()
{
	NoMeshFile();

	// Create the three vertices
	auto mesh = std::make_shared<CTriangleMesh>();
	mMesh = mesh;

	auto v1 = mesh->AddVertex(100, 100);
	auto v2 = mesh->AddVertex(100, 400);
	auto v3 = mesh->AddVertex(400, 400);
	auto v4 = mesh->AddVertex(400, 100);

	auto triangle = mesh->AddFilledTriangle(v1, v2, v3, Color::DarkBlue);
	triangle = mesh->AddFilledTriangle(v1, v3, v4, Color::DarkRed);
	SafeInvalidate();
}



/**
 * Example of three triangles.
 */
void CChildView::OnExamples3triangles()
{
	NoMeshFile();

	// Create the three vertices
	auto mesh = std::make_shared<CTriangleMesh>();
	mMesh = mesh;

	auto v1 = mesh->AddVertex(100, 100);
	auto v2 = mesh->AddVertex(100, 400);
	auto v3 = mesh->AddVertex(400, 400);
	auto v4 = mesh->AddVertex(400, 100);
	auto v5 = mesh->AddVertex(500, 250);

	auto triangle = mesh->AddFilledTriangle(v1, v2, v3, Color::DarkBlue);
	triangle = mesh->AddFilledTriangle(v1, v3, v4, Color::DarkRed);
	triangle = mesh->AddFilledTriangle(v4, v3, v5, Color::DarkGreen);
	SafeInvalidate();
}




/**
 * Load a mesh file from a .OBJ file.
 * \param name File name/path
 */
void CChildView::MeshFile(const std::wstring& name)
{
	mMeshFile = name;
	SetMesh();
}

/**
 * Set to no current mesh file
 */
void CChildView::NoMeshFile()
{
	mMeshFile = L"";
	mMesh = make_shared<CTriangleMesh>();
}

/**
 * Set the mesh to the current mesh file.
 */
void CChildView::SetMesh()
{
	if (mMeshFile.empty())
	{
		return;
	}

	CObjLoader loader(&mRandom);
	loader.SetFilled(mFillType == FillType::Filled);
	loader.SetRandomColors(mRandomColors);

	mMesh = loader.Load(mMeshFile);
}


/// \cond

void CChildView::OnMeshesM()
{
	MeshFile(L"files/m.obj");
	Invalidate();
}

void CChildView::OnMeshesMsu()
{
	MeshFile(L"files/msu.obj");
	Invalidate();
}


void CChildView::OnMeshesMichigan()
{
	MeshFile(L"files/michigan.obj");
	Invalidate();
}



void CChildView::OnMeshesLines()
{
	mFillType = FillType::Lines;
	SetMesh();
	Invalidate();
}


void CChildView::OnUpdateMeshesLines(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(mFillType == FillType::Lines);
}


void CChildView::OnMeshesFilled()
{
	mFillType = FillType::Filled;
	SetMesh();
	Invalidate();
}

void CChildView::OnUpdateMeshesFilled(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(mFillType == FillType::Filled);
}


void CChildView::OnMeshesRandomcolors()
{
	mRandomColors = !mRandomColors;
	SetMesh();
	Invalidate();
}


void CChildView::OnUpdateMeshesRandomcolors(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(mRandomColors);
}

/// \endcond

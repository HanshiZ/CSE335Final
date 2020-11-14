#pragma once

#include <memory>
#include <string>
#include <random>

class CTriangleMesh;

// CChildView window
/**
 * Main view window.
 */
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);

private:
	/// The mesh we are currently displaying
	std::shared_ptr<CTriangleMesh> mMesh;

	void SafeInvalidate();

	/// True if window has not yet been drawn
	bool mNotDrawnYet = true;
	
	/// True if we fill with random colors
	bool mRandomColors = false;

	/// The type of filling
	enum class FillType {Lines, Filled };

	/// Current filling type
	FillType mFillType = FillType::Lines;

	void MeshFile(const std::wstring& name);
	void NoMeshFile();
	void SetMesh();

	/// The currently loaded mesh OBJ file
	std::wstring mMeshFile;

	/// Random number generator
	std::mt19937 mRandom;

public:
	afx_msg void OnExamplesEmpty();
	afx_msg void OnExamples1triangle();
	afx_msg void OnExamples1filledtriangle();
	afx_msg void OnExamplesBox();
	afx_msg void OnExamples3triangles();

	/// \cond
	afx_msg void OnMeshesM();
	afx_msg void OnMeshesMsu();
	afx_msg void OnMeshesLines();
	afx_msg void OnUpdateMeshesLines(CCmdUI* pCmdUI);
	afx_msg void OnMeshesFilled();
	afx_msg void OnMeshesRandomcolors();
	afx_msg void OnUpdateMeshesRandomcolors(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMeshesFilled(CCmdUI* pCmdUI);
	afx_msg void OnMeshesMichigan();
	/// \endcond
};


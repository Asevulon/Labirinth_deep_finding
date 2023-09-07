#pragma once
#include <afxwin.h>
#include"Labirinth.h"
#include<gdiplus.h>
using namespace Gdiplus;

#define CLEN 50
#define BLEN 48
#define IMG_SIZE 5000.
class Drawer :
    public CStatic
{
public:
    virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
    ULONG_PTR token;
    GdiplusStartupInput si;
    Drawer();
    link start;
    void Save();

    float xPadding;
    float yPadding;
    bool hold;
    inline bool IsViewable(PointF p, PointF& v1, PointF& v2, PointF& addon, Matrix& m, bool&br);
    bool Drawer::IsVLineViewable(PointF p, PointF& v1, PointF& v2, PointF& addon, Matrix& m, bool& br);
    bool Drawer::IsHLineViewable(PointF p, PointF& v1, PointF& v2, PointF& addon, Matrix& m, bool& br);

    int len;
    int heigh;
    int X;
    int Y;
    int x, y;
    int bx, by;
    double scalex, scaley;
    DECLARE_MESSAGE_MAP()
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);

    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

};


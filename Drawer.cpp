#include "pch.h"
#include "Drawer.h"

Drawer::Drawer()
{
	GdiplusStartup(&token, &si, NULL);
	len = 0;
	heigh = 0;
	scalex = 1;
	scaley = 1;
	X = 0;
	Y = 0;
	hold = 0;
}
void Drawer::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Bitmap bm(lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top);
	Graphics gr(&bm);
	gr.Clear(Color::White);
	Graphics RealDrawer(lpDrawItemStruct->hDC);
	//gr.SetSmoothingMode(SmoothingModeAntiAlias);
	if (len == 0 || heigh == 0)
	{
		RealDrawer.DrawImage(&bm, 0, 0);
		return;
	}
	
	link rb = start;
	link pos = start;
	Matrix matr;
	matr.Translate(X, Y);
	matr.Scale(scalex, scaley);
	gr.SetTransform(&matr);
	
	Pen BackGroundPen(Color(0, 0, 0), 2.0F);
	Pen WhitePen(Color::White, 2.0F);
	SolidBrush sb(Color(240, 230, 140));
	gr.FillRectangle(&sb, 0, 0, CLEN, CLEN);
	sb.SetColor(Color(128, 128, 0));
	gr.FillRectangle(&sb, (len - 1) * CLEN, (heigh - 1) * CLEN, CLEN, CLEN);

	PointF v1, v2, addon;
	v1.X = 0;
	v1.Y = 0;
	v2.X = v1.X + lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left;
	v2.Y = v1.Y + lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top;
	addon.X = CLEN *scalex;
	addon.Y = CLEN*scaley;
	//matr.TransformPoints(&v1);
	//matr.TransformPoints(&v2);
	bool br = false;

	for (int i = 0; i < len; i++)
	{
		int x = i * CLEN;
		if (!IsViewable(PointF(x,0), v1, v2, addon, matr, br))
		{
			if (br)
			{
				br = false;
				break;
			}
			pos = pos->r;
			continue;
		}
		if (pos->c == none)
		{
			pos = pos->r;
			continue;
		}
		Color c;
		if (pos->c == yellow)c.SetValue(Color::Yellow);
		if (pos->c == green)c.SetValue(Color::Green);
		sb.SetColor(c);
		gr.FillRectangle(&sb, i * CLEN, 0, CLEN, CLEN);
		pos = pos->r;
	}
	for (int j = 1; j < heigh; j++)
	{
		rb = rb->b;
		pos = rb;
		for (int i = 0; i < len; i++)
		{
			int x = i * CLEN;
			int y = j * CLEN;
			if (!IsViewable(PointF(x, y), v1, v2, addon, matr, br))
			{
				if (br)
				{
					br = false;
					break;
				}
				pos = pos->r;
				continue;
			}
			if (pos->c == none)
			{
				pos = pos->r;
				continue;
			}
			Color c;
			if (pos->c == yellow)c.SetValue(Color::Yellow);
			if (pos->c == green)c.SetValue(Color::Green);
			sb.SetColor(c);
			gr.FillRectangle(&sb, x, y, CLEN, CLEN);
			pos = pos->r;
		}
	}

	sb.SetColor(Color(240, 230, 140));
	gr.FillRectangle(&sb, 0, 0, CLEN, CLEN);
	sb.SetColor(Color(128, 128, 0));
	gr.FillRectangle(&sb, (len - 1) * CLEN, (heigh - 1) * CLEN, CLEN, CLEN);

	for (int i = 0; i <= heigh; i++)
	{
		int x = i * CLEN;
		if (!IsHLineViewable(PointF(0, x), v1, v2, addon, matr, br))
		{
			if (br)
			{
				br = false;
				break;
			}
			continue;
		}
		gr.DrawLine(&BackGroundPen, 0, i * CLEN, len * CLEN, i * CLEN);
	}
	for (int i = 0; i <= len; i++)
	{
		int x = i * CLEN;
		if (!IsVLineViewable(PointF(x, 0), v1, v2, addon, matr, br))
		{
			if (br)
			{
				br = false;
				break;
			}
			continue;
		}
		gr.DrawLine(&BackGroundPen, i*CLEN, 0, i * CLEN, heigh * CLEN);
	}


	pos = start;
	rb = start;
	for (int i = 0; i < len; i++)
	{
		int x = i * CLEN;
		if (!IsViewable(PointF(x, 0), v1, v2, addon, matr, br))
		{
			if (br)
			{
				br = false;
				break;
			}
			pos = pos->r;
			continue;
		}
		if (pos->in == top)
		{
			gr.DrawLine(&WhitePen, i * CLEN + 1, 0, i * CLEN + BLEN, 0);
		}
		else if (pos->in == bot)gr.DrawLine(&WhitePen, i * CLEN + 1, CLEN, i * CLEN  + BLEN + 1, CLEN);
		else if (pos->in == left)gr.DrawLine(&WhitePen, i * CLEN, 1, i * CLEN, 1 + BLEN);
		else if (pos->in == right)gr.DrawLine(&WhitePen, (i + 1) * CLEN, 1, (i + 1) * CLEN, 1 + BLEN);
		pos = pos->r;
	}
	for (int j = 1; j < heigh; j++)
	{
		rb = rb->b;
		pos = rb;
		for (int i = 0; i < len; i++)
		{
			int x = i * CLEN;
			int y = j * CLEN;
			if (!IsViewable(PointF(x, y), v1, v2, addon, matr, br))
			{
				if (br)
				{
					br = false;
					break;
				}
				pos = pos->r;
				continue;
			}
			if (pos->in == top)gr.DrawLine(&WhitePen, i * CLEN + 1, j * CLEN, i * CLEN + BLEN + 1, j * CLEN);
			else if (pos->in == bot)gr.DrawLine(&WhitePen, i * CLEN + 1, (j + 1) * CLEN, i * CLEN + BLEN + 1, (j + 1) * CLEN);
			else if (pos->in == left)gr.DrawLine(&WhitePen, i * CLEN, j * CLEN + 1, i * CLEN, j * CLEN + BLEN + 1);
			else if (pos->in == right)gr.DrawLine(&WhitePen, (i + 1) * CLEN, j * CLEN + 1, (i + 1) * CLEN, j * CLEN + BLEN + 1);
			pos = pos->r;
		}
	}

	RealDrawer.DrawImage(&bm, 0, 0);

}
BEGIN_MESSAGE_MAP(Drawer, CStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


void Drawer::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	SetCapture();
	bx = X;
	by = Y;
	x = point.x;
	y = point.y;
	hold = 1;
	CStatic::OnLButtonDown(nFlags, point);
}


void Drawer::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	ReleaseCapture();
	hold = 0;
	
	CStatic::OnLButtonUp(nFlags, point);
}


void Drawer::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (hold)
	{
		X = point.x - x + bx;
		Y = point.y - y + by;
		Invalidate();
	}
	CStatic::OnMouseMove(nFlags, point);
}


BOOL Drawer::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (zDelta > 0)
	{
		scalex *= 1 + double(zDelta)/(1 + zDelta);
		scaley *= 1 + double(zDelta) / (1 + zDelta);
	}
	else
	{
		zDelta *= -1;
		scalex /= 1 + double(zDelta) / (1 + zDelta);
		scaley /= 1 + double(zDelta) / (1 + zDelta);
	}
	Invalidate();
	return CStatic::OnMouseWheel(nFlags, zDelta, pt);
}


void Drawer::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	scalex = 15. / min(len, heigh);;
	scaley = scalex;
	X = 0;
	Y = 0;
	bx = X;
	by = Y;
	Invalidate();
	CStatic::OnLButtonDblClk(nFlags, point);
}


void Drawer::Save()
{
	Bitmap bm(IMG_SIZE, IMG_SIZE);
	Graphics gr(&bm);
	gr.Clear(Color::White);
	if (len == 0 || heigh == 0)
	{
		return;
	}

	link rb = start;
	link pos = start;
	
	Matrix matr;
	matr.Scale(IMG_SIZE / (CLEN * max(len, heigh)), IMG_SIZE / (CLEN * max(len, heigh)));
	gr.SetTransform(&matr);

	Pen BackGroundPen(Color(0, 0, 0), 2.0F);
	Pen WhitePen(Color::White, 2.0F);
	SolidBrush sb(Color(240, 230, 140));
	gr.FillRectangle(&sb, 0, 0, CLEN, CLEN);
	sb.SetColor(Color(128, 128, 0));
	gr.FillRectangle(&sb, (len - 1) * CLEN, (heigh - 1) * CLEN, CLEN, CLEN);

	for (int i = 0; i <= heigh; i++)
	{
		gr.DrawLine(&BackGroundPen, 0, i * CLEN, len * CLEN, i * CLEN);
	}
	for (int i = 0; i <= len; i++)
	{
		gr.DrawLine(&BackGroundPen, i * CLEN, 0, i * CLEN, heigh * CLEN);
	}

	for (int i = 0; i < len; i++)
	{
		if (pos->in == top)
		{
			gr.DrawLine(&WhitePen, i * CLEN + 1, 0, i * CLEN + BLEN, 0);
		}
		else if (pos->in == bot)gr.DrawLine(&WhitePen, i * CLEN + 1, CLEN, i * CLEN + BLEN + 1, CLEN);
		else if (pos->in == left)gr.DrawLine(&WhitePen, i * CLEN, 1, i * CLEN, 1 + BLEN);
		else if (pos->in == right)gr.DrawLine(&WhitePen, (i + 1) * CLEN, 1, (i + 1) * CLEN, 1 + BLEN);
		pos = pos->r;
	}
	for (int j = 1; j < heigh; j++)
	{
		rb = rb->b;
		pos = rb;
		for (int i = 0; i < len; i++)
		{
			if (pos->in == top)gr.DrawLine(&WhitePen, i * CLEN + 1, j * CLEN, i * CLEN + BLEN + 1, j * CLEN);
			else if (pos->in == bot)gr.DrawLine(&WhitePen, i * CLEN + 1, (j + 1) * CLEN, i * CLEN + BLEN + 1, (j + 1) * CLEN);
			else if (pos->in == left)gr.DrawLine(&WhitePen, i * CLEN, j * CLEN + 1, i * CLEN, j * CLEN + BLEN + 1);
			else if (pos->in == right)gr.DrawLine(&WhitePen, (i + 1) * CLEN, j * CLEN + 1, (i + 1) * CLEN, j * CLEN + BLEN + 1);
			pos = pos->r;
		}
	}
	Status s;
	UINT num(0), size(0);
	s = GetImageEncodersSize(&num, &size);
	ImageCodecInfo* info = (ImageCodecInfo*)(malloc(size));

	s = GetImageEncoders(num, size, info);
	auto bmpcdlid = info->Clsid;

	s = bm.Save(L"output.bmp", &bmpcdlid);
	
	free(info);
}




bool Drawer::IsViewable(PointF p, PointF& v1, PointF& v2, PointF& addon, Matrix& m, bool& br)
{
	m.TransformPoints(&p);
	
	if (p.X < v1.X - addon.X)return false;
	if (p.X > v2.X + addon.X)
	{
		br = true;
		return false;
	}
	if (p.Y < v1.Y - addon.Y)return false;
	if (p.Y > v2.Y + addon.Y)
	{
		br = true;
		return false;
	}
	return true;
}
bool Drawer::IsVLineViewable(PointF p, PointF& v1, PointF& v2, PointF& addon, Matrix& m, bool& br)
{
	m.TransformPoints(&p);
	if (p.X < v1.X - addon.X)return false;
	if (p.X > v2.X + addon.X)
	{
		br = true;
		return false;
	}
	return true;
}
bool Drawer::IsHLineViewable(PointF p, PointF& v1, PointF& v2, PointF& addon, Matrix& m, bool& br)
{
	m.TransformPoints(&p);
	if (p.Y < v1.Y - addon.Y)return false;
	if (p.Y > v2.Y + addon.Y)
	{
		br = true;
		return false;
	}
	return true;
}
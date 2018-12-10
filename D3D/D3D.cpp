#include "D3D.h"

CD3DRender::CD3DRender()
{
	m_emaRenderer = new EMARenderer;
}

CD3DRender::~CD3DRender()
{}

struct Vertex
{
	D3DXVECTOR3  p;
	D3DXVECTOR3  n;
	float u, v;

	enum FVF
	{
		FVF_Flags = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1
	};
};

HRESULT CD3DRender::init(HWND hwnd, int Width, int Height)
{
	// Create the D3D object.
	if (NULL == (g_D3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;
	
	g_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.BackBufferWidth = Width;
	d3dpp.BackBufferHeight = Height;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;

	// Create the D3DDevice
	if (FAILED(g_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
									D3DCREATE_SOFTWARE_VERTEXPROCESSING,
									&d3dpp, &g_d3dDevice)))
	{
		return E_FAIL;
	}

	g_d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_d3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(45.0f),
		(float)Width / (float)Height, 0.1f, 100.0f);
	g_d3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);



	return S_OK;
}

// Функция предварительного создания буферов.
HRESULT CD3DRender::CreateBuffers(ushort EMGcount)
{
	g_pIndexBuffer = new LPDIRECT3DINDEXBUFFER9*[EMGcount];
	g_pVertexBuffer = new LPDIRECT3DVERTEXBUFFER9[EMGcount];

	CD3DRender::EMGcount = EMGcount;
	EMGsubmodels = new ushort[EMGcount];

	IndexCount = new ushort*[EMGcount];
	VertexCount = new ushort[EMGcount];
	VertexSize = new ushort[EMGcount];

	DDSid = new Byte*[EMGcount];

	return S_OK;
}

// Функция заполнения массива буферов.
HRESULT CD3DRender::LoadEMG(ushort CurrentEMG, ushort EMGsubmodels, Byte* DDSid, ushort* IndexCount,
	ushort VertexCount, ushort VertexSize, ushort** IndiceArray, Byte* VertexArray)
{
	// Заполнение массивов для использования в ProcessFrame().
	CD3DRender::IndexCount[CurrentEMG] = new ushort[EMGsubmodels];
	CD3DRender::VertexCount[CurrentEMG] = VertexCount;
	CD3DRender::VertexSize[CurrentEMG] = VertexSize;
	CD3DRender::EMGsubmodels[CurrentEMG] = EMGsubmodels;

	CD3DRender::DDSid[CurrentEMG] = new Byte[EMGsubmodels];

	g_pIndexBuffer[CurrentEMG] = new LPDIRECT3DINDEXBUFFER9[EMGsubmodels];

	for (ushort i = 0; i < EMGsubmodels; i++)
	{
		CD3DRender::IndexCount[CurrentEMG][i] = IndexCount[i];
		CD3DRender::DDSid[CurrentEMG][i] = DDSid[i];

		// Create an index buffer to use with our indexed vertex buffer...
		g_d3dDevice->CreateIndexBuffer(IndexCount[i] * sizeof(WORD),
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&(g_pIndexBuffer[CurrentEMG][i]),
			NULL);
		WORD *pIndices = NULL;

		g_pIndexBuffer[CurrentEMG][i]->Lock(0, IndexCount[i] * sizeof(WORD), (void**)&pIndices, 0);
		memcpy(pIndices, IndiceArray[i], IndexCount[i] * sizeof(WORD));
		g_pIndexBuffer[CurrentEMG][i]->Unlock();
	}

	// Create a vertex buffer...
	g_d3dDevice->CreateVertexBuffer(VertexCount * VertexSize,
		D3DUSAGE_WRITEONLY,
		Vertex::FVF_Flags,
		D3DPOOL_MANAGED,
		&(g_pVertexBuffer[CurrentEMG]),
		NULL);
	void *pVertices = NULL;

	g_pVertexBuffer[CurrentEMG]->Lock(0, VertexCount * VertexSize, (void**)&pVertices, 0);
	memcpy(pVertices, VertexArray, VertexCount * VertexSize);
	g_pVertexBuffer[CurrentEMG]->Unlock();

	return S_OK;
}

HRESULT CD3DRender::LoadDDS(ushort DDScount, unsigned long* DDSsize, Byte** DDScontent)
{
	g_Texture = new LPDIRECT3DTEXTURE9[DDScount];
	CD3DRender::DDScount = DDScount;
	for (ushort i = 0; i < DDScount; i++)
		D3DXCreateTextureFromFileInMemory(g_d3dDevice, DDScontent[i], DDSsize[i], &g_Texture[i]);


	return S_OK;
}

HRESULT CD3DRender::Shutdown()
{
	for (ushort i = 0; i < EMGcount; i++)
	{
		for (ushort a = 0; a < EMGsubmodels[i]; a++)
		{
			if (g_pIndexBuffer != NULL)
				g_pIndexBuffer[i][a]->Release();
		}		

		if (g_pVertexBuffer != NULL)
			g_pVertexBuffer[i]->Release();
	}	

	for (ushort i = 0; i < DDScount; i++)
	{
		if (g_Texture != NULL)
			g_Texture[i]->Release();
	}	

    if( g_d3dDevice != NULL )
        g_d3dDevice->Release();

    if( g_D3D != NULL )
        g_D3D->Release();	

	return S_OK;
}

HRESULT CD3DRender::OnMouseMove(short x, short y, bool RMousing)
{
	ptCurrentMousePosit.x = x;
	ptCurrentMousePosit.y = y;

	if (bMousing)
	{
		if (bRMousing != RMousing)
		{
			m_zoom += (ptCurrentMousePosit.y - ptLastMousePosit.y) / (float)1000;
		}
		else
		{
			g_fSpinX -= (ptCurrentMousePosit.x - ptLastMousePosit.x);
			g_fSpinY -= (ptCurrentMousePosit.y - ptLastMousePosit.y);
		}		
	}

	ptLastMousePosit.x = ptCurrentMousePosit.x;
	ptLastMousePosit.y = ptCurrentMousePosit.y;

	return S_OK;
}

HRESULT CD3DRender::OnMouseButtonUp()
{
	bMousing = false;
	bRMousing = false;

	return S_OK;
}

HRESULT CD3DRender::OnMouseButtonDown(short x, short y)
{
	ptLastMousePosit.x = ptCurrentMousePosit.x = x;
	ptLastMousePosit.y = ptCurrentMousePosit.y = y;
	bMousing = true;
	bRMousing = false;

	return S_OK;
}

HRESULT CD3DRender::Reset()
{
	return S_OK;
}

HRESULT CD3DRender::ProcessFrame()
{
	// Clear the backbuffer and the zbuffer
	g_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
						D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	D3DXMATRIX matTrans;
	D3DXMATRIX matRot;
	D3DXMATRIX matWorld;

	D3DXMatrixTranslation(&matTrans, 0.0f, 0.0f, m_zoom);

	D3DXMatrixRotationYawPitchRoll(	&matRot,
									D3DXToRadian(g_fSpinX),
									D3DXToRadian(g_fSpinY),
									0.0f);
	matWorld = matRot * matTrans;
	g_d3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	// Begin the scene
	if (SUCCEEDED(g_d3dDevice->BeginScene()))
	{
		if (g_pIndexBuffer != 0 && g_pVertexBuffer != 0)
		{
			for (int i = 0; i < EMGcount; i++)
			{
				g_d3dDevice->SetStreamSource(0, g_pVertexBuffer[i], 0, VertexSize[i]);
				g_d3dDevice->SetFVF(Vertex::FVF_Flags);				
				
				for (ushort a = 0; a < EMGsubmodels[i]; a++)
				{
					if (g_Texture != NULL)
					{
						g_d3dDevice->SetTexture(0, g_Texture[DDSid[i][a]]);

						g_d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
						g_d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
						g_d3dDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 4);

					}

					g_d3dDevice->SetIndices(g_pIndexBuffer[i][a]);
					g_d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, VertexCount[i], 0, IndexCount[i][a] - 2);		
				}
			}
		}
		// End the scene
		g_d3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	g_d3dDevice->Present(NULL, NULL, NULL, NULL);

	return S_OK;
}

HRESULT CD3DRender::Resize(int Width, int Height)
{
	d3dpp.BackBufferWidth = Width;
	d3dpp.BackBufferHeight = Height;

	g_d3dDevice->Reset(&d3dpp);

	g_d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_d3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(45.0f),
		(float)Width / (float)Height, 0.1f, 100.0f);
	g_d3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	return S_OK;
}


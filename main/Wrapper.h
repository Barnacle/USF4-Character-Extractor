#pragma once

#include "../D3D/D3D.h"

class CD3DRender;

public ref class Wrapper
{
public:
	Wrapper();
	~Wrapper();

	HRESULT WrapInit(int hWnd, int width, int height);
	HRESULT WrapClose();
	HRESULT WrapRender();
	HRESULT	WrapResize(int width, int height);
	HRESULT	WrapOnMouseButtonUp();
	HRESULT	WrapOnMouseMove(short x, short y, bool RMousing);
	HRESULT	WrapOnMouseButtonDown(short x, short y);
	HRESULT WrapCreateBuffers(ushort EMGcount);
	HRESULT	WrapLoadEMG(ushort CurrentEMG, ushort EMGsubmodels, unsigned char* DDSid, ushort* IndexCount,
		ushort VertexCount, ushort VertexSize,
		ushort** IndiceArray, unsigned char* VertexArray);
	HRESULT WrapLoadDDS(ushort DDScount, unsigned long* DDSsize, unsigned char** DDScontent);

	HRESULT WrapSetup(System::String^ emaFileName, unsigned long emaBlockOffset);
	HRESULT WrapUpdate(float(&structure)[500][6], std::string(&names)[500], System::String^ AnimationName, int frame);

	std::string managedStrToNative(System::String^ sysstr)
	{
		using System::IntPtr;
		using System::Runtime::InteropServices::Marshal;

		auto ip = Marshal::StringToHGlobalAnsi(sysstr);
		std::string outString = static_cast<const char*>(ip.ToPointer());
		Marshal::FreeHGlobal(ip);
		return outString;
	}

protected:
	CD3DRender* m_pRenderer;
};

inline Wrapper::Wrapper()
{
	m_pRenderer = new CD3DRender;
}

inline Wrapper::~Wrapper()
{
	delete m_pRenderer;
}

inline HRESULT Wrapper::WrapInit(int hWnd, int width, int height)
{
	return m_pRenderer->init(HWND(hWnd), width, height);
}

inline HRESULT Wrapper::WrapClose()
{
	return m_pRenderer->Shutdown();
}

inline HRESULT Wrapper::WrapRender()
{
	return m_pRenderer->ProcessFrame();
}

inline HRESULT Wrapper::WrapResize(int width, int height)
{
	return m_pRenderer->Resize(width, height);
}

inline HRESULT Wrapper::WrapOnMouseButtonUp()
{
	return m_pRenderer->OnMouseButtonUp();
}

inline HRESULT Wrapper::WrapOnMouseMove(short x, short y, bool RMousing)
{
	return m_pRenderer->OnMouseMove(x, y, RMousing);
}

inline HRESULT Wrapper::WrapOnMouseButtonDown(short x, short y)
{
	return m_pRenderer->OnMouseButtonDown(x, y);
}

inline HRESULT Wrapper::WrapCreateBuffers(ushort EMGcount)
{
	return m_pRenderer->CreateBuffers(EMGcount);
}

inline HRESULT Wrapper::WrapLoadEMG(ushort CurrentEMG, ushort EMGsubmodels, unsigned char* DDSid, ushort* IndexCount, ushort VertexSize, ushort VerteSize, ushort** IndiceArray, unsigned char* VertexArray)
{
	return m_pRenderer->LoadEMG(CurrentEMG, EMGsubmodels, DDSid, IndexCount, VertexSize, VerteSize, IndiceArray, VertexArray);
}

inline HRESULT Wrapper::WrapLoadDDS(ushort DDScount, unsigned long* DDSsize, unsigned char** DDScontent)
{
	return m_pRenderer->LoadDDS(DDScount, DDSsize, DDScontent);
}

inline HRESULT Wrapper::WrapSetup(System::String^ emaFileName, unsigned long emaBlockOffset)
{
	const auto emaFileName1 = managedStrToNative(emaFileName);
	return m_pRenderer->Setup(emaFileName1, emaBlockOffset);
}

inline HRESULT Wrapper::WrapUpdate(float(&structure)[500][6], std::string(&names)[500], System::String^ AnimationName, int frame)
{
	const auto AnimationName1 = managedStrToNative(AnimationName);
	return m_pRenderer->Update(structure, names, AnimationName1, frame);
}

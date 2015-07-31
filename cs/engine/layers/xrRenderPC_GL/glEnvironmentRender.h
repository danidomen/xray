#pragma once

#include "..\..\include\xrRender\EnvironmentRender.h"

#include "..\xrRender\blenders\blender.h"
class CBlender_skybox :
	public IBlender
{
public:
	virtual		LPCSTR		getComment()	{ return "INTERNAL: combiner"; }
	virtual		BOOL		canBeDetailed()	{ return FALSE; }
	virtual		BOOL		canBeLMAPped()	{ return FALSE; }

	virtual		void		Compile(CBlender_Compile& C)
	{
		VERIFY(!"CBlender_skybox::Compile not implemented");
	}
};

class glEnvDescriptorRender : public IEnvDescriptorRender
{
	friend class glEnvDescriptorMixerRender;
public:
	virtual void OnDeviceCreate(CEnvDescriptor &owner);
	virtual void OnDeviceDestroy();

	virtual void Copy(IEnvDescriptorRender &_in);
private:
	ref_texture			sky_texture;
	ref_texture			sky_texture_env;
	ref_texture			clouds_texture;
};

class glEnvDescriptorMixerRender : public IEnvDescriptorMixerRender
{
public:
	virtual void Copy(IEnvDescriptorMixerRender &_in);

	virtual void Destroy();
	virtual void Clear();
	virtual void lerp(IEnvDescriptorRender *inA, IEnvDescriptorRender *inB);
	//private:
public:
	STextureList		sky_r_textures;
	STextureList		sky_r_textures_env;
	STextureList		clouds_r_textures;
};

class glEnvironmentRender :
	public IEnvironmentRender
{
public:
	glEnvironmentRender();

	virtual void Copy(IEnvironmentRender &_in);

	virtual void OnFrame(CEnvironment &env);
	virtual void OnLoad();
	virtual void OnUnload();
	virtual void RenderSky(CEnvironment &env);
	virtual void RenderClouds(CEnvironment &env);
	virtual void OnDeviceCreate();
	virtual void OnDeviceDestroy();
	virtual particles_systems::library_interface const& particles_systems_library();

private:
	CBlender_skybox			m_b_skybox;

	ref_shader				sh_2sky;
	ref_geom				sh_2geom;

	ref_shader				clouds_sh;
	ref_geom				clouds_geom;

	ref_texture				tonemap;
	ref_texture				tsky0, tsky1;
};
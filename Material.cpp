/**
 * Material.cpp
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#pragma region Prerequisites

#include "Material.h"

using namespace EUMD_FlightSimulator::Components;

#pragma endregion

#pragma region Definitions

/* Ctor, Dtor */

Material::Material(const Vec4& ambient, const Vec4& diffuse, const Vec4& specular, 
	float shine, float refraction, MATERIAL_USAGE usage) :
	m_shineFactor(shine),
	m_ambientColor(ambient),
	m_diffuseColor(diffuse),
	m_specularColor(specular),
	m_refractionIndex(refraction),
	m_usage(usage) { ; }

Material::Material(const Vec4& specular, const Vec4& diffuse, const Vec4& ambient, 
	float shine, float refraction) :
	m_shineFactor(shine),
	m_ambientColor(ambient),
	m_diffuseColor(diffuse),
	m_specularColor(specular),
	m_refractionIndex(refraction),
	m_usage(MATERIAL_USAGE::UNTEXTURED) { ; }

Material::Material(const Vec4& diffuse, const Vec4& ambient) :
	m_shineFactor(.0f),
	m_ambientColor(ambient),
	m_diffuseColor(diffuse),
	m_specularColor(Vec4(.0f)),
	m_refractionIndex(RI_VACUUM),
	m_usage(MATERIAL_USAGE::UNTEXTURED) { ; }

Material::Material(MATERIAL_USAGE usage) :
	m_shineFactor(5.0f),
	m_ambientColor(Vec4(1.0f)),
	m_diffuseColor(Vec4(1.0f)),
	m_specularColor(Vec4(1.0f)),
	m_refractionIndex(RI_VACUUM),
	m_usage(usage) { ; }

Material::Material() : 
	m_shineFactor(.0f), 
	m_ambientColor(Vec4(1.0f)),
	m_diffuseColor(Vec4(.0f)),
	m_specularColor(Vec4(.0f)),
	m_refractionIndex(RI_VACUUM),
	m_usage(MATERIAL_USAGE::UNUSED) { ; }

Material::~Material() { ; }

/* Functions */

void Material::clean() { ; }

#pragma endregion

// END OF FILE
/**
 * Material.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#pragma once

#pragma region Prerequisites

#include "Component.h"

using namespace EUMD_FlightSimulator;

#pragma endregion

#pragma region Constants

/* Refractive Indices */

#define RI_VACUUM 1.0
#define RI_AIR 1.000277
#define RI_CARBON_DIOXIDE 1.00045
#define RI_HELIUM 1.000036
#define RI_HYDROGEN 1.000132
#define RI_ARSENIC 1.9
#define RI_BENZENE 1.501
#define RI_CARBON_DISULIFIDE 1.628
#define RI_CARBON_TETRACHLORIDE 1.461
#define RI_ETHANOL 1.361
#define RI_WATER 1.333
#define RI_TITANIUM_DIOXIDE 2.614
#define RI_DIAMOND 2.419
#define RI_STRONTIUM_TITANATE 2.41
#define RI_AMBER 1.55
#define RI_FUSED_SILICA 1.458
#define RI_SODIUM_CHLORIDE 1.544
#define RI_LIQUID_HELIUM 1.025
#define RI_ICE 1.31
#define RI_CORNEA 1.401
#define RI_LENS 1.406
#define RI_ACETONE 1.36
#define RI_GLYCEROL 1.4729
#define RI_BROMINE 1.661
#define RI_TEFLON 1.35
#define RI_JOHN_GOTTI RI_TEFLON
#define RI_CYTOP 1.34
#define RI_POLYDIMETHYLSILOXANE 1.4118
#define RI_PLA 1.46
#define RI_ACRYLIC_GLASS 1.491
#define RI_POLYCARBONATE 1.6
#define RI_PMMA 1.4899
#define RI_PETG 1.57
#define RI_PET 1.575
#define RI_KEROSENE 1.39
#define RI_CROWN_GLASS_PURE 1.54
#define RI_FLINT_GLASS_PURE 1.62
#define RI_CROWN_GLASS_IMPURE 1.755
#define RI_FLINT_GLASS_IMPURE 1.925
#define RI_PYREX 1.47
#define RI_CRYOLITE 1.338
#define RI_ROCK_SALT 1.516
#define RI_SAPPHIRE 1.778
#define RI_CUBIC_ZIRCONIA 2.18
#define RI_POTASSIUM_NIOBATE 2.28
#define RI_SILICON_CARBIDE 2.69
#define RI_CINNABAR 3.02
#define RI_GALLIUM_PHOSPHIDE 3.5
#define RI_GALLIUM_ARSENIDE 3.927
#define RI_ZINC_OXIDE 2.4
#define RI_GERMANIUM 4.05
#define RI_SILICON 3.48
#define RI_SUGAR_SOLUTION_25 1.3723
#define RI_SUGAR_SOLUTION_50 1.42
#define RI_SUGAR_SOLUTION_75 1.4774

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Components {

		enum MATERIAL_USAGE {
			UNUSED = 0,
			STORAGE,
			UNTEXTURED,
			TEXTURED
		};

		class Material;

		typedef std::tr1::shared_ptr<Material> Material_sptr;

		class Material : public Component {

			public:

				/* Ctor, Dtor */

				Material(const Vec4& ambient, const Vec4& diffuse, const Vec4& specular, 
					float shine, float refraction, MATERIAL_USAGE usage);
				Material(const Vec4& specular, const Vec4& diffuse, const Vec4& ambient, 
					float shine, float refraction);
				Material(const Vec4& diffuse, const Vec4& ambient);
				Material(MATERIAL_USAGE usage);
				Material();
				~Material();

				/* Accessors */

				inline const Vec4& getDiffuseColor() const { return m_diffuseColor; }
				inline const Vec4& getSpecularColor() const { return m_specularColor; }
				inline const Vec4& getAmbientColor() const { return m_ambientColor; }
				inline const float& getShineFactor() const { return m_shineFactor; }
				inline const float& getRefractionIndex() const { return m_refractionIndex; }
				inline MATERIAL_USAGE getMaterialUsage() { return m_usage; }

				/* Modifiers */

				inline void setDiffuseColor(const Vec4& v) { m_diffuseColor = v; }
				inline void setSpecularColor(const Vec4& v) { m_specularColor = v; }
				inline void setAmbientcolor(const Vec4& v) { m_ambientColor = v; }
				inline void setShineFactor(const float& f) { m_shineFactor = f; }
				inline void setRefractionIndex(const float& f) { m_refractionIndex = f; }
				inline void setMaterialUsage(MATERIAL_USAGE usage) { m_usage = usage; }

				/* Implementations */

				inline const std::string getType(TypeInfo typeInfo_ex = DEFAULT_TYPE_INFO) override {
					return (typeInfo_ex) ? (Component::getType() + ".Material") : "Material"; }
				void clean() override;

			private:

				/* Members */

				Vec4 m_diffuseColor, m_specularColor, m_ambientColor;
				float m_shineFactor, m_refractionIndex;
				MATERIAL_USAGE m_usage;

				// @TODO: Add Texture member...
		};
	}
}

#pragma endregion

#endif /* !__MATERIAL_H__ */

// END OF FILE
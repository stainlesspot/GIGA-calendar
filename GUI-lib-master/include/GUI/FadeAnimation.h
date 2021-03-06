////////////////////////////////////////////////////////////
//
// GUI-lib - Graphical User Interface Library
// Copyright (C) 2014-2016 ShtGames (shtgamessts@gmail.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef GUI_FADE_ANIMATION
#define GUI_FADE_ANIMATION

#include <SFML/Graphics/Shader.hpp>

#include "Animation.h"

namespace gui
{
	class FadeAnimation : public Animation
	{
	public:
		FadeAnimation(const FadeAnimation& copy) = default;
		FadeAnimation(FadeAnimation&& temp) = default;
		FadeAnimation() = default;
		virtual ~FadeAnimation() = default;

		FadeAnimation& operator=(const FadeAnimation& copy) = default;
		FadeAnimation& operator=(FadeAnimation&& temp) = default;

		FadeAnimation& setDuration(const float duration)override;
		FadeAnimation& setFPS(const float fps)override;
		virtual FadeAnimation& setFadeDirection(const bool direction);

		const bool getFadeDirection()const;
		const float getFadeAmount()const;

		const sf::Shader& getShaderNonTextured()const;
		const sf::Shader& getShaderTextured()const;
		virtual void step()const override;

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	
	private:
		mutable float m_fadeAmount = 0.0f;
		mutable bool  m_fadeDirection = false;

		static const bool loadShader();

		static sf::Shader fadeShaderTextured, fadeShaderNoTexture;
		static const bool shaderLoadSuccessful;
	};
}

#endif
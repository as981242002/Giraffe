/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-19 18:48:37
**/

#ifndef _DIRECTIONAL_LIGHT_HPP_
#define _DIRECTIONAL_LIGHT_HPP_

#include "../math/constant.hpp"
#include "../core/light.hpp"

namespace Giraffe {

class DirectionalLight : public Light
{
	public:
		DirectionalLight(const Vector3d &direction, const Vector3d &intensity);

		Vector3d illuminate(const Isect &isect) const override;

		Vector3d computeLight(Isect &isect) const override;

	private:
		Vector3d direction_;
		Vector3d intensity_;
};

} // namespace Giraffe

#endif /* _DIRECTIONAL_LIGHT_HPP_ */
/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-03 20:16:46
**/

#ifndef _RAY_H_
#define _RAY_H_

#include <vector>
#include <limits>

#include "object.hpp"
#include "random.hpp"

class Ray
{
	public:
		Ray() = default;

		Ray(const Vec3 &origin, const Vec3 &dir):origin_(origin), dir_(dir) { }

		Vec trace(const std::vector<Object *> &, int);
		void intersect(const std::vector<Object *> &, Isect &);

		~Ray() { }

		Vec3 		origin_;
		Vec3 		dir_;
};

#endif /* _RAY_H_ */
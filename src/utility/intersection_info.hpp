/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-20 21:04:55
**/

#ifndef _INTERSECTION_INFO_HPP_
#define _INTERSECTION_INFO_HPP_

#include "../math/vector.hpp"
#include "../math/point.hpp"

namespace Giraffe {

class IntersectionInfo
{
	public:
		IntersectionInfo() = default;

		IntersectionInfo(const Point3d &position, const Point2d &uv, const Vector3d &normal)
		:position_(position), uv_(uv), normal_(normal) { }

		IntersectionInfo& operator=(const IntersectionInfo &that) {
			position_ = that.position_;
			uv_       = that.uv_;
			normal_   = that.normal_;
			return *this;
		}

		void setPosition(const Point3d &position) { position_ = position; }

		const Point3d& position() const { return position_; }
		const Vector3d& normal() const { return normal_; }
		const Point2d& uv() const { return uv_; }

	private:
		Point3d position_;
		Point2d uv_;
		Vector3d normal_;
};

} // namespace Giraffe

#endif /* _INTERSECTION_INFO_HPP_ */
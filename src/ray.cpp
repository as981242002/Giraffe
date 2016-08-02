/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-03 20:25:31
**/

#include "ray.hpp"

void Ray::intersect(const std::vector<Object *> &objects, Isect &isect)
{
	for (size_t i = 0, end = objects.size(); i != end; ++i)
		objects[i]->intersect(origin_, dir_, isect);
}

Vec Ray::trace(const std::vector<Object *> &objects, int depth)
{
	Isect isect;
	intersect(objects, isect);
	if (isect.miss()) return Vec();

	Object *obj = isect.obj_;
	Vec color(obj->color());
	double max = std::max(color.x_, std::max(color.y_, color.z_));
	if (++depth > 5) {
		if (Random() < max) color *= (1.0 / max);
		else return obj->emission();
	}

	Vec pos = origin_ + dir_ * isect.dis_;
	Vec normal = pos - obj->center();
	normalize(normal);
	Vec adjNormal(normal);

	bool into = true;
	if (dot(dir_, normal) > 0) adjNormal = -adjNormal, into = false;

	Vec reflPos = pos + adjNormal * kEpsilon;
	REFL mat = obj->refl();

	if (mat == kDiffuse) {
		Vec u, v, w(adjNormal);
		if (std::fabs(w.x_) > 0.1)
			u = cross(Vec(0, 1, 0), w);
		else
			u = cross(Vec(1, 0, 0), w);
		normalize(u);
		v = cross(w, u);
		normalize(v);
		double a = Random(), b = Random(), sini = std::sqrt(a), cosi = DOU_PI * b;
		Vec dir((sini*std::cos(cosi)*u) + (sini*std::sin(cosi)*v) + (std::sqrt(1-a)*w));
		normalize(dir);

		// Vec c;
		// for (int i = 0, end = objects.size(); i != end; ++i) {
		// 	if (!objects[i]->emit() || objects[i] == obj) continue;
		// 	Vec newDir(objects[i]->center() - obj->center());
		// 	normalize(newDir);
		// 	Object *obj;
		// 	if (!(obj = Ray(pos, newDir).intersect(objects, near)) || obj == objects[i])
		// 		c += objects[i]->emission() * color * std::max(0.0, dot(newDir, adjNormal));
		// }

		return obj->emission() + color * Ray(reflPos, dir).trace(objects, depth);
	}

	Vec refl = dir_ - 2 * dot(dir_, normal) * normal;
	normalize(refl);

	if (mat == kReflect)
		return obj->emission() + color * Ray(reflPos, refl).trace(objects, depth);

	double etai = 1.0, etat = kRefractionRatio;
	double ior;
	if (into) ior = 1.0 / kRefractionRatio;
	else 			ior = kRefractionRatio;

	double cos1 = -dot(dir_, adjNormal), cos2;
	if ((cos2 = (1 - ior * ior * (1.0 - cos1 * cos1))) < 0.0)
		return obj->emission() + color * Ray(reflPos, refl).trace(objects, depth);

	Vec refr(dir_ * ior + adjNormal * (ior * cos1 - std::sqrt(cos2)));
	Vec refrPos = pos - adjNormal * kEpsilon;
	normalize(refr);

	double a = etat - etai, b = etat + etai;
	double R0 = a * a / (b * b), c = 1 - (into ? cos1 : dot(refr, normal));
	double Re = R0 + (1 - R0) * c * c * c * c * c, Tr = 1 - Re;

	double P = 0.25 + 0.5 * Re, RP = Re / P, TP = Tr / (1 - P);
	return obj->emission() + color * (depth > 2 ? (Random() < P ?
		Ray(reflPos, refl).trace(objects, depth)*RP : Ray(refrPos, refr).trace(objects, depth)*TP):
		Ray(reflPos, refl).trace(objects, depth)*Re + Ray(refrPos, refr).trace(objects, depth)*Tr);
}

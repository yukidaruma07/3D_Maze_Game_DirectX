#pragma once
#include "BaseObject.h"
#include "Collider.h"

class CircleCollider : public BaseObject, public Collider {
private:
	BaseObject* parent_;
	int radius_;
public:
	CircleCollider(BaseObject* parent, int radius);
	~CircleCollider();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	int GetRadius() const { return radius_; }
	bool IsCircle(CircleCollider* circleCol);
};
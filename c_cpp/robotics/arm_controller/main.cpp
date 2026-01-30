#include <iostream>

int main()
{
	std::cout << "Hello, Robotics Arm Controller!" << std::endl;
	return 0;
}

class BaseJoint
{
public:
	BaseJoint(float initial_state, float min_state, float max_state, float max_velocity, Vector3 axis)
		: state_(initial_state),
		  min_state_(min_state),
		  max_state_(max_state),
		  velocity_(0.0f),
		  max_velocity_(max_velocity),
		  axis_(axis) {}

	float GetState() const
	{
		return state_;
	}

	void SetVelocity(float vel)
	{
		if (vel > max_velocity_)
			velocity_ = max_velocity_;
		else if (vel < -max_velocity_)
			velocity_ = -max_velocity_;
		else
			velocity_ = vel;
	}

	void UpdateState(float dt)
	{
		state_ += velocity_ * dt;
		if (state_ > max_state_)
			state_ = max_state_;
		else if (state_ < min_state_)
			state_ = min_state_;
	}

private:
	Vector3 axis_;
	float state_; // rad or m
	float min_state_;
	float max_state_;

	float velocity_; // rad/s or m/s
	float max_velocity_;
};

class RotationalJoint : public BaseJoint
{
};

class PrismaticJoint : public BaseJoint
{
};

struct Vector3
{
	float x_;
	float y_;
	float z_;
};

class Transform
{
public:
	Transform(const Vector3 &pos, const std::array<Vector3, 3> &rot)
		: position_(pos), rotation_(rot) {}

	Vector3 GetPosition() const
	{
		return position_;
	}

	std::array<Vector3, 3> GetRotation() const
	{
		return rotation_;
	}

	static Transform Compose(const Transform &a, const Transform &b)
	{
	}

	static Transform Inverse(const Transform &t)
	{
	}

	static Transform ApplyToVector(const Transform &t, const Vector3 &v)
	{
	}

	static Transform ApplyToPoint(const Transform &t, const Vector3 &p)
	{
	}

private:
	Vector3 position_;
	std::array<Vector3, 3> rotation_; // 3x3 rotation matrix
};

struct Link
{
	Vector3 relative_transform_;
};

class Articulation
{
public:
	Articulation(Link link_proximal, Link link_distal, std::unique_ptr<BaseJoint> joint)
		: link_proximal_(link_proximal), link_distal_(link_distal), joint_(std::move(joint)) {}

	Vector3 GetRelativeTransform() const
	{
	}

	void SetJointVelocity(float vel)
	{
		joint_->SetVelocity(vel);
	}

	void Update(float dt)
	{
		joint_->UpdateState(dt);
	}

private:
	Link link_proximal_;
	Link link_distal_;
	std::unique_ptr<BaseJoint> joint_;
};
#include "../physx_wrap.h"
#include "physx_wrap_impl.h"
#include "log.h"
#include <cassert>
#include <geometry/PxHeightField.h>
#include "scene_info_mgr.h"

#define DEFAULT_DENSITY (1.0f)

PhysxScene::PhysxScene()
    : mImpl(new PhysxSceneImpl())
{

}

PhysxScene::~PhysxScene() {
#ifdef _DEBUG
    INFO("call ~PhysxScene()");
#endif
    if (mImpl) {
        delete mImpl;
        mImpl = nullptr;
    }
}

bool PhysxScene::Init(float timestep) {
    return mImpl->Init(timestep, false, "", 0, 0, false);
}

bool PhysxScene::InitWithPVD(float timestep, const std::string &ip, unsigned port, unsigned timeout, bool useFullPvdConnection) {
    return mImpl->Init(timestep, true, ip, port, timeout, useFullPvdConnection);
}

void PhysxScene::CreateScene(const std::string &path) {
    mImpl->CreateScene(path);
}

void PhysxScene::release() {
    mImpl->release();
}

void  PhysxScene::Update() {
    mImpl->Update();
}

uint64_t PhysxScene::CreatePlane(float yAxis) {
    return (uint64_t)mImpl->CreatePlane(0, 1, 0, yAxis);
}

uint64_t PhysxScene::CreateHeightField(const std::vector<int16_t> &heightmap, unsigned columns, unsigned rows, const Vector3 &scale) {
    return (uint64_t)mImpl->CreateHeightField(heightmap, columns, rows, scale);
}

uint64_t PhysxScene::CreateBoxDynamic(const Vector3 &pos, const Vector3 &halfExtents) {
    return (uint64_t)mImpl->CreateBoxDynamic(pos, halfExtents, DEFAULT_DENSITY);
}

uint64_t PhysxScene::CreateBoxKinematic(const Vector3 &pos, const Vector3 &halfExtents) {
    return (uint64_t)mImpl->CreateBoxKinematic(pos, halfExtents, DEFAULT_DENSITY);
}

uint64_t PhysxScene::CreateBoxStatic(const Vector3 &pos, const Vector3 &halfExtents) {
    return (uint64_t)mImpl->CreateBoxStatic(pos, halfExtents);
}

uint64_t PhysxScene::CreateSphereDynamic(const Vector3 &pos, float radius) {
    return (uint64_t)mImpl->CreateSphereDynamic(pos, radius, DEFAULT_DENSITY);
}

uint64_t PhysxScene::CreateSphereKinematic(const Vector3 &pos, float radius) {
    return (uint64_t)mImpl->CreateSphereKinematic(pos, radius, DEFAULT_DENSITY);
}

uint64_t PhysxScene::CreateSphereStatic(const Vector3 &pos, float radius) {
    return (uint64_t)mImpl->CreateSphereStatic(pos, radius);
}

uint64_t PhysxScene::CreateCapsuleDynamic(const Vector3 &pos, float radius, float halfHeight) {
    return (uint64_t)mImpl->CreateCapsuleDynamic(pos, radius, halfHeight, DEFAULT_DENSITY);
}

uint64_t PhysxScene::CreateCapsuleKinematic(const Vector3 &pos, float radius, float halfHeight) {
    return (uint64_t)mImpl->CreateCapsuleKinematic(pos, radius, halfHeight, DEFAULT_DENSITY);
}

uint64_t PhysxScene::CreateCapsuleStatic(const Vector3 &pos, float radius, float halfHeight) {
    return (uint64_t)mImpl->CreateCapsuleStatic(pos, radius, halfHeight);
}

uint64_t PhysxScene::CreateMeshKinematic(const Vector3 &pos, const Vector3 &scale, const std::vector<float> &vb, const std::vector<uint16_t> &ib) {
    return (uint64_t)mImpl->CreateMeshKinematic(pos, scale, vb, ib, DEFAULT_DENSITY);
}

uint64_t PhysxScene::CreateMeshStatic(const Vector3 &pos, const Vector3 &scale, const std::vector<float> &vb, const std::vector<uint16_t> &ib) {
    return (uint64_t)mImpl->CreateMeshStatic(pos, scale, vb, ib);
}

void PhysxScene::SetLinearVelocity(uint64_t id, const Vector3 &velocity) {
    physx::PxRigidActor* actor = (physx::PxRigidActor*)id;
    mImpl->SetLinearVelocity(actor, velocity);
}

void PhysxScene::AddForce(uint64_t id, const Vector3 &force) {
    physx::PxRigidActor* actor = (physx::PxRigidActor*)id;
    mImpl->AddForce(actor, force);
}

void PhysxScene::ClearForce(uint64_t id) {
    physx::PxRigidActor* actor = (physx::PxRigidActor*)id;
    mImpl->ClearForce(actor);
}

Vector3 PhysxScene::GetGlobalPostion(uint64_t id) {
    physx::PxRigidActor* actor = (physx::PxRigidActor*)id;
    return mImpl->GetGlobalPostion(actor);
}

Quat PhysxScene::GetGlobalRotate(uint64_t id) {
    physx::PxRigidActor* actor = (physx::PxRigidActor*)id;
    return mImpl->GetGlobalRotate(actor);
}

void PhysxScene::SetGlobalPostion(uint64_t id, const Vector3 &pos) {
    physx::PxRigidActor* actor = (physx::PxRigidActor*)id;
    mImpl->SetGlobalPostion(actor, pos);
}

void PhysxScene::SetGlobalRotate(uint64_t id, const Quat &rotate) {
    physx::PxRigidActor* actor = (physx::PxRigidActor*)id;
    mImpl->SetGlobalRotate(actor, rotate);
}

MY_DLL_EXPORT_FUNC unsigned GetStaticObjCountInScene(const std::string &path) {
    return gSceneInfoMgr->GetStaticObjCount(path);
}
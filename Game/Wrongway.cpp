#include "Wrongway.h"



#include "CollisionObserver.h"
#include "CollisionSubject.h"
#include "GameArena.h"
#include "GameObject.h"
#include "ImageRenderComponent.h"
#include "RandomAIComponent.h"
#include "TileMovementComponent.h"

Wrongway::Wrongway(GameArena* pArena, ArenaTile* pTile) :
	m_pArena(pArena),
	m_pTile(pTile),
	m_spTileMovementComponent(std::make_shared<TileMovementComponent>(pArena, pTile, true, true)),
	m_MovementDelay(1.f),
	m_WrongwayImagePath("images/Wrongway.png")
{
}

void Wrongway::Initialize()
{
	GetParent()->SetTag("Wrongway");
	
	InitializeSprite();

	GetParent()->AddComponent(m_spTileMovementComponent);
	auto movedCallback = [this]() { HandleTileChange(); };
	m_spTileMovementComponent->SubscribeToMoved(movedCallback);

	m_spTileMovementComponent->SetMovementAllowed(TileMovementComponent::MovementType::down, false);
	m_spTileMovementComponent->SetMovementAllowed(TileMovementComponent::MovementType::left, false);

	const std::shared_ptr<RandomAIComponent> spRandomAIComponent = std::make_shared<RandomAIComponent>(m_pArena, 1.f, true, false, true, true);
	GetParent()->AddComponent(spRandomAIComponent);
}

void Wrongway::InitializeSprite()
{
	std::shared_ptr<minigen::ImageRenderComponent> imageRenderComponent = std::make_shared<minigen::ImageRenderComponent>();

	const float tileSize = m_pArena->GetTileSize();
	const float scale = tileSize / 15.f;
	const float offsetX = tileSize * .85f;
	const float offsetY = tileSize;

	imageRenderComponent->AddImage(m_WrongwayImagePath, { -8 * scale - (offsetX),-10 * scale + (offsetY) }, scale);
	m_pParentObject->AddComponent(imageRenderComponent);

	// Collision
	// Create a collision subject
	const Point2f collisionSize = { 8.f * scale, 4.f * scale };
	Rectf collisionBounds{ -collisionSize.x * .5f  - (offsetX), -collisionSize.y * .5f + (tileSize * 1.5f), collisionSize.x, collisionSize.y };
	std::shared_ptr<minigen::CollisionSubject> spCollisionSubject = std::make_shared<minigen::CollisionSubject>(m_pParentObject, collisionBounds);
	m_pParentObject->SetCollisionSubject(spCollisionSubject);
	// Add observers
	const std::shared_ptr<minigen::CollisionObserver> spCollisionObserver = std::make_shared<minigen::CollisionObserver>(this);
	spCollisionSubject->AddObserver(spCollisionObserver);
}

void Wrongway::Update()
{
}

void Wrongway::HandleTileChange() const
{
	if (m_spTileMovementComponent->GetTile()->IsNullTile())
	{
		GetParent()->MarkForDelete();
	}
}

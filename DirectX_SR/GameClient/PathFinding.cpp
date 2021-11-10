#include "pch.h"
#include "PathFinding.h"
#include "Transform.h"
#include "Node.h"
#include "NeviMesh.h"

void PathFinding::Start(NeviMesh* nevi) noexcept
{
}

void PathFinding::Update(float fElapsedTime) noexcept
{
}

void PathFinding::FindPath(D3DXVECTOR3 vTargetPos)
{
	Node* startNode = _pNevi->NodeFormPosition(_pTrans->GetWorldPosition());
	Node* targetNode = _pNevi->NodeFormPosition(vTargetPos);

}

void PathFinding::RetracePath(Node* startNode, Node* endNode)
{
}

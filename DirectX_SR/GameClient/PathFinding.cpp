#include "pch.h"
#include "PathFinding.h"
#include "Transform.h"
#include "Node.h"
#include "NaviMesh.h"
#include "PriorityQueue.h"

PathFinding::PathFinding(NaviMesh* nevi) noexcept
	:_pNavi(nevi)
{
}
PathFinding::~PathFinding() noexcept
{
	Release();
}
bool PathFinding::FindPath(D3DXVECTOR3 vStartPos,D3DXVECTOR3 vTargetPos)
{
	Node* startNode = _pNavi->NodeFormPosition(vStartPos);
	Node* targetNode = _pNavi->NodeFormPosition(vTargetPos);

	PriorityQueue<Node*,std::vector<Node*>, compare> openSet;
	std::unordered_set<Node*> closedSet;
	openSet.push(startNode);

	while (openSet.size() > 0)
	{
		Node* curNode = openSet.top();
		openSet.pop();

		//찾은 노드가 도착점이면 종료 
		if (curNode == targetNode)
		{
			RetracePath(startNode, targetNode);
			return true;
		}

		//현재 노드를 ClosedSet으로 이동
		closedSet.insert(curNode);

		//현재 노드의 이웃들과 비교 
		for (auto n : curNode->GetNeighbours())
		{
			//갈 수 없는 곳 혹은 이미 확인한 곳이면 패스 
			if (!(n->isWalkable()) || closedSet.find(n) != closedSet.end())
				continue;
		
			//g = 시작점~ 현재 노드 , h = 현재~ 목적지 
			float g = curNode->GetGCost() + GetDistance(curNode, n);
			float h = GetDistance(n, targetNode);
			float f = g + h;
			
			if (!openSet.contains(n))
			{
				n->SetCost(g, h);
				n->SetParent(curNode);
				openSet.push(n);
			}
			else
			{
				//오픈에 현재 노드가 있는 경우 수치 비교 후 경로 교체
				//수치가 동일하면 g수치가 큰쪽으로 바꾼다 (갈길이 얼마 안남았다는 뜻)
				if (n->GetFCost() > f || ((n->GetFCost() == f && n->GetGCost() < g)))
				{
					n->SetCost(g,h);
					n->SetParent(curNode);
				}
			}
		}

	}

	return false;
}

void PathFinding::RetracePath(Node* startNode, Node* endNode)
{
	std::list<Node*> path = std::list<Node*>();
	Node* currentNode = endNode;

	while (currentNode != startNode)
	{
		path.push_back(currentNode);
		currentNode = currentNode->GetParent();
	}

	path.reverse();
	_pPath = path;
}

float PathFinding::GetDistance(Node* A, Node* B)
{
	D3DXVECTOR3 vDir = B->GetPos() - A->GetPos();
	return D3DXVec3Length(&vDir);
}

void PathFinding::Release() noexcept
{
	//std::list<Node*>::iterator iter = _pPath.begin();
	//while (iter != _pPath.end())
	//{
	//	if ((*iter) != nullptr)
	//	{
	//		delete (*iter);
	//		(*iter) = nullptr;
	//	}

	//	iter = _pPath.erase(iter);
	//}

	//_pPath.clear();
}

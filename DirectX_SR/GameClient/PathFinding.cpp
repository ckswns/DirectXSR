#include "pch.h"
#include "PathFinding.h"
#include "Transform.h"
#include "Node.h"
#include "NeviMesh.h"
#include "PriorityQueue.h"

PathFinding::PathFinding(NeviMesh* nevi) noexcept
	:_pNevi(nevi)
{
}
bool PathFinding::FindPath(D3DXVECTOR3 vStartPos,D3DXVECTOR3 vTargetPos)
{
	Node* startNode = _pNevi->NodeFormPosition(vStartPos);
	Node* targetNode = _pNevi->NodeFormPosition(vTargetPos);

//	std::priority_queue<Node*,std::vector<Node*>,std::greater<Node*>> openSet;
	PriorityQueue<Node*,std::vector<Node*>, compare> openSet;
	std::unordered_set<Node*> closedSet;
	openSet.push(startNode);

	while (openSet.size() > 0)
	{
		Node* curNode = openSet.top();
		openSet.pop();

		//ã�� ��尡 �������̸� ���� 
		if (curNode == targetNode)
		{
			RetracePath(startNode, targetNode);
			return true;
		}

		//���� ��带 ClosedSet���� �̵�
		closedSet.insert(curNode);

		//���� ����� �̿���� �� 
		for (auto n : curNode->GetNeighbours())
		{
			//�� �� ���� �� Ȥ�� �̹� Ȯ���� ���̸� �н� 
			if (!(n->isWalkable()) || closedSet.find(n) != closedSet.end())
				continue;
		
			//g = ������~ ���� ��� , h = ����~ ������ 
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
				//���¿� ���� ��尡 �ִ� ��� ��ġ �� �� ��� ��ü
				//��ġ�� �����ϸ� g��ġ�� ū������ �ٲ۴� (������ �� �ȳ��Ҵٴ� ��)
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
	//int dstX = abs(B->GetX() - A->GetX());
	//float dstY = abs(B->GetY() - A->GetY());

	//return (dstX + dstY);

	/*if (dstX > dstY)
	{
		return 14 * dstY + 10 * (dstX - dstY);
	}

	return 14 * dstX + 10 * (dstY - dstX);*/

	D3DXVECTOR3 vDir = B->GetPos() - A->GetPos();
	return D3DXVec3Length(&vDir);
}
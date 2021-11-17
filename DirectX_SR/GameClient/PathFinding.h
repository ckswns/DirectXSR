#pragma once

namespace ce
{
	class Transform;
}
#include "Node.h"
class NaviMesh;
class PathFinding 
{
public:		explicit					PathFinding(NaviMesh* nevi) noexcept;
public:		virtual						~PathFinding() noexcept;

public:		virtual void				Start() noexcept { __noop; }

public:		bool						FindPath(D3DXVECTOR3 vStartPos,D3DXVECTOR3 vTargetPos);
private:	void						RetracePath(Node* startNode, Node* endNode);
private:	float						GetDistance(Node* A, Node* B);
private:	void						Release() noexcept;

public:		const std::list<Node*>&		GetPath() const noexcept { return _pPath; }

private:	Transform*					_pTrans;
private:	NaviMesh*					_pNavi;
private:	std::list<Node*>			_pPath;


public:	struct compare 
	{
	bool operator()(Node* a, Node* b)
	{
		return a->GetFCost() > b->GetFCost();
	}
	};
};


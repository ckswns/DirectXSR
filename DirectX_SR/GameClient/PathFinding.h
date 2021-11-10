#pragma once
#include "Behaviour.h"

namespace ce
{
	class Transform;
}
class Node;
class NeviMesh;
class PathFinding : public Behaviour
{
public:		explicit		PathFinding() noexcept { __noop; }
public:		virtual		~PathFinding() noexcept { __noop; }

public:		virtual void				Start(NeviMesh* nevi) noexcept;
public:		virtual void				Update(float fElapsedTime) noexcept;

public:		void						FindPath(D3DXVECTOR3 vTargetPos);
private:		void						RetracePath(Node* startNode, Node* endNode);

private:		Transform*				_pTrans;
private:		NeviMesh*				_pNevi;

};


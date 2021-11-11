#pragma once

namespace ce
{
	class Transform;
}
class Node;
class NeviMesh;
class PathFinding 
{
public:		explicit		PathFinding(NeviMesh* nevi) noexcept;
public:		virtual		~PathFinding() noexcept { __noop; }

public:		virtual void				Start() noexcept { __noop; }

public:		bool						FindPath(D3DXVECTOR3 vStartPos,D3DXVECTOR3 vTargetPos);
private:		void						RetracePath(Node* startNode, Node* endNode);
private:		int						GetDistance(Node* A, Node* B);
public:		std::list<Node*>		GetPath() { return _pPath; }

private:		Transform*				_pTrans;
private:		NeviMesh*				_pNevi;
private:		std::list<Node*>		_pPath;

};


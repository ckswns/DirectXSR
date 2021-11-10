#pragma once
class  Node
{
private:	using			LIST_NODE = std::list<Node*>;

public:	Node(bool walkAble, D3DXVECTOR3 center, int x, int y)
	:_bWalkable(walkAble), _vCenter(center), _iX(x), _iY(y),
	_fGCost(0), _fHCost(0), _fFcost(0), _pParent(nullptr), _pNeighbours(nullptr)
{
	__noop;
}

public:	const float				GetFCost()const { return _fFcost; }
public:	void						SetParent(Node* p) { _pParent = p; }
public:	const Node*			GetParent()const { return _pParent; }
public:	void						AddNeighbor(Node* n) { _pNeighbours.push_back(n); }
public:	const LIST_NODE	GetNeighbours()const { return _pNeighbours; }

private:	bool						_bWalkable;
private:	int								_iX;
private:	int								_iY;
private:	float						_fGCost;
private:	float						_fHCost;
private:	float						_fFcost;
private:	D3DXVECTOR3		_vCenter;
private:	Node* _pParent;
private:	LIST_NODE		_pNeighbours;
};


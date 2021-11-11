#pragma once
class  Node
{
private:	using			LIST_NODE = std::list<Node*>;

public:	Node(bool walkAble, D3DXVECTOR3 center, int x, int y)
	:_bWalkable(walkAble), _vCenter(center), _iX(x), _iY(y),
	_fGCost(0), _fHCost(0), _fFCost(0), _pParent(nullptr)
{
	__noop;
}

	  //fcost가 작은것이 우선순위가 높게 
public:	bool						operator<(const Node n) const
{
	return this->_fFCost > n._fFCost;
}

public:	void						SetParent(Node* p) { _pParent = p; }
public:	void						SetCost(float g, float h) 
										{ _fGCost = g; _fHCost = h; _fFCost = _fGCost + _fHCost; }
public:	void						SetGCost(float g) { _fGCost = g; }
public:	void						AddNeighbor(Node* n) { _pNeighbours.push_back(n); }

public:	const bool				isWalkable() const { return _bWalkable; }
public:	const int				GetX() const { return _iX; }
public:	const int				GetY() const { return _iY; }
public:	const float				GetGCost() const { return _fGCost; }
public:	const float				GetFCost() const { return _fFCost; }
public:	Node*			GetParent() const { return _pParent; }
public:	const LIST_NODE	GetNeighbours() const { return _pNeighbours; }
public:	D3DXVECTOR3		GetPos() { return  _vCenter; }

private:	bool						_bWalkable;
private:	int							_iX;
private:	int							_iY;
private:	float						_fGCost;
private:	float						_fHCost;
private:	float						_fFCost;
private:	D3DXVECTOR3		_vCenter;
private:	Node*					_pParent;
private:	LIST_NODE			_pNeighbours;
};


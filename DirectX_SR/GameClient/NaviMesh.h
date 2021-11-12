#pragma once

class Node;
class NaviMesh
{
private:	using		VEC_NODE = std::vector<Node*>;

public:		explicit	NaviMesh(D3DXVECTOR3* terrain, int x, int y) noexcept
											:_TerrainVtx(terrain), _iSizeX(x), _iSizeY(y) { __noop; }
public:					~NaviMesh() noexcept;

public:		void		Init() noexcept;
private:	void		SetNeighbours() noexcept;
private:	void		Release() noexcept;

public:	Node*			NodeFormPosition(D3DXVECTOR3 Pos) noexcept;

private: VEC_NODE		Grid;
private: D3DXVECTOR3*	_TerrainVtx;
private: int			_iSizeX;
private: int			_iSizeY;
};


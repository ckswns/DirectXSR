#pragma once

class Node;
class NeviMesh
{
private:	using			VEC_NODE = std::vector<Node*>;

public:	explicit		NeviMesh() noexcept { __noop; }
public:					~NeviMesh() noexcept { __noop; }

public:	void			Init() noexcept;
public:	Node*			NodeFormPosition(D3DXVECTOR3 Pos) noexcept;

private: VEC_NODE		Grid;
};


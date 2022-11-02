//***************************************************************************************
// Geometry.h by X_Jun(MKXJun) (C) 2018-2019 All Rights Reserved.
// Licensed under the MIT License.
//
// 生成常见的几何体网格模型
// Generate common geometry meshes.
//***************************************************************************************

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <vector>
#include <string>
#include <map>
#include "Vertex.h"

namespace Geometry
{
	// 网格数据
	template<class VertexType = VertexPosNormalTex, class IndexType = WORD>
	struct MeshData
	{
		std::vector<VertexType> vertexVec;	// 顶点数组
		std::vector<IndexType> indexVec;	// 索引数组

		MeshData()
		{
			// 需检验索引类型合法性
			static_assert(sizeof(IndexType) == 2 || sizeof(IndexType) == 4, "The size of IndexType must be 2 bytes or 4 bytes!");
			static_assert(std::is_unsigned<IndexType>::value, "IndexType must be unsigned integer!");
		}
	};

	// 创建球体网格数据，levels和slices越大，精度越高。
	template<class VertexType = VertexPosNormalTex, class IndexType = WORD>
	MeshData<VertexType, IndexType> CreateSphere(float radius = 1.0f, UINT levels = 20, UINT slices = 20,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	// 创建立方体网格数据
	template<class VertexType = VertexPosNormalTex, class IndexType = WORD>
	MeshData<VertexType, IndexType> CreateBox(float width = 2.0f, float height = 2.0f, float depth = 2.0f,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	// 创建圆柱体网格数据，slices越大，精度越高。
	template<class VertexType = VertexPosNormalTex, class IndexType = WORD>
	MeshData<VertexType, IndexType> CreateCylinder(float radius = 1.0f, float height = 2.0f, UINT slices = 20,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	// 创建只有圆柱体侧面的网格数据，slices越大，精度越高
	template<class VertexType = VertexPosNormalTex, class IndexType = WORD>
	MeshData<VertexType, IndexType> CreateCylinderNoCap(float radius = 1.0f, float height = 2.0f, UINT slices = 20,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	// 创建圆锥体网格数据，slices越大，精度越高。
	template<class VertexType = VertexPosNormalTex, class IndexType = WORD>
	MeshData<VertexType, IndexType> CreateCone(float radius = 1.0f, float height = 2.0f, UINT slices = 20,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	// 创建只有圆锥体侧面网格数据，slices越大，精度越高。
	template<class VertexType = VertexPosNormalTex, class IndexType = WORD>
	MeshData<VertexType, IndexType> CreateConeNoCap(float radius = 1.0f, float height = 2.0f, UINT slices = 20,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	// 创建一个覆盖NDC屏幕的面
	template<class VertexType = VertexPosTex, class IndexType = WORD>
	MeshData<VertexType, IndexType> Create2DShow(const DirectX::XMFLOAT2& center, const DirectX::XMFLOAT2& scale = { 1.0f, 1.0f },
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
	template<class VertexType = VertexPosTex, class IndexType = WORD>
	MeshData<VertexType, IndexType> Create2DShow(float centerX = 0.0f, float centerY = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	// 创建一个平面
	template<class VertexType = VertexPosNormalTex, class IndexType = WORD>
	MeshData<VertexType, IndexType> CreatePlane(const DirectX::XMFLOAT3& center, const DirectX::XMFLOAT2& planeSize = { 10.0f, 10.0f },
		const DirectX::XMFLOAT2& maxTexCoord = { 1.0f, 1.0f }, const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
	template<class VertexType = VertexPosNormalTex, class IndexType = WORD>
	MeshData<VertexType, IndexType> CreatePlane(float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f,
		float width = 10.0f, float depth = 10.0f, float texU = 1.0f, float texV = 1.0f,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
}





namespace Geometry
{
	namespace Internal
	{
		//
		// 以下结构体和函数仅供内部实现使用
		//

		struct VertexData
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT3 normal;
			DirectX::XMFLOAT4 tangent;
			DirectX::XMFLOAT4 color;
			DirectX::XMFLOAT2 tex;
		};

		// 根据目标顶点类型选择性将数据插入
		template<class VertexType>
		inline void InsertVertexElement(VertexType& vertexDst, const VertexData& vertexSrc)
		{
			static std::string semanticName;
			static const std::map<std::string, std::pair<size_t, size_t>> semanticSizeMap = {
				{"POSITION", std::pair<size_t, size_t>(0, 12)},
				{"NORMAL", std::pair<size_t, size_t>(12, 24)},
				{"TANGENT", std::pair<size_t, size_t>(24, 40)},
				{"COLOR", std::pair<size_t, size_t>(40, 56)},
				{"TEXCOORD", std::pair<size_t, size_t>(56, 64)}
			};

			for (size_t i = 0; i < ARRAYSIZE(VertexType::inputLayout); i++)
			{
				semanticName = VertexType::inputLayout[i].SemanticName;
				const auto& range = semanticSizeMap.at(semanticName);
				memcpy_s(reinterpret_cast<char*>(&vertexDst) + VertexType::inputLayout[i].AlignedByteOffset,
					range.second - range.first,
					reinterpret_cast<const char*>(&vertexSrc) + range.first,
					range.second - range.first);
			}
		}
	}
	
	//
	// 几何体方法的实现
	//

	template<class VertexType, class IndexType>
	inline MeshData<VertexType, IndexType> CreateSphere(float radius, UINT levels, UINT slices, const DirectX::XMFLOAT4 & color)
	{
		using namespace DirectX;

		MeshData<VertexType, IndexType> meshData;
		UINT vertexCount = 2 + (levels - 1) * (slices + 1);
		UINT indexCount = 6 * (levels - 1) * slices;
		meshData.vertexVec.resize(vertexCount);
		meshData.indexVec.resize(indexCount);

		Internal::VertexData vertexData;
		IndexType vIndex = 0, iIndex = 0;

		float phi = 0.0f, theta = 0.0f;
		float per_phi = XM_PI / levels;
		float per_theta = XM_2PI / slices;
		float x, y, z;

		// 放入顶端点
		vertexData = { XMFLOAT3(0.0f, radius, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.0f, 0.0f) };
		Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

		for (UINT i = 1; i < levels; ++i)
		{
			phi = per_phi * i;
			// 需要slices + 1个顶点是因为 起点和终点需为同一点，但纹理坐标值不一致
			for (UINT j = 0; j <= slices; ++j)
			{
				theta = per_theta * j;
				x = radius * sinf(phi) * cosf(theta);
				y = radius * cosf(phi);
				z = radius * sinf(phi) * sinf(theta);
				// 计算出局部坐标、法向量、Tangent向量和纹理坐标
				XMFLOAT3 pos = XMFLOAT3(x, y, z), normal;
				XMStoreFloat3(&normal, XMVector3Normalize(XMLoadFloat3(&pos)));

				vertexData = { pos, normal, XMFLOAT4(-sinf(theta), 0.0f, cosf(theta), 1.0f), color, XMFLOAT2(theta / XM_2PI, phi / XM_PI) };
				Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);
			}
		}

		// 放入底端点
		vertexData = { XMFLOAT3(0.0f, -radius, 0.0f), XMFLOAT3(0.0f, -1.0f, 0.0f),
			XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.0f, 1.0f) };
		Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);


		// 逐渐放入索引
		if (levels > 1)
		{
			for (UINT j = 1; j <= slices; ++j)
			{
				meshData.indexVec[iIndex++] = 0;
				meshData.indexVec[iIndex++] = j % (slices + 1) + 1;
				meshData.indexVec[iIndex++] = j;
			}
		}


		for (UINT i = 1; i < levels - 1; ++i)
		{
			for (UINT j = 1; j <= slices; ++j)
			{
				meshData.indexVec[iIndex++] = (i - 1) * (slices + 1) + j;
				meshData.indexVec[iIndex++] = (i - 1) * (slices + 1) + j % (slices + 1) + 1;
				meshData.indexVec[iIndex++] = i * (slices + 1) + j % (slices + 1) + 1;

				meshData.indexVec[iIndex++] = i * (slices + 1) + j % (slices + 1) + 1;
				meshData.indexVec[iIndex++] = i * (slices + 1) + j;
				meshData.indexVec[iIndex++] = (i - 1) * (slices + 1) + j;
			}
		}

		// 逐渐放入索引
		if (levels > 1)
		{
			for (UINT j = 1; j <= slices; ++j)
			{
				meshData.indexVec[iIndex++] = (levels - 2) * (slices + 1) + j;
				meshData.indexVec[iIndex++] = (levels - 2) * (slices + 1) + j % (slices + 1) + 1;
				meshData.indexVec[iIndex++] = (levels - 1) * (slices + 1) + 1;
			}
		}


		return meshData;
	}
// 主要改动了这里
	template<class VertexType, class IndexType>
	inline MeshData<VertexType, IndexType> CreateBox(float width, float height, float depth, const DirectX::XMFLOAT4 & color)
	{
		using namespace DirectX;

		MeshData<VertexType, IndexType> meshData;
		meshData.vertexVec.resize(24 * 76);
		float num1[76] = { -6, -4, -2, 0, 2, 4, 6, 0, -2, -4, -6, -8, -2, 0, 2, 4, 4, 4, 4, -4, -4, -4, -2, 0, 2, -14, -12, -10, -8, -6, -4, -2, -8, -10, -12, -14, -10, -8, -6, -4, -2, -10, -10, -10, -2, -2, -2, -8, -6, -4, 2, 4, 6, 8, 10, 12, 14, 8, 6, 4, 2, 6, 8, 10, 12, 14, 6, 6, 6, 14, 14, 14, 8, 10, 12, 14};
		float num2[76] = { 14, 14, 14, 14, 14, 14, 14, 12, 10, 8, 6, 4, 8, 8, 8, 8, 6, 4, 2, 6, 4, 2, 2, 2, 2, -2, -2, -2, -2, -2, -2, -2, -4, -6, -8, -10, -8, -8, -8, -8, -8, -10, -12, -14, -10, -12, -14, -14, -14, -14, -2, -2, -2, -2, -2, -2, -2, -4, -6, -8, -10, -8, -8, -8, -8, -8, -10, -12, -14, -10, -12, -14, -14, -14, -14, -14 };
		for (int i = 0; i < 76; i++) {
			num1[i] /= 2.0;
			num2[i] /= 2.0;
		}
		Internal::VertexData vertexDataArr[24 * 76];
		float w2 = width / 15, h2 = height / 15, d2 = depth / 15;

		// 右面(+X面)
		for (UINT i = 0; i < 76; i++) {
			vertexDataArr[0 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + w2, 2 * num2[i] * h2 + -h2, -d2);
			vertexDataArr[1 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + w2, 2 * num2[i] * h2 + h2, -d2);
			vertexDataArr[2 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + w2, 2 * num2[i] * h2 + h2, d2);
			vertexDataArr[3 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + w2, 2 * num2[i] * h2 + -h2, d2);
			// 左面(-X面)
			vertexDataArr[4 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + -w2, 2 * num2[i] * h2 + -h2, d2);
			vertexDataArr[5 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + -w2, 2 * num2[i] * h2 + h2, d2);
			vertexDataArr[6 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + -w2, 2 * num2[i] * h2 + h2, -d2);
			vertexDataArr[7 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + -w2, 2 * num2[i] * h2 + -h2, -d2);
			// 顶面(+Y面)
			vertexDataArr[8 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + -w2, 2 * num2[i] * h2 + h2, -d2);
			vertexDataArr[9 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + -w2, 2 * num2[i] * h2 + h2, d2);
			vertexDataArr[10 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + w2, 2 * num2[i] * h2 + h2, d2);
			vertexDataArr[11 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + w2, 2 * num2[i] * h2 + h2, -d2);
			// 底面(-Y面)
			vertexDataArr[12 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + w2, 2 * num2[i] * h2 + -h2, -d2);
			vertexDataArr[13 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + w2, 2 * num2[i] * h2 + -h2, d2);
			vertexDataArr[14 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + -w2, 2 * num2[i] * h2 + -h2, d2);
			vertexDataArr[15 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + -w2, 2 * num2[i] * h2 + -h2, -d2);
			// 背面(+Z面)
			vertexDataArr[16 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + w2, 2 * num2[i] * h2 + -h2, d2);
			vertexDataArr[17 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + w2, 2 * num2[i] * h2 + h2, d2);
			vertexDataArr[18 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + -w2, 2 * num2[i] * h2 + h2, d2);
			vertexDataArr[19 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + -w2, 2 * num2[i] * h2 + -h2, d2);
			// 正面(-Z面)
			vertexDataArr[20 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + -w2, 2 * num2[i] * h2 + -h2, -d2);
			vertexDataArr[21 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + -w2, 2 * num2[i] * h2 + h2, -d2);
			vertexDataArr[22 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + w2, 2 * num2[i] * h2 + h2, -d2);
			vertexDataArr[23 + 24 * i].pos = XMFLOAT3(2 * num1[i] * w2 + w2, 2 * num2[i] * h2 + -h2, -d2);
		}
		for (UINT j = 0; j < 76; j++) {
			for (UINT i = 0; i < 4; ++i)
			{
				// 右面(+X面)
				vertexDataArr[i + j * 24].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);
				vertexDataArr[i + j * 24].tangent = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
				vertexDataArr[i + j * 24].color = color;
				// 左面(-X面)
				vertexDataArr[i + 4 + j * 24].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);
				vertexDataArr[i + 4 + j * 24].tangent = XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f);
				vertexDataArr[i + 4 + j * 24].color = color;
				// 顶面(+Y面)
				vertexDataArr[i + 8 + j * 24].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
				vertexDataArr[i + 8 + j * 24].tangent = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
				vertexDataArr[i + 8 + j * 24].color = color;
				// 底面(-Y面)
				vertexDataArr[i + 12 + j * 24].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);
				vertexDataArr[i + 12 + j * 24].tangent = XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f);
				vertexDataArr[i + 12 + j * 24].color = color;
				// 背面(+Z面)
				vertexDataArr[i + 16 + j * 24].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);
				vertexDataArr[i + 16 + j * 24].tangent = XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f);
				vertexDataArr[i + 16 + j * 24].color = color;
				// 正面(-Z面)
				vertexDataArr[i + 20 + j * 24].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
				vertexDataArr[i + 20 + j * 24].tangent = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
				vertexDataArr[i + 20 + j * 24].color = color;
			}
		}
		for (UINT j = 0; j < 24; j++) {
			for (UINT i = 0; i < 6; ++i)
			{
				vertexDataArr[i * 4 + 24 * j].tex = XMFLOAT2(0.0f, 1.0f);
				vertexDataArr[i * 4 + 1 + 24 * j].tex = XMFLOAT2(0.0f, 0.0f);
				vertexDataArr[i * 4 + 2 + 24 * j].tex = XMFLOAT2(1.0f, 0.0f);
				vertexDataArr[i * 4 + 3 + 24 * j].tex = XMFLOAT2(1.0f, 1.0f);
			}
		}
		for (UINT i = 0; i < 24 * 76; ++i)
		{
			Internal::InsertVertexElement(meshData.vertexVec[i], vertexDataArr[i]);
		}

		meshData.indexVec = {
			0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14, 14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20,
			24, 25, 26, 26, 27, 24, 28, 29, 30, 30, 31, 28, 32, 33, 34, 34, 35, 32, 36, 37, 38, 38, 39, 36, 40, 41, 42, 42, 43, 40, 44, 45, 46, 46, 47, 44,
			48, 49, 50, 50, 51, 48, 52, 53, 54, 54, 55, 52, 56, 57, 58, 58, 59, 56, 60, 61, 62, 62, 63, 60, 64, 65, 66, 66, 67, 64, 68, 69, 70, 70, 71, 68,
			72, 73, 74, 74, 75, 72, 76, 77, 78, 78, 79, 76, 80, 81, 82, 82, 83, 80, 84, 85, 86, 86, 87, 84, 88, 89, 90, 90, 91, 88, 92, 93, 94, 94, 95, 92,
			96, 97, 98, 98, 99, 96, 100, 101, 102, 102, 103, 100, 104, 105, 106, 106, 107, 104, 108, 109, 110, 110, 111, 108, 112, 113, 114, 114, 115, 112, 116, 117, 118, 118, 119, 116,
			120, 121, 122, 122, 123, 120, 124, 125, 126, 126, 127, 124, 128, 129, 130, 130, 131, 128, 132, 133, 134, 134, 135, 132, 136, 137, 138, 138, 139, 136, 140, 141, 142, 142, 143, 140,
			144, 145, 146, 146, 147, 144, 148, 149, 150, 150, 151, 148, 152, 153, 154, 154, 155, 152, 156, 157, 158, 158, 159, 156, 160, 161, 162, 162, 163, 160, 164, 165, 166, 166, 167, 164,
			168, 169, 170, 170, 171, 168, 172, 173, 174, 174, 175, 172, 176, 177, 178, 178, 179, 176, 180, 181, 182, 182, 183, 180, 184, 185, 186, 186, 187, 184, 188, 189, 190, 190, 191, 188,
			192, 193, 194, 194, 195, 192, 196, 197, 198, 198, 199, 196, 200, 201, 202, 202, 203, 200, 204, 205, 206, 206, 207, 204, 208, 209, 210, 210, 211, 208, 212, 213, 214, 214, 215, 212,
			216, 217, 218, 218, 219, 216, 220, 221, 222, 222, 223, 220, 224, 225, 226, 226, 227, 224, 228, 229, 230, 230, 231, 228, 232, 233, 234, 234, 235, 232, 236, 237, 238, 238, 239, 236,
			240, 241, 242, 242, 243, 240, 244, 245, 246, 246, 247, 244, 248, 249, 250, 250, 251, 248, 252, 253, 254, 254, 255, 252, 256, 257, 258, 258, 259, 256, 260, 261, 262, 262, 263, 260,
			264, 265, 266, 266, 267, 264, 268, 269, 270, 270, 271, 268, 272, 273, 274, 274, 275, 272, 276, 277, 278, 278, 279, 276, 280, 281, 282, 282, 283, 280, 284, 285, 286, 286, 287, 284,
			288, 289, 290, 290, 291, 288, 292, 293, 294, 294, 295, 292, 296, 297, 298, 298, 299, 296, 300, 301, 302, 302, 303, 300, 304, 305, 306, 306, 307, 304, 308, 309, 310, 310, 311, 308,
			312, 313, 314, 314, 315, 312, 316, 317, 318, 318, 319, 316, 320, 321, 322, 322, 323, 320, 324, 325, 326, 326, 327, 324, 328, 329, 330, 330, 331, 328, 332, 333, 334, 334, 335, 332,
			336, 337, 338, 338, 339, 336, 340, 341, 342, 342, 343, 340, 344, 345, 346, 346, 347, 344, 348, 349, 350, 350, 351, 348, 352, 353, 354, 354, 355, 352, 356, 357, 358, 358, 359, 356,
			360, 361, 362, 362, 363, 360, 364, 365, 366, 366, 367, 364, 368, 369, 370, 370, 371, 368, 372, 373, 374, 374, 375, 372, 376, 377, 378, 378, 379, 376, 380, 381, 382, 382, 383, 380,
			384, 385, 386, 386, 387, 384, 388, 389, 390, 390, 391, 388, 392, 393, 394, 394, 395, 392, 396, 397, 398, 398, 399, 396, 400, 401, 402, 402, 403, 400, 404, 405, 406, 406, 407, 404,
			408, 409, 410, 410, 411, 408, 412, 413, 414, 414, 415, 412, 416, 417, 418, 418, 419, 416, 420, 421, 422, 422, 423, 420, 424, 425, 426, 426, 427, 424, 428, 429, 430, 430, 431, 428,
			432, 433, 434, 434, 435, 432, 436, 437, 438, 438, 439, 436, 440, 441, 442, 442, 443, 440, 444, 445, 446, 446, 447, 444, 448, 449, 450, 450, 451, 448, 452, 453, 454, 454, 455, 452,
			456, 457, 458, 458, 459, 456, 460, 461, 462, 462, 463, 460, 464, 465, 466, 466, 467, 464, 468, 469, 470, 470, 471, 468, 472, 473, 474, 474, 475, 472, 476, 477, 478, 478, 479, 476,
			480, 481, 482, 482, 483, 480, 484, 485, 486, 486, 487, 484, 488, 489, 490, 490, 491, 488, 492, 493, 494, 494, 495, 492, 496, 497, 498, 498, 499, 496, 500, 501, 502, 502, 503, 500,
			504, 505, 506, 506, 507, 504, 508, 509, 510, 510, 511, 508, 512, 513, 514, 514, 515, 512, 516, 517, 518, 518, 519, 516, 520, 521, 522, 522, 523, 520, 524, 525, 526, 526, 527, 524,
			528, 529, 530, 530, 531, 528, 532, 533, 534, 534, 535, 532, 536, 537, 538, 538, 539, 536, 540, 541, 542, 542, 543, 540, 544, 545, 546, 546, 547, 544, 548, 549, 550, 550, 551, 548,
			552, 553, 554, 554, 555, 552, 556, 557, 558, 558, 559, 556, 560, 561, 562, 562, 563, 560, 564, 565, 566, 566, 567, 564, 568, 569, 570, 570, 571, 568, 572, 573, 574, 574, 575, 572,
			576, 577, 578, 578, 579, 576, 580, 581, 582, 582, 583, 580, 584, 585, 586, 586, 587, 584, 588, 589, 590, 590, 591, 588, 592, 593, 594, 594, 595, 592, 596, 597, 598, 598, 599, 596,
			600, 601, 602, 602, 603, 600, 604, 605, 606, 606, 607, 604, 608, 609, 610, 610, 611, 608, 612, 613, 614, 614, 615, 612, 616, 617, 618, 618, 619, 616, 620, 621, 622, 622, 623, 620,
			624, 625, 626, 626, 627, 624, 628, 629, 630, 630, 631, 628, 632, 633, 634, 634, 635, 632, 636, 637, 638, 638, 639, 636, 640, 641, 642, 642, 643, 640, 644, 645, 646, 646, 647, 644,
			648, 649, 650, 650, 651, 648, 652, 653, 654, 654, 655, 652, 656, 657, 658, 658, 659, 656, 660, 661, 662, 662, 663, 660, 664, 665, 666, 666, 667, 664, 668, 669, 670, 670, 671, 668,
			672, 673, 674, 674, 675, 672, 676, 677, 678, 678, 679, 676, 680, 681, 682, 682, 683, 680, 684, 685, 686, 686, 687, 684, 688, 689, 690, 690, 691, 688, 692, 693, 694, 694, 695, 692,
			696, 697, 698, 698, 699, 696, 700, 701, 702, 702, 703, 700, 704, 705, 706, 706, 707, 704, 708, 709, 710, 710, 711, 708, 712, 713, 714, 714, 715, 712, 716, 717, 718, 718, 719, 716,
			720, 721, 722, 722, 723, 720, 724, 725, 726, 726, 727, 724, 728, 729, 730, 730, 731, 728, 732, 733, 734, 734, 735, 732, 736, 737, 738, 738, 739, 736, 740, 741, 742, 742, 743, 740,
			744, 745, 746, 746, 747, 744, 748, 749, 750, 750, 751, 748, 752, 753, 754, 754, 755, 752, 756, 757, 758, 758, 759, 756, 760, 761, 762, 762, 763, 760, 764, 765, 766, 766, 767, 764,
			768, 769, 770, 770, 771, 768, 772, 773, 774, 774, 775, 772, 776, 777, 778, 778, 779, 776, 780, 781, 782, 782, 783, 780, 784, 785, 786, 786, 787, 784, 788, 789, 790, 790, 791, 788,
			792, 793, 794, 794, 795, 792, 796, 797, 798, 798, 799, 796, 800, 801, 802, 802, 803, 800, 804, 805, 806, 806, 807, 804, 808, 809, 810, 810, 811, 808, 812, 813, 814, 814, 815, 812,
			816, 817, 818, 818, 819, 816, 820, 821, 822, 822, 823, 820, 824, 825, 826, 826, 827, 824, 828, 829, 830, 830, 831, 828, 832, 833, 834, 834, 835, 832, 836, 837, 838, 838, 839, 836,
			840, 841, 842, 842, 843, 840, 844, 845, 846, 846, 847, 844, 848, 849, 850, 850, 851, 848, 852, 853, 854, 854, 855, 852, 856, 857, 858, 858, 859, 856, 860, 861, 862, 862, 863, 860,
			864, 865, 866, 866, 867, 864, 868, 869, 870, 870, 871, 868, 872, 873, 874, 874, 875, 872, 876, 877, 878, 878, 879, 876, 880, 881, 882, 882, 883, 880, 884, 885, 886, 886, 887, 884,
			888, 889, 890, 890, 891, 888, 892, 893, 894, 894, 895, 892, 896, 897, 898, 898, 899, 896, 900, 901, 902, 902, 903, 900, 904, 905, 906, 906, 907, 904, 908, 909, 910, 910, 911, 908,
			912, 913, 914, 914, 915, 912, 916, 917, 918, 918, 919, 916, 920, 921, 922, 922, 923, 920, 924, 925, 926, 926, 927, 924, 928, 929, 930, 930, 931, 928, 932, 933, 934, 934, 935, 932,
			936, 937, 938, 938, 939, 936, 940, 941, 942, 942, 943, 940, 944, 945, 946, 946, 947, 944, 948, 949, 950, 950, 951, 948, 952, 953, 954, 954, 955, 952, 956, 957, 958, 958, 959, 956,
			960, 961, 962, 962, 963, 960, 964, 965, 966, 966, 967, 964, 968, 969, 970, 970, 971, 968, 972, 973, 974, 974, 975, 972, 976, 977, 978, 978, 979, 976, 980, 981, 982, 982, 983, 980,
			984, 985, 986, 986, 987, 984, 988, 989, 990, 990, 991, 988, 992, 993, 994, 994, 995, 992, 996, 997, 998, 998, 999, 996, 1000, 1001, 1002, 1002, 1003, 1000, 1004, 1005, 1006, 1006, 1007, 1004,
			1008, 1009, 1010, 1010, 1011, 1008, 1012, 1013, 1014, 1014, 1015, 1012, 1016, 1017, 1018, 1018, 1019, 1016, 1020, 1021, 1022, 1022, 1023, 1020, 1024, 1025, 1026, 1026, 1027, 1024, 1028, 1029, 1030, 1030, 1031, 1028,
			1032, 1033, 1034, 1034, 1035, 1032, 1036, 1037, 1038, 1038, 1039, 1036, 1040, 1041, 1042, 1042, 1043, 1040, 1044, 1045, 1046, 1046, 1047, 1044, 1048, 1049, 1050, 1050, 1051, 1048, 1052, 1053, 1054, 1054, 1055, 1052,
			1056, 1057, 1058, 1058, 1059, 1056, 1060, 1061, 1062, 1062, 1063, 1060, 1064, 1065, 1066, 1066, 1067, 1064, 1068, 1069, 1070, 1070, 1071, 1068, 1072, 1073, 1074, 1074, 1075, 1072, 1076, 1077, 1078, 1078, 1079, 1076,
			1080, 1081, 1082, 1082, 1083, 1080, 1084, 1085, 1086, 1086, 1087, 1084, 1088, 1089, 1090, 1090, 1091, 1088, 1092, 1093, 1094, 1094, 1095, 1092, 1096, 1097, 1098, 1098, 1099, 1096, 1100, 1101, 1102, 1102, 1103, 1100,
			1104, 1105, 1106, 1106, 1107, 1104, 1108, 1109, 1110, 1110, 1111, 1108, 1112, 1113, 1114, 1114, 1115, 1112, 1116, 1117, 1118, 1118, 1119, 1116, 1120, 1121, 1122, 1122, 1123, 1120, 1124, 1125, 1126, 1126, 1127, 1124,
			1128, 1129, 1130, 1130, 1131, 1128, 1132, 1133, 1134, 1134, 1135, 1132, 1136, 1137, 1138, 1138, 1139, 1136, 1140, 1141, 1142, 1142, 1143, 1140, 1144, 1145, 1146, 1146, 1147, 1144, 1148, 1149, 1150, 1150, 1151, 1148,
			1152, 1153, 1154, 1154, 1155, 1152, 1156, 1157, 1158, 1158, 1159, 1156, 1160, 1161, 1162, 1162, 1163, 1160, 1164, 1165, 1166, 1166, 1167, 1164, 1168, 1169, 1170, 1170, 1171, 1168, 1172, 1173, 1174, 1174, 1175, 1172,
			1176, 1177, 1178, 1178, 1179, 1176, 1180, 1181, 1182, 1182, 1183, 1180, 1184, 1185, 1186, 1186, 1187, 1184, 1188, 1189, 1190, 1190, 1191, 1188, 1192, 1193, 1194, 1194, 1195, 1192, 1196, 1197, 1198, 1198, 1199, 1196,
			1200, 1201, 1202, 1202, 1203, 1200, 1204, 1205, 1206, 1206, 1207, 1204, 1208, 1209, 1210, 1210, 1211, 1208, 1212, 1213, 1214, 1214, 1215, 1212, 1216, 1217, 1218, 1218, 1219, 1216, 1220, 1221, 1222, 1222, 1223, 1220,
			1224, 1225, 1226, 1226, 1227, 1224, 1228, 1229, 1230, 1230, 1231, 1228, 1232, 1233, 1234, 1234, 1235, 1232, 1236, 1237, 1238, 1238, 1239, 1236, 1240, 1241, 1242, 1242, 1243, 1240, 1244, 1245, 1246, 1246, 1247, 1244,
			1248, 1249, 1250, 1250, 1251, 1248, 1252, 1253, 1254, 1254, 1255, 1252, 1256, 1257, 1258, 1258, 1259, 1256, 1260, 1261, 1262, 1262, 1263, 1260, 1264, 1265, 1266, 1266, 1267, 1264, 1268, 1269, 1270, 1270, 1271, 1268,
			1272, 1273, 1274, 1274, 1275, 1272, 1276, 1277, 1278, 1278, 1279, 1276, 1280, 1281, 1282, 1282, 1283, 1280, 1284, 1285, 1286, 1286, 1287, 1284, 1288, 1289, 1290, 1290, 1291, 1288, 1292, 1293, 1294, 1294, 1295, 1292,
			1296, 1297, 1298, 1298, 1299, 1296, 1300, 1301, 1302, 1302, 1303, 1300, 1304, 1305, 1306, 1306, 1307, 1304, 1308, 1309, 1310, 1310, 1311, 1308, 1312, 1313, 1314, 1314, 1315, 1312, 1316, 1317, 1318, 1318, 1319, 1316,
			1320, 1321, 1322, 1322, 1323, 1320, 1324, 1325, 1326, 1326, 1327, 1324, 1328, 1329, 1330, 1330, 1331, 1328, 1332, 1333, 1334, 1334, 1335, 1332, 1336, 1337, 1338, 1338, 1339, 1336, 1340, 1341, 1342, 1342, 1343, 1340,
			1344, 1345, 1346, 1346, 1347, 1344, 1348, 1349, 1350, 1350, 1351, 1348, 1352, 1353, 1354, 1354, 1355, 1352, 1356, 1357, 1358, 1358, 1359, 1356, 1360, 1361, 1362, 1362, 1363, 1360, 1364, 1365, 1366, 1366, 1367, 1364,
			1368, 1369, 1370, 1370, 1371, 1368, 1372, 1373, 1374, 1374, 1375, 1372, 1376, 1377, 1378, 1378, 1379, 1376, 1380, 1381, 1382, 1382, 1383, 1380, 1384, 1385, 1386, 1386, 1387, 1384, 1388, 1389, 1390, 1390, 1391, 1388,
			1392, 1393, 1394, 1394, 1395, 1392, 1396, 1397, 1398, 1398, 1399, 1396, 1400, 1401, 1402, 1402, 1403, 1400, 1404, 1405, 1406, 1406, 1407, 1404, 1408, 1409, 1410, 1410, 1411, 1408, 1412, 1413, 1414, 1414, 1415, 1412,
			1416, 1417, 1418, 1418, 1419, 1416, 1420, 1421, 1422, 1422, 1423, 1420, 1424, 1425, 1426, 1426, 1427, 1424, 1428, 1429, 1430, 1430, 1431, 1428, 1432, 1433, 1434, 1434, 1435, 1432, 1436, 1437, 1438, 1438, 1439, 1436,
			1440, 1441, 1442, 1442, 1443, 1440, 1444, 1445, 1446, 1446, 1447, 1444, 1448, 1449, 1450, 1450, 1451, 1448, 1452, 1453, 1454, 1454, 1455, 1452, 1456, 1457, 1458, 1458, 1459, 1456, 1460, 1461, 1462, 1462, 1463, 1460,
			1464, 1465, 1466, 1466, 1467, 1464, 1468, 1469, 1470, 1470, 1471, 1468, 1472, 1473, 1474, 1474, 1475, 1472, 1476, 1477, 1478, 1478, 1479, 1476, 1480, 1481, 1482, 1482, 1483, 1480, 1484, 1485, 1486, 1486, 1487, 1484,
			1488, 1489, 1490, 1490, 1491, 1488, 1492, 1493, 1494, 1494, 1495, 1492, 1496, 1497, 1498, 1498, 1499, 1496, 1500, 1501, 1502, 1502, 1503, 1500, 1504, 1505, 1506, 1506, 1507, 1504, 1508, 1509, 1510, 1510, 1511, 1508,
			1512, 1513, 1514, 1514, 1515, 1512, 1516, 1517, 1518, 1518, 1519, 1516, 1520, 1521, 1522, 1522, 1523, 1520, 1524, 1525, 1526, 1526, 1527, 1524, 1528, 1529, 1530, 1530, 1531, 1528, 1532, 1533, 1534, 1534, 1535, 1532,
			1536, 1537, 1538, 1538, 1539, 1536, 1540, 1541, 1542, 1542, 1543, 1540, 1544, 1545, 1546, 1546, 1547, 1544, 1548, 1549, 1550, 1550, 1551, 1548, 1552, 1553, 1554, 1554, 1555, 1552, 1556, 1557, 1558, 1558, 1559, 1556,
			1560, 1561, 1562, 1562, 1563, 1560, 1564, 1565, 1566, 1566, 1567, 1564, 1568, 1569, 1570, 1570, 1571, 1568, 1572, 1573, 1574, 1574, 1575, 1572, 1576, 1577, 1578, 1578, 1579, 1576, 1580, 1581, 1582, 1582, 1583, 1580,
			1584, 1585, 1586, 1586, 1587, 1584, 1588, 1589, 1590, 1590, 1591, 1588, 1592, 1593, 1594, 1594, 1595, 1592, 1596, 1597, 1598, 1598, 1599, 1596, 1600, 1601, 1602, 1602, 1603, 1600, 1604, 1605, 1606, 1606, 1607, 1604,
			1608, 1609, 1610, 1610, 1611, 1608, 1612, 1613, 1614, 1614, 1615, 1612, 1616, 1617, 1618, 1618, 1619, 1616, 1620, 1621, 1622, 1622, 1623, 1620, 1624, 1625, 1626, 1626, 1627, 1624, 1628, 1629, 1630, 1630, 1631, 1628,
			1632, 1633, 1634, 1634, 1635, 1632, 1636, 1637, 1638, 1638, 1639, 1636, 1640, 1641, 1642, 1642, 1643, 1640, 1644, 1645, 1646, 1646, 1647, 1644, 1648, 1649, 1650, 1650, 1651, 1648, 1652, 1653, 1654, 1654, 1655, 1652,
			1656, 1657, 1658, 1658, 1659, 1656, 1660, 1661, 1662, 1662, 1663, 1660, 1664, 1665, 1666, 1666, 1667, 1664, 1668, 1669, 1670, 1670, 1671, 1668, 1672, 1673, 1674, 1674, 1675, 1672, 1676, 1677, 1678, 1678, 1679, 1676,
			1680, 1681, 1682, 1682, 1683, 1680, 1684, 1685, 1686, 1686, 1687, 1684, 1688, 1689, 1690, 1690, 1691, 1688, 1692, 1693, 1694, 1694, 1695, 1692, 1696, 1697, 1698, 1698, 1699, 1696, 1700, 1701, 1702, 1702, 1703, 1700,
			1704, 1705, 1706, 1706, 1707, 1704, 1708, 1709, 1710, 1710, 1711, 1708, 1712, 1713, 1714, 1714, 1715, 1712, 1716, 1717, 1718, 1718, 1719, 1716, 1720, 1721, 1722, 1722, 1723, 1720, 1724, 1725, 1726, 1726, 1727, 1724,
			1728, 1729, 1730, 1730, 1731, 1728, 1732, 1733, 1734, 1734, 1735, 1732, 1736, 1737, 1738, 1738, 1739, 1736, 1740, 1741, 1742, 1742, 1743, 1740, 1744, 1745, 1746, 1746, 1747, 1744, 1748, 1749, 1750, 1750, 1751, 1748,
			1752, 1753, 1754, 1754, 1755, 1752, 1756, 1757, 1758, 1758, 1759, 1756, 1760, 1761, 1762, 1762, 1763, 1760, 1764, 1765, 1766, 1766, 1767, 1764, 1768, 1769, 1770, 1770, 1771, 1768, 1772, 1773, 1774, 1774, 1775, 1772,
			1776, 1777, 1778, 1778, 1779, 1776, 1780, 1781, 1782, 1782, 1783, 1780, 1784, 1785, 1786, 1786, 1787, 1784, 1788, 1789, 1790, 1790, 1791, 1788, 1792, 1793, 1794, 1794, 1795, 1792, 1796, 1797, 1798, 1798, 1799, 1796,
			1800, 1801, 1802, 1802, 1803, 1800, 1804, 1805, 1806, 1806, 1807, 1804, 1808, 1809, 1810, 1810, 1811, 1808, 1812, 1813, 1814, 1814, 1815, 1812, 1816, 1817, 1818, 1818, 1819, 1816, 1820, 1821, 1822, 1822, 1823, 1820
		};

		return meshData;
	}

	template<class VertexType, class IndexType>
	inline MeshData<VertexType, IndexType> CreateCylinder(float radius, float height, UINT slices, const DirectX::XMFLOAT4 & color)
	{
		using namespace DirectX;

		auto meshData = CreateCylinderNoCap<VertexType, IndexType>(radius, height, slices, color);
		UINT vertexCount = 4 * (slices + 1) + 2;
		UINT indexCount = 12 * slices;
		meshData.vertexVec.resize(vertexCount);
		meshData.indexVec.resize(indexCount);

		float h2 = height / 2;
		float theta = 0.0f;
		float per_theta = XM_2PI / slices;

		IndexType vIndex = 2 * (slices + 1), iIndex = 6 * slices;
		IndexType offset = 2 * (slices + 1);
		Internal::VertexData vertexData;

		// 放入顶端圆心
		vertexData = { XMFLOAT3(0.0f, h2, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f),
			XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.5f, 0.5f) };
		Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

		// 放入顶端圆上各点
		for (UINT i = 0; i <= slices; ++i)
		{
			theta = i * per_theta;
			vertexData = { XMFLOAT3(radius * cosf(theta), h2, radius * sinf(theta)), XMFLOAT3(0.0f, 1.0f, 0.0f),
				XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(cosf(theta) / 2 + 0.5f, sinf(theta) / 2 + 0.5f) };
			Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);
		}

		// 放入底端圆心
		vertexData = { XMFLOAT3(0.0f, -h2, 0.0f), XMFLOAT3(0.0f, -1.0f, 0.0f),
			XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.5f, 0.5f) };
		Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

		// 放入底部圆上各点
		for (UINT i = 0; i <= slices; ++i)
		{
			theta = i * per_theta;
			vertexData = { XMFLOAT3(radius * cosf(theta), -h2, radius * sinf(theta)), XMFLOAT3(0.0f, -1.0f, 0.0f),
				XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(cosf(theta) / 2 + 0.5f, sinf(theta) / 2 + 0.5f) };
			Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);
		}

		

		// 逐渐放入顶部三角形索引
		for (UINT i = 1; i <= slices; ++i)
		{
			meshData.indexVec[iIndex++] = offset;
			meshData.indexVec[iIndex++] = offset + i % (slices + 1) + 1;
			meshData.indexVec[iIndex++] = offset + i;
		}

		// 逐渐放入底部三角形索引
		offset += slices + 2;
		for (UINT i = 1; i <= slices; ++i)
		{
			meshData.indexVec[iIndex++] = offset;
			meshData.indexVec[iIndex++] = offset + i;
			meshData.indexVec[iIndex++] = offset + i % (slices + 1) + 1;
		}

		return meshData;
	}

	template<class VertexType, class IndexType>
	inline MeshData<VertexType, IndexType> CreateCylinderNoCap(float radius, float height, UINT slices, const DirectX::XMFLOAT4 & color)
	{
		using namespace DirectX;

		MeshData<VertexType, IndexType> meshData;
		UINT vertexCount = 2 * (slices + 1);
		UINT indexCount = 6 * slices;
		meshData.vertexVec.resize(vertexCount);
		meshData.indexVec.resize(indexCount);

		float h2 = height / 2;
		float theta = 0.0f;
		float per_theta = XM_2PI / slices;

		Internal::VertexData vertexData;

		// 放入侧面顶端点
		for (UINT i = 0; i <= slices; ++i)
		{
			theta = i * per_theta;
			vertexData = { XMFLOAT3(radius * cosf(theta), h2, radius * sinf(theta)), XMFLOAT3(cosf(theta), 0.0f, sinf(theta)),
				XMFLOAT4(-sinf(theta), 0.0f, cosf(theta), 1.0f), color, XMFLOAT2(theta / XM_2PI, 0.0f) };
			Internal::InsertVertexElement(meshData.vertexVec[i], vertexData);
		}

		// 放入侧面底端点
		for (UINT i = 0; i <= slices; ++i)
		{
			theta = i * per_theta;
			vertexData = { XMFLOAT3(radius * cosf(theta), -h2, radius * sinf(theta)), XMFLOAT3(cosf(theta), 0.0f, sinf(theta)),
				XMFLOAT4(-sinf(theta), 0.0f, cosf(theta), 1.0f), color, XMFLOAT2(theta / XM_2PI, 1.0f) };
			UINT vIndex = (slices + 1) + i;
			Internal::InsertVertexElement(meshData.vertexVec[vIndex], vertexData);
		}

		// 放入索引
		UINT iIndex = 0;

		for (UINT i = 0; i < slices; ++i)
		{
			meshData.indexVec[iIndex++] = i;
			meshData.indexVec[iIndex++] = i + 1;
			meshData.indexVec[iIndex++] = (slices + 1) + i + 1;

			meshData.indexVec[iIndex++] = (slices + 1) + i + 1;
			meshData.indexVec[iIndex++] = (slices + 1) + i;
			meshData.indexVec[iIndex++] = i;
		}


		return meshData;
	}

	template<class VertexType, class IndexType>
	MeshData<VertexType, IndexType> CreateCone(float radius, float height, UINT slices, const DirectX::XMFLOAT4& color)
	{
		using namespace DirectX;
		auto meshData = CreateConeNoCap<VertexType, IndexType>(radius, height, slices, color);

		UINT vertexCount = 3 * slices + 1;
		UINT indexCount = 6 * slices;
		meshData.vertexVec.resize(vertexCount);
		meshData.indexVec.resize(indexCount);
		
		float h2 = height / 2;
		float theta = 0.0f;
		float per_theta = XM_2PI / slices;
		UINT iIndex = 3 * slices;
		UINT vIndex = 2 * slices;
		Internal::VertexData vertexData;

		// 放入圆锥底面顶点
		for (UINT i = 0; i < slices; ++i)
		{
			theta = i * per_theta;
			vertexData = { XMFLOAT3(radius * cosf(theta), -h2, radius * sinf(theta)), XMFLOAT3(0.0f, -1.0f, 0.0f),
				XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(cosf(theta) / 2 + 0.5f, sinf(theta) / 2 + 0.5f) };
			Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);
		}
		vertexData = { XMFLOAT3(0.0f, -h2, 0.0f), XMFLOAT3(0.0f, -1.0f, 0.0f),
				XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.5f, 0.5f) };
		Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

		// 放入索引
		UINT offset = 2 * slices;
		for (UINT i = 0; i < slices; ++i)
		{
			meshData.indexVec[iIndex++] = offset + slices;
			meshData.indexVec[iIndex++] = offset + i % slices;
			meshData.indexVec[iIndex++] = offset + (i + 1) % slices;
		}

		return meshData;
	}

	template<class VertexType, class IndexType>
	MeshData<VertexType, IndexType> CreateConeNoCap(float radius, float height, UINT slices, const DirectX::XMFLOAT4& color)
	{
		using namespace DirectX;

		MeshData<VertexType, IndexType> meshData;
		UINT vertexCount = 2 * slices;
		UINT indexCount = 3 * slices;
		meshData.vertexVec.resize(vertexCount);
		meshData.indexVec.resize(indexCount);

		float h2 = height / 2;
		float theta = 0.0f;
		float per_theta = XM_2PI / slices;
		float len = sqrtf(height * height + radius * radius);
		UINT iIndex = 0;
		UINT vIndex = 0;
		Internal::VertexData vertexData;

		// 放入圆锥尖端顶点(每个顶点包含不同的法向量和切线向量)
		for (UINT i = 0; i < slices; ++i)
		{
			theta = i * per_theta + per_theta / 2;
			vertexData = { XMFLOAT3(0.0f, h2, 0.0f), XMFLOAT3(radius * cosf(theta) / len, height / len, radius * sinf(theta) / len),
				XMFLOAT4(-sinf(theta), 0.0f, cosf(theta), 1.0f), color, XMFLOAT2(0.5f, 0.5f) };
			Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);
		}

		// 放入圆锥底面顶点
		for (UINT i = 0; i < slices; ++i)
		{
			theta = i * per_theta;
			vertexData = { XMFLOAT3(radius * cosf(theta), -h2, radius * sinf(theta)), XMFLOAT3(radius * cosf(theta) / len, height / len, radius * sinf(theta) / len),
				XMFLOAT4(-sinf(theta), 0.0f, cosf(theta), 1.0f), color, XMFLOAT2(cosf(theta) / 2 + 0.5f, sinf(theta) / 2 + 0.5f) };
			Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);
		}

		// 放入索引
		for (UINT i = 0; i < slices; ++i)
		{
			meshData.indexVec[iIndex++] = i;
			meshData.indexVec[iIndex++] = slices + (i + 1) % slices;
			meshData.indexVec[iIndex++] = slices + i % slices;
		}

		return meshData;
	}

	template<class VertexType, class IndexType>
	inline MeshData<VertexType, IndexType> Create2DShow(const DirectX::XMFLOAT2 & center, const DirectX::XMFLOAT2 & scale,
		const DirectX::XMFLOAT4 & color)
	{
		return Create2DShow<VertexType, IndexType>(center.x, center.y, scale.x, scale.y, color);
	}

	template<class VertexType, class IndexType>
	inline MeshData<VertexType, IndexType> Create2DShow(float centerX, float centerY, float scaleX, float scaleY, const DirectX::XMFLOAT4 & color)
	{
		using namespace DirectX;

		MeshData<VertexType, IndexType> meshData;
		meshData.vertexVec.resize(4);

		Internal::VertexData vertexData;
		IndexType vIndex = 0;

		vertexData = { XMFLOAT3(centerX - scaleX, centerY - scaleY, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),
			XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.0f, 1.0f) };
		Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

		vertexData = { XMFLOAT3(centerX - scaleX, centerY + scaleY, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),
			XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.0f, 0.0f) };
		Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

		vertexData = { XMFLOAT3(centerX + scaleX, centerY + scaleY, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),
			XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(1.0f, 0.0f) };
		Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

		vertexData = { XMFLOAT3(centerX + scaleX, centerY - scaleY, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),
			XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(1.0f, 1.0f) };
		Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

		meshData.indexVec = { 0, 1, 2, 2, 3, 0 };
		return meshData;
	}

	template<class VertexType, class IndexType>
	inline MeshData<VertexType, IndexType> CreatePlane(const DirectX::XMFLOAT3 & center, const DirectX::XMFLOAT2 & planeSize,
		const DirectX::XMFLOAT2 & maxTexCoord, const DirectX::XMFLOAT4 & color)
	{
		return CreatePlane<VertexType, IndexType>(center.x, center.y, center.z, planeSize.x, planeSize.y, maxTexCoord.x, maxTexCoord.y, color);
	}

	template<class VertexType, class IndexType>
	inline MeshData<VertexType, IndexType> CreatePlane(float centerX, float centerY, float centerZ, float width, float depth, float texU, float texV, const DirectX::XMFLOAT4 & color)
	{
		using namespace DirectX;

		MeshData<VertexType, IndexType> meshData;
		meshData.vertexVec.resize(4);

		Internal::VertexData vertexData;
		IndexType vIndex = 0;

		vertexData = { XMFLOAT3(centerX - width / 2, centerY, centerZ - depth / 2), XMFLOAT3(0.0f, 1.0f, 0.0f),
			XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.0f, texV) };
		Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

		vertexData = { XMFLOAT3(centerX - width / 2, centerY, centerZ + depth / 2), XMFLOAT3(0.0f, 1.0f, 0.0f),
			XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.0f, 0.0f) };
		Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

		vertexData = { XMFLOAT3(centerX + width / 2, centerY, centerZ + depth / 2), XMFLOAT3(0.0f, 1.0f, 0.0f),
			XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(texU, 0.0f) };
		Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

		vertexData = { XMFLOAT3(centerX + width / 2, centerY, centerZ - depth / 2), XMFLOAT3(0.0f, 1.0f, 0.0f),
			XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(texU, texV) };
		Internal::InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

		meshData.indexVec = { 0, 1, 2, 2, 3, 0 };
		return meshData;
	}
}



#endif

